#include "HelloWorldScene.h"
#include "Leefy.h"
#include "Local.h"
#include "HUD.h"
#include "SimpleAudioEngine.h"
#include <math.h>
#include "BranchFactory.h"
#include "CoinFactory.h"
#include <memory>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // create the scene with physics enabled
    auto scene = HelloWorld::create();
 
    //WithPhysics
    // set gravity
    //scene->getPhysicsWorld()->setGravity(Vec2(0, -900));

    // optional: set debug draw
   // scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

    //auto layer = HelloWorld::create();
    //scene->addChild(layer);

    return scene;
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

    //make factories 
    this->_CoinFactory = new CoinFactory();
    this->_BranchFactory = new BranchFactory();
    //this->CoinFactory = std::make_unique<CoinFactory>(); // p is a unique_ptr that owns a D
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); 
 
    /*
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
 
    */

    this->addHUD();

    //this->addBackground();
 
    //add leefy
    this->addLeefy();
        
    //Add touch and click to scene
    this->addTouch();
      
/*
//create a sprite
auto sprite = Sprite::create("BranchTiny.png");
sprite->setPosition(ccp(100, 100));
addChild(sprite);

//create a sprite
auto sprited = Sprite::create("Branch1.png");
sprited->setPosition(ccp(200, 200));
addChild(sprited);
    
//create a sprite
auto coins = Sprite::create("Coin.png");
coins->setPosition(ccp(100, 200));
addChild(coins);
*/

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

void HelloWorld::addHUD()
{ 
    this->HUD = HUDLayer::create();
    this->addChild(this->HUD, 1);

    //init hud to 0
    this->HUD->setScore(0);
}

void HelloWorld::addBackground()
{
    return;
    // add sky_Background
    this->_backgroundSprite = Sprite::create("sky_Background.png");
    if (this->_backgroundSprite == nullptr)
    {
        problemLoading("'sky_Background.png'");
    }
    else
    {


        // add the sprite as a child to this layer
        this->addChild(this->_backgroundSprite, 2);
    }    
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
    Update every frame 
*/
void HelloWorld::update(float delta)
{ 
    this->_CoinFactory->genetateCoin();

    //cocos2d::log(" %4.2f %4.2f",this->getPosition().x, this->getPosition().y );
 
    this->updateHUD(delta);
    this->updateLeefy(delta);
    this->updateCamera(delta);
}


 
void HelloWorld::updateHUD(float delta)
{

    auto camera = this->getDefaultCamera();  
    auto position = camera->getPosition();
    auto visibleSize = Director::getInstance()->getVisibleSize();
 
    this->HUD->setPosition(Vec2(0, position.y - (visibleSize.height / 2)));        
} 

//todo move to leefy class
void HelloWorld::updateLeefy(float delta)
{ 
    auto position = this->_leefySprite->getPosition();
    float y = position.y;
 
    if(touchDown)
    {
        //auto directionNormalized = (position - this->lastTouch).getNormalized();
        auto directionNormalized = (position.x - this->lastTouch.x);
        position.x -= directionNormalized * LEEFY_MOVE_SPEED * delta;        
    }
 
    position.y -= LEEFY_FALL_SPEED * delta;
    this->_leefySprite->setPosition(position);  
}

void HelloWorld::updateCamera(float delta)
{
    auto camera = this->getDefaultCamera();
    auto pos = camera->getPosition3D();
//camera->setPosition3D(Vec3(pos.x, pos.y - delta * LEEFY_FALL_SPEED, pos.z));

    cam era->setPositionY(camera->getPositionY() - delta * LEEFY_FALL_SPEED);    
}
 














