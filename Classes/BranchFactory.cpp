#include "BranchFactory.h"
#include "HelloWorldScene.h"
#include "Local.h"

USING_NS_CC;
  
/*
void BranchFactory::genetateBranch()
{ 
    CCScene *scene = CCDirector::sharedDirector()->getRunningScene();    
    HelloWorld* gameScene = dynamic_cast<HelloWorld*>(scene);    
    if(gameScene != NULL)
    {
        auto camera = gameScene->getDefaultCamera();  
        auto position = camera->getPosition();
        auto visibleSize = Director::getInstance()->getVisibleSize();
 
        float y = position.y - (visibleSize.height / 2);

        auto branch = Sprite::create("Branch1.png");

        this->Branches.pushBack(branch); 
        branch->setPosition(ccp(50, y));

        scene->addChild(branch, 5);
    }


}
*/


void BranchFactory::genetateBranch()
{ 

    CCScene *scene = CCDirector::sharedDirector()->getRunningScene();    
    HelloWorld* gameScene = dynamic_cast<HelloWorld*>(scene);    
    if(gameScene != NULL)
    {
        auto camera = gameScene->getDefaultCamera();  
        auto position = camera->getPosition();
        auto visibleSize = Director::getInstance()->getVisibleSize(); 
        float y = position.y - (visibleSize.height / 2);
            
        if(!this->canGenetateBranch(y))
        {
            return;
        }

        auto spriteName = String::create("Branch1.png");
        if(RandomHelper::random_int(0, 1) == 1)
        {
            spriteName = ccs("BranchTiny.png");
        }
 
        //
        auto branch = Sprite::create(spriteName->getCString());
        if(branch == nullptr)
        {
            return;
        }

        this->Branches.pushBack(branch); 

        int x = RandomHelper::random_int(10, int(visibleSize.width) - 10);
 
        branch->setPosition(ccp(x, y));

        //todo struct const these or something
        //3 id higher than coins (2)
        scene->addChild(branch, 3);
    }
 
}

bool BranchFactory::canGenetateBranch(float y)
{
    if(this->Branches.empty())
    {
        return true;
    }

    //get last sprite
    auto branch = this->Branches.back();

    if(branch == nullptr)
    {
        return true;
    }
     
    float distance = branch->getPosition().y - y;

    float dist = (float)RandomHelper::random_int(DISTANCE_BETWEEN_BRANCHES_MIN, DISTANCE_BETWEEN_BRANCHES_MAX);
 
    return (distance >= dist); 
}

//todo make one single check between all functions to check if branch collides with rect

//todo
//should put this in an update schedule
void BranchFactory::deleteOldBranches()
{ 

    CCScene *scene = CCDirector::sharedDirector()->getRunningScene();    
    HelloWorld* gameScene = dynamic_cast<HelloWorld*>(scene);    
    if(gameScene == NULL)
    {
        return;            
    }

    auto camera = gameScene->getDefaultCamera();  
    auto position = camera->getPosition();
    auto visibleSize = Director::getInstance()->getVisibleSize(); 

    float maxY = position.y + ( (visibleSize.height / 2) - 10) ;

    //  loop through bullets
    for (auto branchIt: this->Branches)
    { 
        if( branchIt->getPositionY() > maxY )
        {
            //delete this object
            this->Branches.eraseObject(branchIt);

            //delete this sprite
            branchIt->removeFromParentAndCleanup(true);
        }
    }
}

/**
 * checkCollisions
 * true if CCObject collides with any branches
 **/
bool BranchFactory::checkCollisions(Node * node)
{
    //delete cant see branches
    this->deleteOldBranches();

    auto nodeRect = CCRectMake(
    node->getPosition().x - (node->getContentSize().width/2),
    node->getPosition().y - (node->getContentSize().height/2),
    node->getContentSize().width,
    node->getContentSize().height);
     
    //  loop through bullets
    for (auto branchIt: this->Branches)
    {
        auto branchRect = CCRectMake(
        branchIt->getPosition().x - (branchIt->getContentSize().width/2),
        branchIt->getPosition().y - (branchIt->getContentSize().height/2),
        branchIt->getContentSize().width,
        branchIt->getContentSize().height);
        
        if (branchRect.intersectsRect(nodeRect))
        {
            //delete this object
            this->Branches.eraseObject(branchIt);

            //delete this sprite
            //branchIt->removeFromParentAndCleanup(true);

            //return true to update score
            return true;
        }
    }
 
    return false; 
}