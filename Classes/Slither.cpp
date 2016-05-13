//
//  Slither.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "Slither.hpp"
#include "json.hpp"

using namespace nlohmann;

Slither::Slither():length(100),
width(20),
direction(Vec2(0,1)),
_updateTime(0),
_updateInterval(0)
{
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
        Vec2 point;
        point.x = pointsJson[i]["x"];
        point.y = pointsJson[i]["y"];
        points.push_back(point);
    }
    
    _updateInterval = 1000 / speed;
}

void Slither::update(double deltaTime)
{
    _updateTime += deltaTime;
    std::vector<Vec2> newPoints;
    if(_updateTime >= _updateInterval)
    {
        Vec2 lastPt = points[points.size() - 1];
        Vec2 newPt = lastPt.add(direction.mul(width));
        points.erase(points.begin());
        points.push_back(newPt);
        _updateTime = 0;
    }
}

Slither* Slither::dieTest(Slither* slither)
{
    for(int i = 0;i < slither->points.size() - 1;i++)
    {
        Vec2 dieTestHead = this->points[points.size() - 1];
        Vec2 dieTestLineBegin = slither->points[i];
        Vec2 dieTestLineEnd = slither->points[i + 1];
        
        double distance = dieTestHead.pointToLineDistance(dieTestHead,dieTestLineBegin,dieTestLineEnd);
        if(distance >=0 && distance < slither->width / 2 + width / 2)
        {
            //i die
            return this;
        }
    }
    
    for(int i = 0;i < this->points.size() - 1;i++)
    {
        Vec2 dieTestHead = slither->points[slither->points.size() - 1];
        Vec2 dieTestLineBegin = points[i];
        Vec2 dieTestLineEnd = points[i + 1];
        double distance = dieTestHead.pointToLineDistance(dieTestHead,dieTestLineBegin,dieTestLineEnd);
        if(distance >=0 && distance < slither->width / 2 + width / 2)
        {
            //u die
            return slither;
        }
    }
    return NULL;
}