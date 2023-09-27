//
// Created by Ariel Saldana on 9/5/23.
//

#ifndef DISCORDLITE_HEARTBEAT_H
#define DISCORDLITE_HEARTBEAT_H

#include "networking/payload.h"
#include <chrono>
#include <iostream>
#include <thread>

class Heartbeat
{
    bool should_send_heartbeat;
    HelloGatewayEvent helloGatewayEvent;
    client *ws_client;
    websocketpp::connection_hdl hdl;
    int heartbeat_count = 1;
    std::thread t1;

    boost::asio::io_context &io_context;// Assuming you have an io_context available
    boost::asio::steady_timer timer;

    void send_heartbeat()
    {
        rapidjson::Document d;
        d.SetObject();

        rapidjson::Document::AllocatorType &allocator = d.GetAllocator();

        d.AddMember("t", rapidjson::Value().SetNull(), allocator);
        d.AddMember("s", rapidjson::Value().SetNull(), allocator);
        d.AddMember("op", rapidjson::Value().SetInt(1), allocator);
        d.AddMember("d", rapidjson::Value().SetInt(heartbeat_count), allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);

        const char *jsonString = buffer.GetString();

        try
        {
            websocketpp::lib::error_code ec;
            ws_client->send(hdl, jsonString, websocketpp::frame::opcode::text, ec);

            if (ec)
            {
                std::cout << "Send Error: " << ec.message() << std::endl;
            }
            else
            {
                //                std::cout << "Successfully sent heartbeat: " << jsonString << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        heartbeat_count++;

        if (heartbeat_count == 1)
        {
            should_send_heartbeat = false;
        }
    }

public:
    void start_heartbeat()
    {

        if (should_send_heartbeat)
        {
            std::cout << "called" << std::endl;
            // When the timer expires, send the heartbeat.
            this->send_heartbeat();

            //            timer.expires_after(std::chrono::milliseconds(this->helloGatewayEvent.heartbeat_interval));
            timer.expires_after(std::chrono::milliseconds(1000));
            timer.async_wait([this](const boost::system::error_code &ec) {
                if (!ec)
                {

                    //                    // When the timer expires, send the heartbeat.
                    //                    this->send_heartbeat();


                    // Schedule the next heartbeat.
                    start_heartbeat();
                }
                else
                {

                    // Handle any errors, if needed
                    std::cout << "Timer error: " << ec.message() << std::endl;
                }
            });
        }
    }

    //explicit Heartbeat(client *ws_client, const websocketpp::connection_hdl &hdl, const HelloGatewayEvent &helloGatewayEvent)
    explicit Heartbeat(client *ws_client, const websocketpp::connection_hdl &hdl, const HelloGatewayEvent &helloGatewayEvent, boost::asio::io_context &io_context_)
        : io_context(io_context_), timer(io_context_)
    {
        this->ws_client = ws_client;
        this->hdl = hdl;
        this->helloGatewayEvent = helloGatewayEvent;
        this->should_send_heartbeat = true;

        start_heartbeat();


        //        t1 = std::thread([this] {
        //            while (should_send_heartbeat)
        //            {
        //                this->send_heartbeat();
        //                std::this_thread::sleep_for(std::chrono::milliseconds(this->helloGatewayEvent.heartbeat_interval));
        //            }
        //        });

        //        t1.detach();
    }
    ~Heartbeat()
    {
        if (t1.joinable())
        {
            t1.join();
        }
    }
};

#endif//DISCORDLITE_HEARTBEAT_H
