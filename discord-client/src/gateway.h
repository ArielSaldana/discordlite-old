//
// Created by Ariel Saldana on 8/27/23.
//

#ifndef DISCORDLITE_GATEWAY_H
#define DISCORDLITE_GATEWAY_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <iostream>
#include <string>
#include <utility>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

class Gateway
{
    std::pair<int, rapidjson::Document> peek_opcode(const std::string &payload_json);
    void process_event(client *ws_client, websocketpp::connection_hdl hdl, const std::string &payload);
    void handle_gateway_message();
};


#endif//DISCORDLITE_GATEWAY_H
