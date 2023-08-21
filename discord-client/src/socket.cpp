//
// Created by Ariel Saldana on 8/20/23.
//
#include "networking/socket.h"
#include <functional>
#include <iostream>
#include <utility>
#include <websocketpp/common/thread.hpp>


using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
std::chrono::high_resolution_clock::time_point m_tls_init;

context_ptr Socket::on_tls_init(const char *hostname, websocketpp::connection_hdl) {
    m_tls_init = std::chrono::high_resolution_clock::now();
    context_ptr ctx = websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tls_client);

    try {
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                         boost::asio::ssl::context::no_sslv2 |
                         boost::asio::ssl::context::no_sslv3 |
                         boost::asio::ssl::context::single_dh_use);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return ctx;
}
void Socket::on_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;

//        HelloEvent hello;
//        hello.
//        GatewayEventProcessor::process_event(msg->get_payload());
    gateway_event_processor.process_event(ws_client, hdl, msg->get_payload());
    //    websocketpp::lib::error_code ec;

    //    ws_client->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
    //    if (ec) {
    //        std::cout << "Echo failed because: " << ec.message() << std::endl;
    //    }
}

void Socket::send_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg) {
    websocketpp::lib::error_code ec;

    ws_client->send(std::move(hdl), msg->get_payload(), msg->get_opcode(), ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}


void Socket::connect() {
    std::cout << " attempting to make a connection" << std::endl;

    std::string uri = "wss://gateway.discord.gg/?v=10&encoding=json";
    std::string hostname = "gateway.discord.gg";
    client ws_client;

    try {
        ws_client.set_access_channels(websocketpp::log::alevel::all);
        ws_client.clear_access_channels(websocketpp::log::alevel::frame_payload);
        ws_client.init_asio();
        //        ws_client.set_message_handler(bind(&on_message, &ws_client, ::_1, ::_2));
        ws_client.set_message_handler(std::bind(&Socket::on_message, this, &ws_client, std::placeholders::_1, std::placeholders::_2));
        ws_client.set_tls_init_handler(std::bind(&Socket::on_tls_init, this, hostname.c_str(), ::_1));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = ws_client.get_connection(uri, ec);

        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            //            return 0;
        }
        // Note that connect here only requests a connection. No network messages are
        // exchanged until the event loop starts running in the next line.
        ws_client.connect(con);

        // Start the ASIO io_service run loop
        // this will cause a single connection to be made to the server. c.run()
        // will exit when this connection is closed.
        ws_client.run();

    } catch (websocketpp::exception const &e) {
        std::cout << e.what() << std::endl;
    }
}
