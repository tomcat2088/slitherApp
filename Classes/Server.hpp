//
//  Server.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#ifndef Server_hpp
#define Server_hpp

#include "easywsclient.hpp"
#include "json.hpp"

typedef enum {
    ServerCommandLogin = 10000,
    ServerCommandSyncSlither = 10001,
    ServerCommandMap = 10002,
    ServerCommandKill = 10003,
    ServerCommandEatFood = 10004,
    ServerCommandLogout = 10005,
} ServerCommand;

struct User {
    std::string uid;
    std::string nickname;
};

class Slither;

class Server
{
public:
    std::function<void(ServerCommand,nlohmann::json)> commandCallBack;
    bool avaliable;
    easywsclient::WebSocket::pointer websocket;
    
    Server();
    void login(std::string nickname);
    void loadMap();
    void syncSlither(Slither* slither);
    void eatFood(std::string foodUid);
    void kill(std::string targetUid);
    
private:
    std::thread loopThread[1];
    void loop();
    void processResponse(nlohmann::json obj);
    void sendCommand(ServerCommand command, nlohmann::json data);
    void sendCommand(ServerCommand command,std::string data);
};
#endif /* Server_hpp */
