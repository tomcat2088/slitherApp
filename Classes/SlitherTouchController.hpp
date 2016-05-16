//
//  SlitherTouchController.hpp
//  slitherApp
//
//  Created by ocean on 5/16/16.
//
//

#ifndef SlitherTouchController_hpp
#define SlitherTouchController_hpp

#include <stdio.h>
#include "Vector2.hpp"

class SlitherTouchController
{
public:
    Vector2 direction;
    void touchBegin(cocos2d::Vec2 point);
    void touchMove(cocos2d::Vec2 point);
    void touchEnd(cocos2d::Vec2 point);
    
private:
    cocos2d::Vec2 _beginTouchPoint;
};
#endif /* SlitherTouchController_hpp */
