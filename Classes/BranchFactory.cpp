#include "BranchFactory.h"
#include "HelloWorldScene.h"

USING_NS_CC;
  
void BranchFactory::genetateBranch()
{ 
    CCScene *scene = CCDirector::sharedDirector()->getRunningScene();    
    HelloWorld* gameScene = dynamic_cast<HelloWorld*>(scene);    
    if(gameScene != NULL)
    {
  //      auto point = node1->convertToWorldSpace(gameScene->getPosition()); 

        auto camera = gameScene->getDefaultCamera();  
        auto position = camera->getPosition();
        auto visibleSize = Director::getInstance()->getVisibleSize();
 
        float y = position.y - (visibleSize.height / 2);

        auto branch = Sprite::create("Branch1.png");

        this->Branches.pushBack(branch); 
        branch->setPosition(ccp(50, y));

        scene->addChild(branch, 5);
    }
else{
    cocos2d::log("is nul");
}

}