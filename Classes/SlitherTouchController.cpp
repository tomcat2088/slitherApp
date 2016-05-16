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
    direction = Vector2(0,0);
}

void SlitherTouchController::touchMove(cocos2d::Vec2 point)
{
    direction = Vector2(point.x,point.y).sub(Vector2(_beginTouchPoint.x,_beginTouchPoint.y)).normalize();
    _beginTouchPoint = point;
}

void SlitherTouchController::touchEnd(cocos2d::Vec2 point)
{
    
}