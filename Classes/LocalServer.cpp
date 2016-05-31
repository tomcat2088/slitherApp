//
//  LocalServer.cpp
//  slitherApp
//
//  Created by ocean on 5/31/16.
//
//

#include "LocalServer.hpp"
#include "Slither.hpp"
#include "Logger.hpp"

using namespace nlohmann;

LocalServer::LocalServer():
    _slither(NULL)
{
    
}

LocalServer::~LocalServer()
{
    
}

void LocalServer::login(std::string nickname)
{
    if(_slither == NULL)
    {
        _slither = new Slither();
        json data = _slither->serialize();
        data["uid"] = "222";
        data["nickname"] = nickname;
        this->commandCallBack(ServerCommandLogin,data);
    }
}

void LocalServer::loadMap()
{
    sendCommand(ServerCommandMap,std::string(""));
}

void LocalServer::syncSlither(Slither* slither)
{
    sendCommand(ServerCommandSyncSlither,slither->serialize());
}

void LocalServer::eatFood(std::string foodUid)
{
    sendCommand(ServerCommandEatFood, foodUid);
}

void LocalServer::kill(std::string targetUid)
{
    sendCommand(ServerCommandKill, targetUid);
}

void LocalServer::loop()
{
    while (true) {
        websocket->poll();
        websocket->dispatch([&](const std::string& message){
            json obj = json::parse(message);
            processResponse(obj);
        });
    }
}

void LocalServer::sendCommand(ServerCommand command,json data)
{
    if(websocket == NULL)
        return;
    json result;
    result["command"] = command;
    result["data"] = data;
    websocket->send(result.dump());
}

void LocalServer::sendCommand(ServerCommand command,std::string data)
{
    if(websocket == NULL)
        return;
    json result;
    result["command"] = command;
    result["data"] = data;
    websocket->send(result.dump());
}

void LocalServer::processResponse(json obj)
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