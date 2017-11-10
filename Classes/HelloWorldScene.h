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
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    //override and run updates each frame
    void update(float) override;    
private:    
    //add leefy
    void addLeefy();   

    //add touch to schene
    void addTouch();
    
    //Update each frame
    void updateLeefy(float delta);     
    
private:
    //pointer to the main character 
    LeefySprite * _leefySprite;
    
    //
    cocos2d::Vec2 lastTouch;
    bool touchDown;    
    
};

#endif // __HELLOWORLD_SCENE_H__
