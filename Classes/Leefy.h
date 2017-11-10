#ifndef _LeefySprite_H_
#define _LeefySprite_H_

#include "cocos2d.h"

class LeefySprite : public cocos2d::Sprite
{
    public:
        LeefySprite();
        ~LeefySprite();
        static LeefySprite* create();
 
        //void addEvents();
        //void touchEvent(cocos2d::Touch* touch, cocos2d::Vector2 _p);
        
        void happy();
        void bump();
        void talk();
    private:
        void initAnims();
        void initLeefy();

    private:
        cocos2d::Vector<cocos2d::SpriteFrame*> leefyTalk;

        cocos2d::Vector<cocos2d::SpriteFrame*> leefyBump; 

        cocos2d::Vector<cocos2d::SpriteFrame*> leefyConcern; 

        cocos2d::Vector<cocos2d::SpriteFrame*> leefyHappy; 

        cocos2d::Vector<cocos2d::SpriteFrame*> leefySkeleton; 
};

#endif // _LeefySprite_H_