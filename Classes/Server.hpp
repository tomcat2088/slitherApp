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
    ServerCommandSync = 10001,
    ServerCommandMessage = 10002,
    ServerCommandLogout = 10003,
    ServerCommandMap = 10004,
    ServerCommandCatchProp = 10005,
} ServerCommand;

struct User {
    std::string uid;
    std::string nickname;
};


class Server
{
public:
    std::function<void(ServerCommand,nlohmann::json)> commandCallBack;
    bool avaliable;
    easywsclient::WebSocket::pointer websocket;
    User* loginUser;
    
    Server();
    void login();
    void sendCommand(ServerCommand command, nlohmann::json data);
    
private:
    std::thread loopThread[1];
    void loop();
    void processResponse(nlohmann::json obj);
};
#endif /* Server_hpp */
