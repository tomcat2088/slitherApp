//
//  Slither.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#ifndef Slither_hpp
#define Slither_hpp

#include "Vec2.hpp"
#include "json.hpp"

class Slither
{
public:
    std::string nickname;
    std::string uid;
    double length;
    double width;
    std::vector<Vec2> points;
    double speed;
    Vec2 direction;
    
    Slither();
    
    nlohmann::json serialize();
    void deserialize(std::string dataStr);
    
    void update(double deltaTime);
    Slither* dieTest(Slither* slither);
    
private:
    double _updateTime;
    double _updateInterval;
    double updateHead(double deltaTime);
    Vec2 head();
    void updateTail(double deltaTime,double forwardDistance);
};
#endif /* Slither_hpp */
