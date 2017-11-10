#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Leefy.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    

    //override and run updates each frame
    void update(float) override;    


    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:    
    //add leefy
    void addLeefy();   

    //add touch to schene
    void addTouch();
    
    //add hud to schene  
    void addHUD();
    
    //Update each frame
    void updateLeefy(float delta);     
    
    //Update each function each frame
    void updateHUD(float delta);
    
    //Update each frame
    void updateCamera(float delta);        
private:
    //pointer to the main character 
    LeefySprite * _leefySprite;
    
    HUDLayer * HUD;     
    //
    cocos2d::Vec2 lastTouch;
    bool touchDown;    
    
};

#endif // __HELLOWORLD_SCENE_H__
