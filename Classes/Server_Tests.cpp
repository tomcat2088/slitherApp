//
//  Server_Tests.cpp
//  slitherApp
//
//  Created by wangyang on 16/5/12.
//
//

#include "Server_Tests.hpp"
#include "Server.hpp"
#include "Logger.hpp"

ServerTests::ServerTests()
{
    Server* server = new Server();
    server->commandCallBack = [&](ServerCommand command,nlohmann::json data){
        logInfo(data.dump());
        if(command == ServerCommandLogin)
        {
            server->loadMap();
        }
        if(command == ServerCommandMap)
        {
            
        }
    };
    
    server->login("ocean");
}