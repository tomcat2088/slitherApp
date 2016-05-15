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
class SlitherRenderUnit : public cocos2d::LayerColor
{
public:
    virtual bool init();
    
    void moveTo(cocos2d::Vec2 pos,double duration);
    void update(double deltaTime);
    
    CREATE_FUNC(SlitherRenderUnit);
private:
    cocos2d::Vec2 _oldPos;
    cocos2d::Vec2 _targetPos;
    double _duration;
    double _durationLeft;
};
#endif /* SlitherRenderUnit_hpp */
