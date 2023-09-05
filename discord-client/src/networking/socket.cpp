//
// Created by Ariel Saldana on 8/20/23.
//
#include "socket.h"
#include <functional>
#include <iostream>
#include <utility>
#include <websocketpp/common/thread.hpp>

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
std::chrono::high_resolution_clock::time_point m_tls_init;

context_ptr Socket::on_tls_init(const char *hostname, websocketpp::connection_hdl)
{
    m_tls_init = std::chrono::high_resolution_clock::now();
    context_ptr ctx = websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tls_client);

    try
    {
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                         boost::asio::ssl::context::no_sslv2 |
                         boost::asio::ssl::context::no_sslv3 |
                         boost::asio::ssl::context::single_dh_use);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return ctx;
}

void Socket::on_ws_message(client *ws_event_client, websocketpp::connection_hdl hdl, const message_ptr &msg)
{
    ws_event_client->get_alog().write(websocketpp::log::alevel::app, "on_ws_message handler: " + msg->get_payload());

    std::unique_ptr<Payload> p = std::make_unique<Payload>();
    p->client = ws_event_client;
    p->hdl = &hdl;
    p->data_string = msg->get_raw_payload();

    if (on_message_cb_trigger)
    {
        on_message_cb_trigger(std::move(p));
    }
}

void Socket::on_ws_open(client *ws_client, websocketpp::connection_hdl hdl)
{
    ws_client->get_alog().write(websocketpp::log::alevel::app, "Connection Opened");
    if (on_connection_open_cb_trigger)
    {
        on_connection_open_cb_trigger();
    }
}

void Socket::on_ws_fail(client *ws_client, websocketpp::connection_hdl hdl)
{
    ws_client->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
    if (on_connection_fail_cb_trigger)
    {
        on_connection_fail_cb_trigger();
    }
}

void Socket::on_ws_close(client *ws_client, websocketpp::connection_hdl hdl)
{
    ws_client->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
    if (on_connection_close_cb_trigger)
    {
        on_connection_close_cb_trigger();
    }
}

void Socket::send_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg)
{
    websocketpp::lib::error_code ec;

    ws_client->send(std::move(hdl), msg->get_payload(), msg->get_opcode(), ec);

    if (ec)
    {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}


void Socket::connect(const std::string &uri, const std::string &hostname)
{
    try
    {
        // Setup logging levels
        ws_client.clear_access_channels(websocketpp::log::alevel::all);
        ws_client.set_access_channels(websocketpp::log::alevel::app);
        ws_client.set_access_channels(websocketpp::log::alevel::connect);
        ws_client.set_access_channels(websocketpp::log::alevel::disconnect);
        ws_client.set_access_channels(websocketpp::log::alevel::control);

        // Initialize asio
        ws_client.init_asio();

        // Setup handlers using lambdas
        ws_client.set_open_handler([this, client = &ws_client](auto &&hdl) {
            this->on_ws_open(client, std::forward<decltype(hdl)>(hdl));
        });
        ws_client.set_close_handler([this, client = &ws_client](auto &&hdl) {
            on_ws_close(client, std::forward<decltype(hdl)>(hdl));
        });
        ws_client.set_fail_handler([this, client = &ws_client](auto &&hdl) {
            on_ws_fail(client, std::forward<decltype(hdl)>(hdl));
        });
        ws_client.set_tls_init_handler([this, client = hostname.c_str()](auto &&hostname) {
            return on_tls_init(client, std::forward<decltype(hostname)>(hostname));
        });
        ws_client.set_message_handler([this, client = &ws_client](auto &&hdl, auto &&msg) {
            on_ws_message(client, std::forward<decltype(hdl)>(hdl), std::forward<decltype(msg)>(msg));
        });

        websocketpp::lib::error_code ec;
        client::connection_ptr con = ws_client.get_connection(uri, ec);

        if (ec)
        {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
        }
        // Note that connect here only requests a connection. No network messages are
        // exchanged until the event loop starts running in the next line.
        ws_client.connect(con);

        // Start the ASIO io_service run loop
        // this will cause a single connection to be made to the server. c.run()
        // will exit when this connection is closed.
        ws_client.run();
    }
    catch (websocketpp::exception const &e)
    {
        std::cout << e.what() << std::endl;
    }
}

client *Socket::get_client()
{
    return &(this->ws_client);
}
