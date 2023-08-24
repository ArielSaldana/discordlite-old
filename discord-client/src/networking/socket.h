//
// Created by Ariel Saldana on 8/20/23.
//

#ifndef DISCORDLITE_SOCKET_H
#define DISCORDLITE_SOCKET_H


//#include "gateway_event_processor.h"
#include <iostream>
#include <string>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

class Socket {

private:
    client ws_client;
    context_ptr on_tls_init(const char *hostname, websocketpp::connection_hdl);
    void on_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg);
    void send_message(client *ws_client, websocketpp::connection_hdl hdl, message_ptr msg);

public:
    void
    connect(const std::string &uri, const std::string &hostname);

    //    GatewayEventProcessor gateway_event_processor;
};

#endif//DISCORDLITE_SOCKET_H
