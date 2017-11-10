#ifndef _CoinFactory_H_
#define _CoinFactory_H_

#include "cocos2d.h"

class CoinFactory 
{
    public:
       // CoinFactory();
       // ~CoinFactory();
        
        void deleteOldCoins();
        void genetateCoin();
    private:               
        bool canGenetateCoin(float y);
    private:          
        cocos2d::Vector<cocos2d::Sprite*> Coins; 
};

#endif // _CoinFactory_H_