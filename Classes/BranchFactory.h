#ifndef _BranchFactory_H_
#define _BranchFactory_H_

#include "cocos2d.h"

class BranchFactory 
{
    public:
       // BranchFactory();
       // ~BranchFactory();
  
        void genetateBranch();
        void deleteOldBranches();
        bool checkCollisions(cocos2d::Node * node);
    private:               
        bool canGenetateBranch(float y);
    private:        
        cocos2d::String Branch1;
        cocos2d::String Branch2;
        cocos2d::Vector<cocos2d::Sprite*> Branches; 
};

#endif // _BranchFactory_H_