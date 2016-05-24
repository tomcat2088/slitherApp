//
//  SlitherRender.cpp
//  slitherApp
//
//  Created by ocean on 5/13/16.
//
//

#include "SlitherRender.hpp"
#include "Slither.hpp"
#include "Vector2.hpp"

#include "SlitherRenderUnit.hpp"

using namespace cocos2d;

SlitherRender::SlitherRender(Slither* slither)
{
    _slither = slither;
}

SlitherRender::~SlitherRender()
{
    detach();
}

void SlitherRender::syncNodes()
{
    //if(_nodes.size() != _slither->points.size())
    {
        for(int i=(int)_slither->points.size() - 1;i >= 0;i--)
        {
            Vector2 pos = _slither->points[i];
            SlitherRenderUnit* node = NULL;
            if(i >= 0 && i < _nodes.size())
            {
                node = dynamic_cast<SlitherRenderUnit*>(_nodes.at(i));
            }
            else
            {
                node = dynamic_cast<SlitherRenderUnit*>(SlitherRenderUnit::create());
                node->setContentSize(cocos2d::Size(_slither->width,_slither->width));
                node->setPosition(Vec2(pos.x, pos.y));
                _nodes.insert(0, node);
            }
            
            if(node->getParent() == NULL && _attachedLayer)
            {
                _attachedLayer->addChild(node);
            }
            node->moveTo(Vec2(pos.x, pos.y),_slither->updateInterval);
        }
    }
}

void SlitherRender::update(double deltaTime)
{
    for(int i= 0;i < _nodes.size();i++)
    {
        SlitherRenderUnit* node = dynamic_cast<SlitherRenderUnit*>(_nodes.at(i));
        node->update(deltaTime);
        
        if(i < _nodes.size() - 1)
        {
            Vec2 pt1 = _nodes.at(i + 1)->getPosition();
            Vec2 pt2 = _nodes.at(i)->getPosition();
            Vector2 direciton = Vector2(pt1.x,pt1.y).sub(Vector2(pt2.x,pt2.y));
            node->setRotation(Vector2::directionToDegree(direciton));
        }
        _nodes.at(_nodes.size() - 1)->setRotation(Vector2::directionToDegree(_slither->direction));
    }
}

void SlitherRender::attachTo(cocos2d::Layer* layer)
{
    if(_isAttached)
        return;
    _isAttached = true;
    _attachedLayer = layer;
}

cocos2d::Node* SlitherRender::headNode()
{
    if(_nodes.size() >= 1)
        return _nodes.at(_nodes.size() - 1);
    return NULL;
}

void SlitherRender::detach()
{
    if(_isAttached == false)
        return;
     _isAttached = false;
    _attachedLayer = NULL;
}