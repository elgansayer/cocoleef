#include "CoinFactory.h"
#include "HelloWorldScene.h"
#include "Local.h"
USING_NS_CC;
  
void CoinFactory::genetateCoin()
{ 

    CCScene *scene = CCDirector::sharedDirector()->getRunningScene();    
    HelloWorld* gameScene = dynamic_cast<HelloWorld*>(scene);    
    if(gameScene != NULL)
    {
        auto camera = gameScene->getDefaultCamera();  
        auto position = camera->getPosition();
        auto visibleSize = Director::getInstance()->getVisibleSize(); 
        float y = position.y - (visibleSize.height / 2);
            
        if(!this->canGenetateCoin(y))
        {
            return;
        }


  //      auto point = node1->convertToWorldSpace(gameScene->getPosition()); 

        auto coin = Sprite::create("Coin.png");

        this->Coins.pushBack(coin); 

        int x = RandomHelper::random_int(10, int(visibleSize.width) - 10);
 
        coin->setPosition(ccp(x, y));

        scene->addChild(coin, 2);
    }
 
}

bool CoinFactory::canGenetateCoin(float y)
{
    if(this->Coins.empty())
    {
        return true;
    }

    //get last sprite
    auto coin = this->Coins.back();

    if(coin == nullptr)
    {
        return true;
    }
     
    float distance = coin->getPosition().y - y;

    float dist = (float)RandomHelper::random_int(DISTANCE_BETWEEN_COINS_MIN, DISTANCE_BETWEEN_COINS_MAX);
 
    return (distance >= dist); 
}



//todo
//should put this in an update schedule
void CoinFactory::deleteOldCoins()
{ 
}

/**
 * checkCollisions
 * true if CCObject collides with any coins
 **/
bool CoinFactory::checkCollisions(Node * node)
{
    auto nodeRect = CCRectMake(
    node->getPosition().x - (node->getContentSize().width/2),
    node->getPosition().y - (node->getContentSize().height/2),
    node->getContentSize().width,
    node->getContentSize().height);
    
  
    //  loop through bullets
    for (auto coinIt: this->Coins)
    {
        auto coinRect = CCRectMake(
        coinIt->getPosition().x - (coinIt->getContentSize().width/2),
        coinIt->getPosition().y - (coinIt->getContentSize().height/2),
        coinIt->getContentSize().width,
        coinIt->getContentSize().height);
        
        if (coinRect.intersectsRect(nodeRect))
        {
            //delete this object
            this->Coins.eraseObject(coinIt);

            //delete this sprite
            coinIt->removeFromParentAndCleanup(true);

            //return true to update score
            return true;
        }
    }

//this->_bullets.eraseObject(bullet);

    return false; 
}