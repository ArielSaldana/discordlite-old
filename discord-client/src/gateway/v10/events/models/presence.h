//
// Created by Ariel Saldana on 9/24/23.
//

#ifndef DISCORDLITE_PRESENCE_H
#define DISCORDLITE_PRESENCE_H

#include "../serializable.h"
#include <iostream>
#include <string>

struct Presence : Serializable
{
    std::string status;
    uint32_t since;
    bool afk;

    rapidjson::Value serialize(rapidjson::Document::AllocatorType &allocator) const
    {
        rapidjson::Value obj(rapidjson::kObjectType);

        obj.AddMember("status", rapidjson::Value(status.c_str(), allocator), allocator);
        obj.AddMember("since", since, allocator);
        obj.AddMember("afk", afk, allocator);

        return obj;
    }
};

#endif//DISCORDLITE_PRESENCE_H
