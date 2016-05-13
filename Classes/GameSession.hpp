//
//  GameSession.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#ifndef GameSession_hpp
#define GameSession_hpp

#include "Slither.hpp"
#include "Server.hpp"
#include "json.hpp"

class GameSession
{
public:
    GameSession(cocos2d::Layer* gameLayer);
    ~GameSession();
    Slither* slither;
    std::vector<Slither*> otherSlithers;
    
    void update(double deltaTime);
private:
    Server* server;
    cocos2d::Layer* _gameLayer;
    void processServerResponse(ServerCommand command,nlohmann::json obj);
};
#endif /* GameSession_hpp */
