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
#include "LocalServer.hpp"
#include "json.hpp"

class GameSession
{
public:
    GameSession(cocos2d::Layer* gameLayer,cocos2d::Camera* camera);
    ~GameSession();
    Slither* slither;
    std::vector<Slither*> otherSlithers;
    
    void update(double deltaTime);
private:
    LocalServer* server;
    cocos2d::Layer* _gameLayer;
    cocos2d::Camera* _camera;
    void processServerResponse(ServerCommand command,nlohmann::json obj);
};
#endif /* GameSession_hpp */
