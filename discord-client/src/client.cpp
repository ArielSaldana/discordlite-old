#include "../include/client.h"
#include "networking/socket.h"
#include <iostream>
#include <string>

void DiscordLiteClient::start()
{
    std::string uri = "wss://gateway.discord.gg/?v=10&encoding=json";
    std::string hostname = "gateway.discord.gg";

    Socket websocket;
    websocket.connect(uri, hostname);

    std::cout << "Connect called" << std::endl;
}
