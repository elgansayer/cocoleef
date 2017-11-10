#ifndef  _HUD_H_
#define  _HUD_H_

#include "cocos2d.h"

class HUDLayer : public cocos2d::LayerColor
{
    public:
        //~HUDLayer();        
        //virtual bool init();
        //virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);
        
        //static HUDLayer* createLayer();
        static HUDLayer* create();
        
        void addLabels();


        void setScore(int score);
  //      CREATE_FUNC(HUDLayer); 
    private:
       // void setup();
       cocos2d::Label* ScoreLabel;
         
};

#endif // _HUD_H_