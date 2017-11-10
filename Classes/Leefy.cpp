#include "Leefy.h"
#include "SimpleAudioEngine.h"

USING_NS_CC; 

LeefySprite::LeefySprite() {}

LeefySprite::~LeefySprite() {}

LeefySprite* LeefySprite::create()
{ 
    auto pSprite = new LeefySprite();

    if (pSprite->initWithSpriteFrameName("Leefy-Skeleton.png"))
    { 
        pSprite->autorelease();

        pSprite->initLeefy();

        //add animations
        pSprite->initAnims();
 
        //make him happy enough
        pSprite->happy();
        
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void LeefySprite::initLeefy()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
    // position the sprite on the center of the screen
    //visibleSize.height/4 + origin.y
    float y = (visibleSize.height/2 + origin.y);    
    y += (this->getBoundingBox().size.height / 2);
    this->setPosition(Vec2(visibleSize.width/2 + origin.x, y));

}

void LeefySprite::initAnims()
{
    
    auto cache = SpriteFrameCache::getInstance();

    // add talking anim
    this->leefyTalk.pushBack(cache->getSpriteFrameByName("Leefy-Happy.png"));
    this->leefyTalk.pushBack(cache->getSpriteFrameByName("Leefy-Smile.png"));        

    // add bump anim 
    this->leefyBump.pushBack(cache->getSpriteFrameByName("Leefy-Bump.png"));    

    this->leefyHappy.pushBack(cache->getSpriteFrameByName("Leefy-Happy.png"));    
    
}
 
void LeefySprite::happy()
{
    Animation* anim = new Animation;
    anim->initWithSpriteFrames(this->leefyHappy, 1.0f);
    this->runAction(RepeatForever::create(Animate::create(anim)));                    
}

void LeefySprite::talk()
{
    Animation* anim = new Animation;
    anim->initWithSpriteFrames(this->leefyTalk, 0.35f);
    this->runAction(RepeatForever::create(Animate::create(anim)));                    
}

void LeefySprite::bump()
{
    Animation* anim = new Animation;
    anim->initWithSpriteFrames(this->leefyBump, 1.0f);
    this->runAction(Animate::create(anim));                    
}