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
            Node* node = NULL;
            if(i >= 0 && i < _nodes.size())
            {
                node = _nodes.at(i);
            }
            else
            {
                node = LayerColor::create(Color4B(255, 0, 0, 255), _slither->width/2, _slither->width/2);
                _nodes.insert(0, node);
            }
            
            if(node->getParent() == NULL && _attachedLayer)
            {
                _attachedLayer->addChild(node);
            }
            
            Vector2 pos = _slither->points[i];
            node->setPosition(Vec2(pos.x, pos.y));
        }
    }
}

void SlitherRender::update(double deltaTime)
{
    syncNodes();
}

void SlitherRender::attachTo(cocos2d::Layer* layer)
{
    if(_isAttached)
        return;
    _isAttached = true;
    _attachedLayer = layer;
}

void SlitherRender::detach()
{
    if(_isAttached == false)
        return;
     _isAttached = false;
    _attachedLayer = NULL;
}