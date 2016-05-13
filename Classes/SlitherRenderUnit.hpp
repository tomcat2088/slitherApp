//
//  SlitherRenderUnit.hpp
//  slitherApp
//
//  Created by ocean on 5/13/16.
//
//

#ifndef SlitherRenderUnit_hpp
#define SlitherRenderUnit_hpp

#include <stdio.h>
class SlitherRenderUnit : public cocos2d::Node
{
public:
    void moveTo(cocos2d::Vec2 pos,double duration);
    void update(double deltaTime);
};
#endif /* SlitherRenderUnit_hpp */
