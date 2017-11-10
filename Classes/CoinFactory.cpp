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