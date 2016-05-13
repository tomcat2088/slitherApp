//
//  GameSession.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "GameSession.hpp"


using namespace nlohmann;
using namespace cocos2d;

GameSession::GameSession():slither(NULL)
{
    server = new Server();
    server->commandCallBack = [&](ServerCommand command,json obj){
        processServerResponse(command,obj);
    };
    server->login("ocean");
}

GameSession::~GameSession()
{
    if(server)
        delete server;
}

void GameSession::update(double deltaTime)
{
    if(slither)
    {
        slither->update(deltaTime);
    }
}

void GameSession::processServerResponse(ServerCommand command,nlohmann::json obj)
{
    if(command == ServerCommandLogin)
    {
        slither = new Slither();
        slither->deserialize(obj);
    }
}


