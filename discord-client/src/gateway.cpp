//
// Created by Ariel Saldana on 8/27/23.
//

#include "gateway.h"
#include "gateway/v10/events/gateway-event-payload.h"
#include "gateway/v10/events/models/activity.h"
#include "gateway/v10/events/models/presence.h"
#include "gateway/v10/events/models/properties.h"
#include "gateway/v10/events/receive/hello.h"
#include "gateway/v10/events/send/identify.h"
#include "heartbeat.h"

std::pair<int, rapidjson::Document> Gateway::peek_opcode(const std::string &payload_json)
{
    rapidjson::Document json_doc;
    json_doc.Parse(payload_json.c_str());
    rapidjson::Value &op_code = json_doc["op"];
    return std::make_pair(op_code.GetInt(), std::move(json_doc));
}

void Gateway::process_event(client *ws_client, const websocketpp::connection_hdl &hdl, const std::string &payload)
{
    auto event_context = peek_opcode(payload);
    auto op_code = event_context.first;
    rapidjson::Document json_document = std::move(event_context.second);

    // Hello Gateway Event
    if (op_code == 10)
    {
        auto gatewayEventPayload = new GatewayEventPayload<HelloGatewayEvent>(json_document);
        auto helloGatewayEvent = gatewayEventPayload->d.value();

        boost::asio::io_context io_context;


        // send identify
        auto properties = Properties();
        properties.os = "MacOS";
        properties.device = "Bot";
        properties.browser = "Bot";

        auto activity = Activity();
        auto presence = Presence();
        auto identify = Identify();

        identify.token = "MTE1NjQyMDQ3MTAxMzc3NzU4MA.G-X3Cl.IhnMR7NGKv-rsrYAaiNPa8ZVlI8bfU9T-HS7Tk";
        identify.properties = properties;
        identify.large_threshold = 250;
        //        identify.intents = 7;

        //        gatewayEventPayload()
        auto identifyEvent = GatewayEventPayload<Identify>();
        identifyEvent.op = 2;
        identifyEvent.d = identify;

        rapidjson::Document doc;
        doc.SetObject();

        rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

        doc.AddMember("op", rapidjson::Value(2), allocator);
        doc.AddMember("t", rapidjson::Value().SetNull(), allocator);
        doc.AddMember("s", rapidjson::Value().SetNull(), allocator);
        doc.AddMember("d", identify.serialize(allocator), allocator);

        //        rapidjson::Document::AllocatorType alloc;

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        try
        {
            websocketpp::lib::error_code ec;
            //            ws_client->send(hdl, identify.toJsonString(), websocketpp::frame::opcode::text, ec);
            //            ws_client->send(hdl, identifyEvent.jsonString(), websocketpp::frame::opcode::text, ec);
            ws_client->send(hdl, buffer.GetString(), websocketpp::frame::opcode::text, ec);

            // start heart beat
            //            io_context.run();


            //            std::thread io_thread([&io_context, &ws_client, &hdl, &helloGatewayEvent]() {
            //                auto heartbeat = Heartbeat(ws_client, hdl, helloGatewayEvent, io_context);
            //                //                io_context.run();
            //            });


            auto heartbeat = Heartbeat(ws_client, hdl, helloGatewayEvent, io_context);
            //            io_context.run();


            std::thread io_thread([&io_context, &ws_client, &hdl, helloGatewayEvent, &heartbeat]() {
                try
                {
                    io_context.run();

                    //                    auto heartbeat = Heartbeat(ws_client, hdl, helloGatewayEvent, io_context);

                    //                    std::cout << helloGatewayEvent.heartbeat_interval << std::endl;
                    //                    std::cout << "Thread running" << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Exception in thread: " << e.what() << std::endl;
                }
                catch (...)
                {
                    std::cerr << "Unknown exception in thread!" << std::endl;
                }
            });


            io_thread.detach();

            //std::cout << helloGatewayEvent.heartbeat_interval << std::endl;


            if (ec)
            {
                std::cout << "Send Error: " << ec.message() << std::endl;
            }
            else
            {
                //                std::cout << "Successfully sent identify: " << buffer.GetString() << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
}

void Gateway::handle_gateway_message()
{
}
