//
//  SlitherTouchController.cpp
//  slitherApp
//
//  Created by ocean on 5/16/16.
//
//

#include "SlitherTouchController.hpp"
void SlitherTouchController::touchBegin(cocos2d::Vec2 point)
{
    _beginTouchPoint = point;
    rotateDirection = 0;
}

void SlitherTouchController::touchMove(cocos2d::Vec2 point)
{
    if(point.x < _beginTouchPoint.x)
        rotateDirection = 1;
    else if(point.x > _beginTouchPoint.x)
      rotateDirection = -1;
    else
        rotateDirection = 0;
}

void SlitherTouchController::touchEnd(cocos2d::Vec2 point)
{
    rotateDirection = 0;
}