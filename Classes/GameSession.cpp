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

GameSession::GameSession(cocos2d::Layer* gameLayer,cocos2d::Camera* camera):slither(NULL)
{
    _gameLayer = gameLayer;
    _camera = camera;
    server = new LocalServer();
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
        cocos2d::Vec2 pos = slither->headPosition();
        _camera->setPosition(pos);
    }
}

void GameSession::processServerResponse(ServerCommand command,nlohmann::json obj)
{
    if(command == ServerCommandLogin)
    {
        slither = new Slither();
        slither->render(_gameLayer);
        slither->deserialize(obj);
    }
}


