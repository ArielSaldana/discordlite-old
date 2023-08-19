//
// Created by Ariel Saldana on 8/19/23.
//
#include <iostream>
#include "library.h"
#include "gateway/v10/events/receive/hello.h"
#include "gateway/v10/events/send/identify.h"

int main() {
    Identify identify;
    identify.browser = "Arc";
    identify.device = "MBP";
    identify.os = "MacOS";

    std::cout << identify.toJsonString() << std::endl;

    std::cout << "Hello, World from Bot" << std::endl;
    hello();
}