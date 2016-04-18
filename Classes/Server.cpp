//
//  Server.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "Server.hpp"

using namespace nlohmann;

Server::Server():websocket(NULL),loginUser(NULL)
{

}

void Server::login()
{
    if(websocket != NULL)
        return;
    websocket = easywsclient::WebSocket::from_url("ws://localhost:8765");
    
    std::thread websocketThread([this]{loop();});

}

void Server::loop()
{
    while (true) {
        websocket->poll();
        websocket->dispatch([](std::string& message){
            
        });
    }
}

void Server::sendCommand(ServerCommand command,json data)
{
    if(websocket == NULL)
        return;
    json result;
    if(command != ServerCommandLogin)
    {
        if(loginUser != NULL)
            result["uid"] = loginUser->uid;
        else
            return;
    }
    result["command"] = command;
    result["data"] = data;
    websocket->send(result.dump());
}