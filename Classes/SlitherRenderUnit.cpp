//
//  SlitherRenderUnit.cpp
//  slitherApp
//
//  Created by ocean on 5/13/16.
//
//

#include "SlitherRenderUnit.hpp"
#include "Vector2.hpp"

using namespace cocos2d;

bool SlitherRenderUnit::init()
{
    bool res =  this->cocos2d::Sprite::initWithFile("unit2.png");
    this->setAnchorPoint(Vec2(0.5, 0.5));
    return res;
}

void SlitherRenderUnit::moveTo(cocos2d::Vec2 pos,double duration)
{
    _oldPos = getPosition();
    _targetPos = pos;
    _duration = duration;
    _durationLeft = duration;
}

void SlitherRenderUnit::setOriginPosition(cocos2d::Vec2 pos)
{
    setPosition(pos);
    _oldPos = pos;
    _targetPos = pos;
    _duration = 0;
    _durationLeft = 0;
}

void SlitherRenderUnit::update(double deltaTime)
{
    _durationLeft -= deltaTime;
    if(_durationLeft <= 0)
    {
        setPosition(_targetPos);
    }
    else
    {
        double percent = 1 - _durationLeft / _duration;
        Vector2 vec(_targetPos.x,_targetPos.y);
        vec = vec.sub(Vector2(_oldPos.x,_oldPos.y));
        vec = vec.mul(percent).add(Vector2(_oldPos.x,_oldPos.y));
        setPosition(Vec2(vec.x, vec.y));
    }
}