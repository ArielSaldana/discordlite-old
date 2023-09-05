#include "../include/client.h"
#include "networking/payload.h"
#include "networking/socket.h"
#include <iostream>
#include <string>

void DiscordLiteClient::start()
{
    std::string uri = "wss://gateway.discord.gg/?v=10&encoding=json";
    std::string hostname = "gateway.discord.gg";

    Socket websocket;

    websocket.on_connection_open([] {
        std::cout << "CONNECTION!!" << std::endl;
    });

    websocket.on_connection_close([] {
        std::cout << "CONNECTION CLOSED!!" << std::endl;
    });

    websocket.on_message([](std::unique_ptr<Payload> p) {
        std::cout << "GOT A MESSAGE!! Data: " << p->data_string << std::endl;
    });

    websocket.connect(uri, hostname);
}
