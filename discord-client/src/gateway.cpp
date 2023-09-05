//
// Created by Ariel Saldana on 8/27/23.
//

#include "gateway.h"
#include "gateway/v10/events/gateway-event-payload.h"
#include "gateway/v10/events/receive/hello.h"


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
        auto gep = new GatewayEventPayload<HelloGatewayEvent>(json_document);
        std::cout << gep->d->heartbeat_interval << std::endl;
    }
}

void Gateway::handle_gateway_message()
{
}
