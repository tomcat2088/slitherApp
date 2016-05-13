//
//  Vector2.cpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#include "Vector2.hpp"
Vector2::Vector2()
{

}

Vector2::Vector2(double x,double y):x(x),y(y)
{
    
}

Vector2 Vector2::add(Vector2 pt)
{
    return Vector2(x + pt.x,y + pt.y);
}

Vector2 Vector2::sub(Vector2 pt)
{
    return Vector2(x - pt.x,y - pt.y);
}

Vector2 Vector2::mul(double val)
{
    return Vector2(x * val,y * val);
}

double Vector2::len()
{
    return sqrt(x * x + y*y);
}

Vector2 Vector2::normalize()
{
    double len = sqrt(x * x + y*y);
    return Vector2(x / len,y / len);
}

bool Vector2::equal(Vector2 pt)
{
    if(fabs(x - pt.x) < DBL_EPSILON && fabs(y - pt.y) < DBL_EPSILON)
        return true;
    return false;
}

Vector2 Vector2::normal()
{
    Vector2 normalizePt = normalize();
    double y = normalizePt.x / sqrt(1 + normalizePt.y * normalizePt.y);
    double x = sqrt(1 - y * y);
    return Vector2(x,y);
}

Vector2 Vector2::rotate(Vector2 fromVec,Vector2 toVec)
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

    return Vector2(newX,newY);
}

double Vector2::pointToLineDistance(Vector2 pt,Vector2 lineBegin,Vector2 lineEnd)
{
    pt.x -= lineBegin.x;
    pt.y -= lineBegin.y;
    lineEnd.x -= lineBegin.x;
    lineEnd.y -= lineBegin.y;
    lineBegin.x = 0;
    lineBegin.y = 0;
    
    double len = lineEnd.len();
    lineEnd = lineEnd.normalize();
    pt = pt.rotate(lineEnd,Vector2(1,0));
    if(pt.x >=0 && pt.x <= len)
        return fabs(pt.y);
    return -1;
}