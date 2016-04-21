//
//  GameSession.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "GameSession.hpp"


using namespace nlohmann;
GameSession::GameSession()
{
    server = new Server();
    server->commandCallBack = [&](ServerCommand command,json obj){
        
    };
}

void GameSession::processServerResponse(ServerCommand command,nlohmann::json obj)
{
    if(command == ServerCommandMap)
    {
        
    }
}


