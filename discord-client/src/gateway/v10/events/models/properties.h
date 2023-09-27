//
// Created by Ariel Saldana on 9/24/23.
//

#ifndef DISCORDLITE_PROPERTIES_H
#define DISCORDLITE_PROPERTIES_H

#include "../serializable.h"
#include <iostream>
#include <string>

struct Properties : Serializable
{
    std::string os;
    std::string browser;
    std::string device;

    rapidjson::Value serialize(rapidjson::Document::AllocatorType &allocator) const override
    {
        rapidjson::Value obj(rapidjson::kObjectType);

        obj.AddMember("os", rapidjson::Value(os.c_str(), allocator), allocator);
        obj.AddMember("browser", rapidjson::Value(browser.c_str(), allocator), allocator);
        obj.AddMember("device", rapidjson::Value(device.c_str(), allocator), allocator);

        return obj;
    }
};

#endif//DISCORDLITE_PROPERTIES_H
