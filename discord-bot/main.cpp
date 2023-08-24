//
// Created by Ariel Saldana on 8/19/23.
//
#include "client.h"
//#include "gateway/v10/events/receive/hello.h"
//#include "gateway/v10/events/send/identify.h"
#include <iostream>

int main()
{
    DiscordLiteClient::connect();
    //    Identify identify;
    //    identify.browser = "Arc";
    //    identify.device = "MBP";
    //    identify.os = "MacOS";
    //
    //    std::cout << identify.toJsonString() << std::endl;
    //
    //    std::cout << "Hello, World from Bot" << std::endl;
    //    hello();
}
