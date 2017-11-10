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
    // add talking anim
    auto cache = SpriteFrameCache::getInstance();
    this->leefyTalk.pushBack(cache->getSpriteFrameByName("Leefy-Happy.png"));
    this->leefyTalk.pushBack(cache->getSpriteFrameByName("Leefy-Smile.png"));        
}
 
void LeefySprite::talk()
{
    Animation* anim = new Animation;
    anim->initWithSpriteFrames(this->leefyTalk, 0.35f);
    this->runAction(RepeatForever::create(Animate::create(anim)));                    
}