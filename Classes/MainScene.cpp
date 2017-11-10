//
//  MainScene.cpp
//  ExpJam
//
//  Created by Two Tails on 09/12/2014.
//
//

#include "MainScene.h"


USING_NS_CC;



// on "init" you need to initialize your instance
bool MainScene::init()
{
    // super init first
    if ( !Super::init() )
    {
        return false;
    }
    
    // get visible size of window
    Size visibleSize = Director::getInstance()->getVisibleSize();
  
    // add a sprite
    Sprite* sprite = Sprite::create( "BlueBlob-Normal.png" );
    sprite->setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2 ) );
    // add the sprite as a child to this layer
    this->addChild( sprite );
    
    
    // done
    return true;
}

void MainScene::onEnter()
{
    Super::onEnter();
    
    // create a keyboard event listener
    if( _keyEventListener == NULL )
    {
        _keyEventListener = EventListenerKeyboard::create();
        _keyEventListener->onKeyPressed = CC_CALLBACK_2( MainScene::onKeyPressed, this );
        _keyEventListener->onKeyReleased = CC_CALLBACK_2( MainScene::onKeyReleased, this );
    }
    
    // create a mouse event listener
    if( _mouseEventListener == NULL )
    {
        _mouseEventListener = EventListenerMouse::create();
        _mouseEventListener->onMouseMove = CC_CALLBACK_1( MainScene::onMouseMove, this );
        _mouseEventListener->onMouseUp = CC_CALLBACK_1( MainScene::onMouseUp, this );
        _mouseEventListener->onMouseDown = CC_CALLBACK_1( MainScene::onMouseDown, this );
        _mouseEventListener->onMouseScroll = CC_CALLBACK_1( MainScene::onMouseScroll, this );
    }
    
    // register event listeners
    _eventDispatcher->addEventListenerWithSceneGraphPriority( _keyEventListener, this );
    _eventDispatcher->addEventListenerWithSceneGraphPriority( _mouseEventListener, this );
    
    // schedule update calls
    scheduleUpdate();
}

void MainScene::onExit()
{
    Super::onExit();
    
    // de-register event listeners
    _eventDispatcher->removeEventListener( _keyEventListener );
    _eventDispatcher->removeEventListener( _mouseEventListener );
    
    // unschedule update
    unscheduleUpdate();
}

void MainScene::update( float delta )
{
    // called once per frame
//    cocos2d::log( "Update: %f", delta );
    
}


#pragma mark - Key Events


void MainScene::onKeyPressed( EventKeyboard::KeyCode keyCode, Event* event )
{
    cocos2d::log( "Key with keycode %d pressed", keyCode );
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event )
{
    cocos2d::log( "Key with keycode %d released", keyCode );
}


#pragma mark - Mouse Events


void MainScene::onMouseDown( Event *event )
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Down detected, Key: ";
    str += std::to_string(e->getMouseButton());
    cocos2d::log( "%s", str.c_str() );
}

void MainScene::onMouseUp( Event *event )
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Up detected, Key: ";
    str += std::to_string(e->getMouseButton());
    cocos2d::log( "%s", str.c_str() );
}

void MainScene::onMouseMove( Event *event )
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "MousePosition X:";
    str += std::to_string(e->getCursorX()) + " Y:" + std::to_string(e->getCursorY());
//    cocos2d::log( "%s", str.c_str() );
}

void MainScene::onMouseScroll( Event *event )
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Scroll detected, X: ";
    str += std::to_string(e->getScrollX()) + " Y: " + std::to_string(e->getScrollY());
    cocos2d::log( "%s", str.c_str() );
}
