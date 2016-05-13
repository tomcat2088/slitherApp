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
    GameSession();
    ~GameSession();
    Slither* slither;
    std::vector<Slither*> otherSlithers;
    
    void update(double deltaTime);
private:
    Server* server;
    void processServerResponse(ServerCommand command,nlohmann::json obj);
};
#endif /* GameSession_hpp */
