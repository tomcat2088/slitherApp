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
color(0xaaaa00),
direction(Vec2(0,1))
{
    points.push_back(Vec2(2,2));
}

std::string Slither::serialize()
{
    json obj;
    obj["length"] = length;
    obj["width"] = width;
    obj["color"] = color;
    json pointsJson;
    for(int i=0;i<points.size();i++)
    {
        json pointJson;
        pointJson["x"] = points[i].x;
        pointJson["y"] = points[i].y;
        pointsJson.push_back(pointJson);
    }
    obj["points"] = pointsJson;
    return std::string(obj.dump());
}

void Slither::deserialize(std::string dataStr)
{
    json obj = json::parse(dataStr);
    length = obj["length"];
    width = obj["width"];
    color = obj["color"];
    
    points.clear();
    json pointsJson = obj["points"];
    for(int i=0;i<pointsJson.size();i++)
    {
        Vec2 point;
        point.x = pointsJson[i]["x"];
        point.y = pointsJson[i]["y"];
        points.push_back(point);
    }
}

void Slither::update(double deltaTime)
{
    double forwardDistance = updateHead(deltaTime);
    updateTail(deltaTime,forwardDistance);
}

//Head
Vec2 Slither::head()
{
    return points[points.size() - 1];
}

double Slither::updateHead(double deltaTime)
{
    Vec2 newPoint = head();
    newPoint = newPoint.add(direction.mul(speed * deltaTime));
    double forwardDistance = speed * deltaTime;
    double len = points.size();
    Vec2 oldVec = points[len - 1].sub(points[len - 2]).normalize();
    if(direction.normalize().equal(oldVec))
    {
        points[points.size() - 1] = newPoint;
    }
    else
    {
        points.push_back(newPoint);
    }
    return forwardDistance;
}

//Tail
void Slither::updateTail(double deltaTime,double forwardDistance)
{
    double trackedLen = 0;
    for(int index = (int)points.size()-1;index >= 1;index--)
    {
        double segmentLen = points[index].sub(points[index-1]).len();
        trackedLen+=segmentLen;
        if(trackedLen >= length)
        {
            //track finish
            double forwardOnThisSeg =  trackedLen - length;
            double overLen = forwardOnThisSeg;
            Vec2 vec = points[index].sub(points[index-1]).normalize();
            points[index-1] = points[index-1].add(vec.mul(overLen));
            for(int j=0;j<index-1;j++)
            {
                points.erase(points.begin());
            }
            return;
        }
    }
}