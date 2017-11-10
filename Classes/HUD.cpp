#include "HUD.h"

USING_NS_CC;
 
 
HUDLayer* HUDLayer::create()
{ 
    HUDLayer *ret = new (std::nothrow) HUDLayer();
    if (ret && ret->initWithColor(Color4B(135, 206, 250	, 255)))
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        ret->setContentSize(visibleSize);
        ret->setPosition(Vec2(0,0));

        ret->addLabels();

        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    } 
}
 
void HUDLayer::addLabels()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create 'hud' layer
    //this->HUDLayer = LayerColor::create(Color4B(135, 206, 250	, 255));
    //this->HUDLayer->setContentSize(visibleSize);
    //this->HUDLayer->setPosition(Vec2(0,0));
    //this->addChild(this->HUDLayer, 1);

    auto label = Label::createWithTTF("Score: ", "fonts/Marker Felt.ttf", 24);
    if (label != nullptr)
    {
        label->setTextColor(Color4B(0, 0, 0, 255));

        // position the label on the center of the screen
        label->setPosition(Vec2( (label->getContentSize().width / 2) + 5,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    this->ScoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
    if (this->ScoreLabel != nullptr)
    {
        this->ScoreLabel->setTextColor(Color4B(0, 0, 0, 255));
        // position the label on the center of the screen
        auto position = label->getPosition();
        auto size = (label->getContentSize().width / 2) + 10;
        position.x += size;
        this->ScoreLabel->setPosition(position);
        // add the label as a child to this layer
        this->addChild(this->ScoreLabel, 1);
    }
}

void HUDLayer::setScore(int score)
{
    //todo revisit cocos way
    //cheap, nasty, lazy
    auto str = String::createWithFormat("%d", score);
    this->ScoreLabel->setString(str->_string);
}
 