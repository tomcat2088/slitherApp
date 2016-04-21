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
    
    if(websocket)
    {
        loopThread[0] = std::thread([this]{loop();});
        
        json loginData;
        loginData["nickname"] = "ocean";
        sendCommand(ServerCommandLogin, loginData);
    }

}

void Server::loop()
{
    while (true) {
        websocket->poll();
        websocket->dispatch([&](const std::string& message){
            json obj = json::parse(message);
            if((ServerCommand)obj["command"] == ServerCommandLogin)
            {
                if(loginUser != NULL)
                    delete loginUser;
                loginUser = new User();
                loginUser->nickname = obj["data"]["nickname"];
                loginUser->uid = obj["data"]["uid"];
            }
            processResponse(obj);
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
            commandCallBack((ServerCommand)command,obj);
    }
}