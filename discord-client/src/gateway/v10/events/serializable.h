//
// Created by Ariel Saldana on 8/19/23.
//

#ifndef DISCORDLITE_SERIALIZABLE_H
#define DISCORDLITE_SERIALIZABLE_H

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <string>

class Serializable
{
public:
    virtual rapidjson::Value serialize(rapidjson::Document::AllocatorType &allocator) const = 0;

    [[nodiscard]] std::string toJsonString() const
    {
        rapidjson::Document doc;// Use this document's allocator for serialization
        rapidjson::Value val = serialize(doc.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        val.Accept(writer);

        return {buffer.GetString()};
    }
};

#endif//DISCORDLITE_SERIALIZABLE_H
