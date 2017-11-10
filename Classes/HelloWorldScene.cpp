#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Leefy.h"
#include "Local.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    //preload leefy
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("leefy.plist");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    //add leefy
    this->addLeefy();

    //Add touch and click to scene
    this->addTouch();
    
    //schedule an update 'run update()'
    this->scheduleUpdate();
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}




void HelloWorld::addLeefy()
{
    this->_leefySprite = LeefySprite::create();

    if (_leefySprite == nullptr)
    {
        problemLoading("'Leefy'");
    }
    else
    {

        // add the sprite as a child to this layer
        this->addChild(_leefySprite, 3);    
        
        //test talking
        this->_leefySprite->talk();
    }    
}

/**
    Add touch controls to scene 
*/
void HelloWorld::addTouch()
{
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);        
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{       
    this->touchDown = true;
    this->lastTouch = touch->getLocation();
    
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    this->touchDown = false;
    //todo smooth out
    this->_leefySprite->setRotation(0); 
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    this->lastTouch = touch->getLocation();    
    this->touchDown = true;
 
    //not quite working right, 
    //todo revisit
    float angle = atan2(touch->getLocation().y - this->_leefySprite->getPosition().y, touch->getLocation().x - this->_leefySprite->getPosition().x );
    angle = angle * (180/M_PI);   
    //todo limit angle!
    //cocos2d::log(" Angle: '%d'", angle);
    this->_leefySprite->setRotation((270 + angle ));  
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    this->touchDown = false;
}

/**
    Update every frame 
*/
void HelloWorld::update(float delta)
{ 
    this->updateLeefy(delta);
}
 

//todo move to leefy class
/**
    Update leefy position each frame 
*/
void HelloWorld::updateLeefy(float delta)
{ 
    auto position = this->_leefySprite->getPosition();
    float y = position.y;
 
    //if we are touching
    if(touchDown)
    {
        auto directionNormalized = (position.x - this->lastTouch.x);
        position.x -= directionNormalized * LEEFY_MOVE_SPEED * delta;        
    }
 
    position.y -= LEEFY_FALL_SPEED * delta;
    this->_leefySprite->setPosition(position);  
}
