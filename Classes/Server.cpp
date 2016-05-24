//
//  Server.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "Server.hpp"
#include "Slither.hpp"
#include "Logger.hpp"

using namespace nlohmann;

Server::Server():websocket(NULL)
{

}

Server::~Server()
{
    if(websocket)
    {
        websocket->close();
    }
}

void Server::login(std::string nickname)
{
    if(websocket != NULL)
        return;
    websocket = easywsclient::WebSocket::from_url("ws://192.168.1.103:8081");
    
    if(websocket)
    {
        logInfo("Connected to Server.Begin login...");
        loopThread[0] = std::thread([this]{loop();});
        
        json loginData;
        loginData["nickname"] = nickname;
        sendCommand(ServerCommandLogin, loginData);
    }
}

void Server::loadMap()
{
    sendCommand(ServerCommandMap,std::string(""));
}

void Server::syncSlither(Slither* slither)
{
    sendCommand(ServerCommandSyncSlither,slither->serialize());
}

void Server::eatFood(std::string foodUid)
{
    sendCommand(ServerCommandEatFood, foodUid);
}

void Server::kill(std::string targetUid)
{
    sendCommand(ServerCommandKill, targetUid);
}

void Server::loop()
{
    while (true) {
        websocket->poll();
        websocket->dispatch([&](const std::string& message){
            json obj = json::parse(message);
            processResponse(obj);
        });
    }
}

void Server::sendCommand(ServerCommand command,json data)
{
    if(websocket == NULL)
        return;
    json result;
    result["command"] = command;
    result["data"] = data;
    websocket->send(result.dump());
}

void Server::sendCommand(ServerCommand command,std::string data)
{
    if(websocket == NULL)
        return;
    json result;
    result["command"] = command;
    result["data"] = data;
    websocket->send(result.dump());
}

void Server::processResponse(json obj)
{
    int code = obj["code"];
    if(code != 0)
    {
        return;
    }
    else
    {
        int command = obj["command"];
        if(commandCallBack)
            commandCallBack((ServerCommand)command,obj["data"]);
    }
}