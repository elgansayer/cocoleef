#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Leefy.h"
#include "HUD.h"
#include "CoinFactory.h"
#include "BranchFactory.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    //add leefy
    void addLeefy();
    void addBackground();

    //override and run updates each frame
    void update(float) override; 

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    //add touch to schene
    void addTouch();
    
    //add hud to schene  
    void addHUD();

    void checkCollisions();

    //Update each function each frame
    void updateHUD(float delta);
    void updateLeefy(float delta);
    void updateCamera(float delta);    
private:
    CoinFactory * _CoinFactory;
    BranchFactory * _BranchFactory;

    HUDLayer * HUD; 
    LeefySprite *_leefySprite;
    cocos2d::Sprite * _backgroundSprite; 
    
    cocos2d::Vec2 lastTouch;
    bool touchDown;

    int Score;
};

#endif // __HELLOWORLD_SCENE_H__
