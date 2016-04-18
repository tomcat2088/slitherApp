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