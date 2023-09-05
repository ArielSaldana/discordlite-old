//
// Created by Ariel Saldana on 8/20/23.
//

#ifndef DISCORDLITE_SOCKET_H
#define DISCORDLITE_SOCKET_H


//#include "gateway_event_processor.h"
#include "payload.h"
#include <iostream>
#include <string>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

class Socket
{

private:
    client ws_client;
    std::function<void()> on_connection_open_cb_trigger = nullptr;
    std::function<void()> on_connection_close_cb_trigger = nullptr;
    std::function<void()> on_connection_fail_cb_trigger = nullptr;
    std::function<void(std::unique_ptr<Payload>)> on_message_cb_trigger = nullptr;

    context_ptr on_tls_init(const char *hostname, websocketpp::connection_hdl);

    void on_ws_message(client *ws_client, websocketpp::connection_hdl hdl, const message_ptr &msg);
    void on_ws_open(client *ws_client, websocketpp::connection_hdl hdl);
    void on_ws_close(client *ws_client, websocketpp::connection_hdl hdl);
    void on_ws_fail(client *ws_client, websocketpp::connection_hdl hdl);
    void send_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg);

public:
    client *get_client();
    void connect(const std::string &uri, const std::string &hostname);

    template<typename Callable>
    void on_connection_open(Callable callback)
    {
        this->on_connection_open_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_connection_close(Callable callback)
    {
        this->on_connection_close_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_connection_fail(Callable callback)
    {
        this->on_connection_fail_cb_trigger = std::move(callback);
    }

    template<typename Callable>
    void on_message(Callable &&callback)
    {
        this->on_message_cb_trigger = std::forward<Callable>(callback);
    }
};

#endif//DISCORDLITE_SOCKET_H
