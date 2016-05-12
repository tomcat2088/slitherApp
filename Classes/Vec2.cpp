//
//  Vec2.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "Vec2.hpp"
Vec2::Vec2()
{

}

Vec2::Vec2(double x,double y):x(x),y(y)
{
    
}

Vec2 Vec2::add(Vec2 pt)
{
    return Vec2(x + pt.x,y + pt.y);
}

Vec2 Vec2::sub(Vec2 pt)
{
    return Vec2(x - pt.x,y - pt.y);
}

Vec2 Vec2::mul(double val)
{
    return Vec2(x * val,y * val);
}

double Vec2::len()
{
    return sqrt(x * x + y*y);
}

Vec2 Vec2::normalize()
{
    double len = sqrt(x * x + y*y);
    return Vec2(x / len,y / len);
}

bool Vec2::equal(Vec2 pt)
{
    if(fabs(x - pt.x) < DBL_EPSILON && fabs(y - pt.y) < DBL_EPSILON)
        return true;
    return false;
}

Vec2 Vec2::normal()
{
    Vec2 normalizePt = normalize();
    double y = normalizePt.x / sqrt(1 + normalizePt.y * normalizePt.y);
    double x = sqrt(1 - y * y);
    return Vec2(x,y);
}

Vec2 Vec2::rotate(Vec2 fromVec,Vec2 toVec)
{
    //fromVec x,y
    //toVec x',y'
    double sin = (fromVec.x * toVec.y - fromVec.y * toVec.x) / (fromVec.x * fromVec.x + fromVec.y * fromVec.y);
    double cos = 0;
    if(fromVec.x == 0)
        cos = 0;
    else
        cos = toVec.x/fromVec.x + fromVec.y/fromVec.x * sin;
    
    double newX = x * cos - y * sin;
    double newY = x * sin + y * cos;

    return Vec2(newX,newY);
}

double Vec2::pointToLineDistance(Vec2 pt,Vec2 lineBegin,Vec2 lineEnd)
{
    pt.x -= lineBegin.x;
    pt.y -= lineBegin.y;
    lineEnd.x -= lineBegin.x;
    lineEnd.y -= lineBegin.y;
    lineBegin.x = 0;
    lineBegin.y = 0;
    
    double len = lineEnd.len();
    lineEnd = lineEnd.normalize();
    pt = pt.rotate(lineEnd,Vec2(1,0));
    if(pt.x >=0 && pt.x <= len)
        return fabs(pt.y);
    return -1;
}