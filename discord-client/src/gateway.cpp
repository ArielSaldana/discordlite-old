//
// Created by Ariel Saldana on 8/27/23.
//

#include "gateway.h"

std::pair<int, rapidjson::Document> Gateway::peek_opcode(const std::string &payload_json)
{
    rapidjson::Document json_doc;
    json_doc.Parse(payload_json.c_str());
    rapidjson::Value &op_code = json_doc["op"];
    return std::make_pair(op_code.GetInt(), std::move(json_doc));
}

void Gateway::process_event(client *ws_client, websocketpp::connection_hdl hdl, const std::string &payload)
{
    auto event_context = peek_opcode(payload);
    auto op_code = event_context.first;
    rapidjson::Document json_document = std::move(event_context.second);

    std::cout << "ATTEMPTING TO PROCESS EVENT" << std::endl;
    std::cout << op_code << std::endl;

    if (op_code == 10)
    {
        //        Payload::deserialize(json_document);
    }
    else
    {
    }
}

void Gateway::handle_gateway_message()
{
}
