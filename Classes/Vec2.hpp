//
//  Vec2.hpp
//  slitherApp
//
//  Created by wangyang on 16/4/18.
//
//

#ifndef Vec2_hpp
#define Vec2_hpp

#include <stdio.h>
class Vec2
{
public:
    double x;
    double y;
    
    Vec2();
    Vec2(double x,double y);
    Vec2 add(Vec2 pt);
    Vec2 sub(Vec2 pt);
    Vec2 mul(double val);
    double len();
    Vec2 normalize();
    bool equal(Vec2 pt);
    Vec2 normal();
};
#endif /* Vec2_hpp */
