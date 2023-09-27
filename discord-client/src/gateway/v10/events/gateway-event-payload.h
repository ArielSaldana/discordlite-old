//
// Created by Ariel Saldana on 9/5/23.
//

#ifndef DISCORDLITE_GATEWAY_EVENT_PAYLOAD_H
#define DISCORDLITE_GATEWAY_EVENT_PAYLOAD_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "receive/hello.h"
#include <iostream>
#include <optional>
#include <string>

template<typename T>
struct GatewayEventPayload
{
    int op;
    std::optional<T> d;
    std::optional<int> s;
    std::optional<std::string> t;

    GatewayEventPayload()
    {
    }

    explicit GatewayEventPayload(const rapidjson::Document &json_doc)
    {
        op = json_doc["op"].GetInt();

        if (json_doc.HasMember("d") && json_doc["d"].IsObject())
        {
            d = T(json_doc["d"].GetObject());
        }

        if (json_doc.HasMember("s") && json_doc["s"].IsInt())
        {
            s = json_doc["s"].GetInt();// Assigning the value of 'd'
        }

        if (json_doc.HasMember("t") && json_doc["t"].IsString())
        {
            t = json_doc["t"].GetString();// Assigning the value of 'd'
        }
    }
};

#endif//DISCORDLITE_GATEWAY_EVENT_PAYLOAD_H
