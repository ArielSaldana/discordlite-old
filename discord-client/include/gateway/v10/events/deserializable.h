//
// Created by Ariel Saldana on 8/19/23.
//

#ifndef DISCORDLITE_DESERIALIZABLE_H
#define DISCORDLITE_DESERIALIZABLE_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

template <typename T>
class Deserializable {
public:
    virtual T deserialize(const rapidjson::Value& json) = 0;
};


#endif //DISCORDLITE_DESERIALIZABLE_H
