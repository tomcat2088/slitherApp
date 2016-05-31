//
//  Slither.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "Slither.hpp"
#include "json.hpp"
#include "SlitherRender.hpp"

using namespace nlohmann;

Slither::Slither():length(3),
width(30),
direction(Vector2(0,1)),
_updateTime(0),
updateInterval(0),
speed(30),
_render(NULL),
rotateDirection(0)
{
    for(int i=length - 1; i>= 0 ;i--)
    {
        points.push_back(Vector2(0, 0 - i * width));
    }
}

json Slither::serialize()
{
    json obj;
    obj["length"] = length;
    obj["width"] = width;
    json pointsJson;
    for(int i=0;i<points.size();i++)
    {
        json pointJson;
        pointJson["x"] = points[i].x;
        pointJson["y"] = points[i].y;
        pointsJson.push_back(pointJson);
    }
    obj["points"] = pointsJson;
    return obj;
}

void Slither::deserialize(json obj)
{
    length = obj["length"];
    width = obj["width"];
    uid = obj["uid"];
    nickname = obj["nickname"];
    
    points.clear();
    json pointsJson = obj["points"];
    for(int i=0;i<pointsJson.size();i++)
    {
        Vector2 point;
        point.x = pointsJson[i]["x"];
        point.y = pointsJson[i]["y"];
        points.push_back(point);
    }
    
    updateInterval = 0.2;
}

void Slither::update(double deltaTime)
{
    _updateTime += deltaTime;
    std::vector<Vector2> newPoints;
    if(_updateTime >= updateInterval)
    {
        Vector2 lastPt = points[points.size() - 1];
        Vector2 newPt = lastPt.add(direction.mul(width));
        points.erase(points.begin());
        points.push_back(newPt);
        _updateTime = 0;
        
        if(_render != NULL)
        {
            _render->syncNodes();
        }
    }
    
    if(_render != NULL)
    {
        _render->update(deltaTime);
    }
    
    direction.rotateWithDegree(rotateDirection);
}

cocos2d::Vec2 Slither::headPosition()
{
    cocos2d::Node* headNode = _render->headNode();
    if(headNode)
        return headNode->getPosition();
    else
    {
        return cocos2d::Vec2(0,0);
    }
}

Slither* Slither::dieTest(Slither* slither)
{
    for(int i = 0;i < slither->points.size() - 1;i++)
    {
        Vector2 dieTestHead = this->points[points.size() - 1];
        Vector2 dieTestLineBegin = slither->points[i];
        Vector2 dieTestLineEnd = slither->points[i + 1];
        
        double distance = dieTestHead.pointToLineDistance(dieTestHead,dieTestLineBegin,dieTestLineEnd);
        if(distance >=0 && distance < slither->width / 2 + width / 2)
        {
            //i die
            return this;
        }
    }
    
    for(int i = 0;i < this->points.size() - 1;i++)
    {
        Vector2 dieTestHead = slither->points[slither->points.size() - 1];
        Vector2 dieTestLineBegin = points[i];
        Vector2 dieTestLineEnd = points[i + 1];
        double distance = dieTestHead.pointToLineDistance(dieTestHead,dieTestLineBegin,dieTestLineEnd);
        if(distance >=0 && distance < slither->width / 2 + width / 2)
        {
            //u die
            return slither;
        }
    }
    return NULL;
}

SlitherRender* Slither::render(cocos2d::Layer* layer)
{
    if(_render == NULL)
    {
        _render = new SlitherRender(this);
        _render->attachTo(layer);
    }
    return _render;
}