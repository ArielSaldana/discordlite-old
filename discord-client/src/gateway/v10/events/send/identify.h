//
// Created by Ariel Saldana on 8/19/23.
//

#ifndef DISCORDLITE_IDENTIFY_H
#define DISCORDLITE_IDENTIFY_H

#include <iostream>
#include <string>
#include "../serializable.h"

struct Identify: public Serializable {
    std::string os;
    std::string browser;
    std::string device;

    rapidjson::Value serialize(rapidjson::Document::AllocatorType& allocator) const override {
        rapidjson::Value obj(rapidjson::kObjectType);

        obj.AddMember("os", rapidjson::Value(os.c_str(), allocator), allocator);
        obj.AddMember("browser", rapidjson::Value(browser.c_str(), allocator), allocator);
        obj.AddMember("device", rapidjson::Value(device.c_str(), allocator), allocator);

        return obj;
    }
};

#endif //DISCORDLITE_IDENTIFY_H
