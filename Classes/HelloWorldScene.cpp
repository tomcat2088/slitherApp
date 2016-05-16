#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "GameSession.hpp"
#include "SlitherTouchController.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::create();
    // 'layer' is an autorelease object
    HelloWorld* layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->camera = scene->getDefaultCamera();
    layer->camera->setScene(scene);
    layer->camera->setPosition(cocos2d::Vec2(0,0));
    layer->camera->retain();
    
    layer->newSession();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    touchController = new SlitherTouchController();

    cocos2d::EventListenerTouchOneByOne* eventListener = cocos2d::EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = [&](Touch* touch, Event* event){
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        touchController->touchBegin(locationInNode);
        return true;
    };
    
    eventListener->onTouchMoved = [&](Touch* touch, Event* event){
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        touchController->touchMove(locationInNode);
        if(session->slither)
        {
            session->slither->direction = touchController->direction;
        }
    };
    
    eventListener->onTouchEnded = [&](Touch* touch, Event* event){
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        touchController->touchEnd(locationInNode);
    };
    
    
    getEventDispatcher()->addEventListenerWithFixedPriority(eventListener, 1000);
    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::update));
    return true;
}

void HelloWorld::newSession()
{
    session = new GameSession(this,camera);
}

void HelloWorld::update(float deltaTime)
{
    if(session != NULL)
    {
        session->update(deltaTime);
    }
}


