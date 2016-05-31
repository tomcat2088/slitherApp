//
//  LocalServer.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#ifndef LocalServer_hpp
#define LocalServer_hpp

#include "easywsclient.hpp"
#include "json.hpp"
#include "ServerCommands.h"

class Slither;

class LocalServer
{
public:
    std::function<void(ServerCommand,nlohmann::json)> commandCallBack;
    bool avaliable;
    easywsclient::WebSocket::pointer websocket;
    
    LocalServer();
    ~LocalServer();
    void close();
    void login(std::string nickname);
    void loadMap();
    void syncSlither(Slither* slither);
    void eatFood(std::string foodUid);
    void kill(std::string targetUid);
    
private:
    Slither* _slither;
    std::thread loopThread[1];
    void loop();
    void processResponse(nlohmann::json obj);
    void sendCommand(ServerCommand command, nlohmann::json data);
    void sendCommand(ServerCommand command,std::string data);
};
#endif /* LocalServer_hpp */
