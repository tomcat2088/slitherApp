//
//  Slither.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#ifndef Slither_hpp
#define Slither_hpp

#include "Vector2.hpp"
#include "json.hpp"

class SlitherRender;
class Slither
{
public:
    std::string nickname;
    std::string uid;
    double length;
    double width;
    std::vector<Vector2> points;
    double speed;
    Vector2 direction;
    
    int rotateDirection;
    
    double updateInterval;
    
    Slither();
    
    nlohmann::json serialize();
    void deserialize(nlohmann::json obj);
    
    void update(double deltaTime);
    Slither* dieTest(Slither* slither);
    SlitherRender* render(cocos2d::Layer* layer);
    
    cocos2d::Vec2 headPosition();
    
private:
    double _updateTime;
    SlitherRender* _render;
    double updateHead(double deltaTime);
    Vector2 head();
    void updateTail(double deltaTime,double forwardDistance);
};
#endif /* Slither_hpp */
