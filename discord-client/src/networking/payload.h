//
// Created by Ariel Saldana on 9/4/23.
//

#ifndef DISCORDLITE_PAYLOAD_H
#define DISCORDLITE_PAYLOAD_H

#include <iostream>
#include <string>
#include <websocketpp/client.hpp>
#include <websocketpp/common/connection_hdl.hpp>
#include <websocketpp/config/asio_client.hpp>

struct Payload
{
    websocketpp::client<websocketpp::config::asio_tls_client> *client;
    websocketpp::connection_hdl *hdl;
    std::string data_string;
};

#endif//DISCORDLITE_PAYLOAD_H
