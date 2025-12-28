/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

HelloWorld::HelloWorld()
    : mVisibleSize(Director::getInstance()->getVisibleSize())
    , mOrigin(Director::getInstance()->getVisibleOrigin())
    , mRemainingTime(60)
{

}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

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
        float x = mOrigin.x + mVisibleSize.width - closeItem->getContentSize().width/2;
        float y = mOrigin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(mOrigin.x + mVisibleSize.width/2,
                                mOrigin.y + mVisibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        sprite->setName("HelloWorld");
        // position the sprite on the center of the screen
        //sprite->setPosition(Vec2(mVisibleSize.width / 2 + mOrigin.x, mVisibleSize.height / 2 + mOrigin.y));
        sprite->setPosition(mVisibleSize.width/2 + mOrigin.x, mVisibleSize.height/2 + mOrigin.y);
        sprite->setAnchorPoint(Vec2(0.0, 0.0));
        //sprite->setPosition(Vec2(0.0, 0.0));
        //sprite->setPosition(Vec2(mOrigin.x, mOrigin.y));
        //sprite->setPosition(Vec2( (sprite->getContentSize().width) / 2, (sprite->getContentSize().height) / 2));
        //sprite->setRotation(45);
        sprite->setScale(1.0, 1.0);
        //sprite->setFlippedX(true);
        //sprite->setFlippedY(true);

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

    auto value = cocos2d::StringUtils::format("TimeCount : %d", mRemainingTime);
    auto timeCountLabel = Label::createWithTTF(value, "fonts/Marker Felt.ttf", 48);
    timeCountLabel->setName("TimeCount");
    timeCountLabel->setPosition(Vec2(timeCountLabel->getContentSize().width / 2,
        mOrigin.y + mVisibleSize.height - (timeCountLabel->getContentSize().height / 2)));
    //timeCountLabel->setString("Count");
    this->addChild(timeCountLabel, 0);

    this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
    auto sprite = dynamic_cast<Sprite*>(this->getChildByName("HelloWorld"));
    //sprite->setRotation(5.0 + sprite->getRotation());
    //sprite->setRotation( (90.0 * delta) + sprite->getRotation() );
    //sprite->setPosition(Vec2(10.0, 0.0) + sprite->getPosition());
    //sprite->setPosition( (Vec2(100.0, 0.0) *delta) + sprite->getPosition());
    mRemainingTime -= delta;
    //int remainingTime = mRemainingTime;
    auto timeCountLabel = dynamic_cast<Label*>(this->getChildByName("TimeCount"));
    auto value = cocos2d::StringUtils::format("TimeCount : %4.2f",mRemainingTime);
    //auto value = cocos2d::StringUtils::format("TimeCount : %d",remainingTime);
    timeCountLabel->setString(value);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
