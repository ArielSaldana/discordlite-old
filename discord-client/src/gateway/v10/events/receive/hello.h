//
// Created by Ariel Saldana on 8/19/23.
//

#ifndef DISCORDLITE_HELLO_H
#define DISCORDLITE_HELLO_H

//#include "payload-data.h"
#include "../deserializable.h"
#include "../payload-data.h"

struct Hello : public Deserializable<Hello> {
    int heartbeat_interval{};
};

struct HelloGatewayEvent : public PayloadData, Deserializable<HelloGatewayEvent> {
    int heartbeat_interval{};

    HelloGatewayEvent() = default;
    explicit HelloGatewayEvent(const rapidjson::Value &json)
    {
        init(json);
    }

    void init(const rapidjson::Value &json)
    {
        deserialize(json);
    }

    HelloGatewayEvent deserialize(const rapidjson::Value &json) override
    {
        HelloGatewayEvent hello_gateway_event;
        if (json.HasMember("heartbeat_interval") && json["heartbeat_interval"].IsInt())
        {
            //            event_data.heartbeat_interval = json["heartbeat_interval"].GetInt();
            heartbeat_interval = json["heartbeat_interval"].GetInt();
        }
        return hello_gateway_event;
    }
};

#endif//DISCORDLITE_HELLO_H
