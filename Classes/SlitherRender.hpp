//
//  SlitherRender.hpp
//  slitherApp
//
//  Created by ocean on 5/13/16.
//
//

#ifndef SlitherRender_hpp
#define SlitherRender_hpp

class Slither;
class SlitherRender
{
public:
    SlitherRender(Slither* slither);
    ~SlitherRender();
    
    void syncNodes();
    void update(double deltaTime);
    void attachTo(cocos2d::Layer* layer);
    cocos2d::Node* headNode();
private:
    Slither* _slither;
    bool _isAttached;
    
    cocos2d::Layer* _attachedLayer;
    cocos2d::Vector<cocos2d::Node*> _nodes;
    
    void detach();
};
#endif /* SlitherRender_hpp */
