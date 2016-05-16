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
            SlitherRenderUnit* node = NULL;
            if(i >= 0 && i < _nodes.size())
            {
                node = dynamic_cast<SlitherRenderUnit*>(_nodes.at(i));
            }
            else
            {
                node = dynamic_cast<SlitherRenderUnit*>(SlitherRenderUnit::create());
                _nodes.insert(0, node);
            }
            
            if(node->getParent() == NULL && _attachedLayer)
            {
                _attachedLayer->addChild(node);
            }
            
            Vector2 pos = _slither->points[i];
            node->moveTo(Vec2(pos.x, pos.y),_slither->updateInterval);
        }
    }
}

void SlitherRender::update(double deltaTime)
{
    for(int i=0;i<_nodes.size();i++)
    {
        SlitherRenderUnit* node = dynamic_cast<SlitherRenderUnit*>(_nodes.at(i));
        node->update(deltaTime);
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