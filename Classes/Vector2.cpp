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

void Vector2::rotateWithDegree(double degree)
{
    double oldX = x;
    double oldY = y;
    double cos = cosf(degree / 180 * M_PI);
    double sin = sinf(degree / 180 * M_PI);
    double newX = oldX * cos - oldY * sin;
    double newY = oldX * sin + oldY * cos;
    x = newX;
    y = newY;
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

double Vector2::directionToDegree(Vector2 direction)
{
    double atan = direction.y / direction.x;
    double degree = atanf(atan)/3.14 * 180;
    double x = direction.x;
    double y = direction.y;
    if(x > 0)
    {
        if(y <= 0)
        {
            degree = -degree;
        }
        else
        {
            degree = 360 - degree;
        }
    }
    else
    {
        if(y <= 0)
        {
            degree = 180 - degree;
        }
        else
        {
            degree = 180 - degree;
        }
    }
    return degree;
}