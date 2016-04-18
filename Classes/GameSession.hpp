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


class GameSession
{
public:
    
    Slither* slither;
    std::vector<Slither*> otherSlithers;
    
};
#endif /* GameSession_hpp */
