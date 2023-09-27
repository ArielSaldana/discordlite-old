//
// Created by Ariel Saldana on 8/19/23.
//

#ifndef DISCORDLITE_IDENTIFY_H
#define DISCORDLITE_IDENTIFY_H

#include "../models/presence.h"
#include "../models/properties.h"
#include "../serializable.h"
#include <iostream>
#include <list>
#include <string>

struct Identify : public Serializable
{
    std::string token;
    Properties properties;
    bool compress;
    uint32_t large_threshold;
    std::list<uint16_t> shard;
    Presence presence;
    uint16_t intents;

    //    std::string serialize() const override
    //    {
    //        rapidjson::Document doc;// Create a new document
    //        auto &allocator = doc.GetAllocator();
    //
    //        rapidjson::Value obj(rapidjson::kObjectType);
    //
    //        obj.AddMember("token", rapidjson::Value(token.c_str(), allocator), allocator);
    //        obj.AddMember("properties", properties.serialize(allocator), allocator);// Assuming Properties has an allocator-based serialize method
    //        obj.AddMember("compress", compress, allocator);
    //        obj.AddMember("large_threshold", large_threshold, allocator);
    //
    //        rapidjson::Value shardArray(rapidjson::kArrayType);
    //        for (auto &s: shard)
    //        {
    //            shardArray.PushBack(s, allocator);
    //        }
    //        obj.AddMember("shard", shardArray, allocator);
    //
    //        obj.AddMember("presence", presence.serialize(allocator), allocator);// Assuming Presence has an allocator-based serialize method
    //        obj.AddMember("intents", intents, allocator);
    //
    //        // Convert the Value to a string
    //        rapidjson::StringBuffer buffer;
    //        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    //        obj.Accept(writer);
    //
    //        return buffer.GetString();
    //    }

    rapidjson::Value serialize(rapidjson::Document::AllocatorType &allocator) const override
    {
        rapidjson::Value obj(rapidjson::kObjectType);

        obj.AddMember("token", rapidjson::Value(token.c_str(), allocator), allocator);
        obj.AddMember("properties", properties.serialize(allocator), allocator);
        obj.AddMember("compress", compress, allocator);
        obj.AddMember("large_threshold", large_threshold, allocator);

        rapidjson::Value shardArray(rapidjson::kArrayType);
        for (auto &s: shard)
        {
            shardArray.PushBack(s, allocator);
        }
        if (!shard.empty())
        {
            obj.AddMember("shard", shardArray, allocator);
        }

        obj.AddMember("presence", presence.serialize(allocator), allocator);// Assuming Presence has a serialize method
        obj.AddMember("intents", intents, allocator);

        return obj;
    }
};

#endif//DISCORDLITE_IDENTIFY_H
