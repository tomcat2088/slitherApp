//
//  Vector2.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#ifndef Vector2_hpp
#define Vector2_hpp

#include <stdio.h>
class Vector2
{
public:
    double x;
    double y;
    
    Vector2();
    Vector2(double x,double y);
    Vector2 add(Vector2 pt);
    Vector2 sub(Vector2 pt);
    Vector2 mul(double val);
    double len();
    Vector2 normalize();
    bool equal(Vector2 pt);
    Vector2 normal();
    Vector2 rotate(Vector2 fromVec,Vector2 toVec);
    double pointToLineDistance(Vector2 point,Vector2 lineBegin,Vector2 lineEnd);
};
#endif /* Vector2_hpp */
