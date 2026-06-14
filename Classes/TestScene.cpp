#include "stdafx.h"
#include "TestScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UILayout.h"


USING_NS_CC;

CTestScene::CTestScene()
    : mVisibleSize(Director::getInstance()->getVisibleSize())
    , mOrigin(Director::getInstance()->getVisibleOrigin())
    , mRemainingTime(60)
{

}

Scene* CTestScene::createScene()
{
    return CTestScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CTestSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CTestScene::init()
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
                                           CC_CALLBACK_1(CTestScene::menuCloseCallback, this));

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
    auto timeCountLabel = Label::createWithTTF(value, "fonts/oshigo.ttf", 48);
    timeCountLabel->setName("TimeCount");
    timeCountLabel->setPosition(Vec2(timeCountLabel->getContentSize().width / 2,
        mOrigin.y + mVisibleSize.height - (timeCountLabel->getContentSize().height / 2)));
    this->addChild(timeCountLabel, 0);

    this->scheduleUpdate();

    this->scheduleUpdate();

    cocos2d::Vec2 positions[(int)tLevel::nNum] =
    {
        cocos2d::Vec2(120, 90),
        cocos2d::Vec2(710, 90),
        cocos2d::Vec2(1310, 90)
    };

    for (int i = 0; i < static_cast<int>(tLevel::nNum); ++i)
    {
        auto touchPanel = cocos2d::ui::Layout::create();
        touchPanel->setContentSize(cocos2d::Size(500, 900));
        touchPanel->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        touchPanel->setColor(cocos2d::Color3B::GREEN);
        touchPanel->setOpacity(50);
        touchPanel->setTouchEnabled(true);
        touchPanel->addClickEventListener(CreateDecisionEvent(i));
        touchPanel->setPosition(positions[i]);
        this->addChild(touchPanel);
    }

    return true;
}

void CTestScene::update(float delta)
{
    auto sprite = dynamic_cast<Sprite*>(this->getChildByName("HelloWorld"));
    //sprite->setRotation(5.0 + sprite->getRotation());
    //sprite->setRotation( (90.0 * delta) + sprite->getRotation() );
    //sprite->setPosition(Vec2(10.0, 0.0) + sprite->getPosition());
    //sprite->setPosition( (Vec2(100.0, 0.0) *delta) + sprite->getPosition());
    mRemainingTime -= delta;
    int remainingTime = mRemainingTime;
    auto timeCountLabel = dynamic_cast<Label*>(this->getChildByName("TimeCount"));
    //auto value = cocos2d::StringUtils::format("TimeCount : %4.2f",mRemainingTime);
    auto value = cocos2d::StringUtils::format("TimeCount : %d",remainingTime);
    timeCountLabel->setString(value);

    mRemainingTime -= delta;
    if (mRemainingTime >= 0.0)
    {
        int remainingTime = mRemainingTime;
        auto timeCountLabel = dynamic_cast<Label*>(this->getChildByName("TimeCount"));
        auto value = cocos2d::StringUtils::format("TimeCount : %d", remainingTime);
        timeCountLabel->setString(value);
    }
}


void CTestScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

    int x = 0;
    if (x)
    {
        // されない
    }
    else
    {
        // される
    }
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CTestScene::CreateDecisionEvent(int aLevel)
{
    return [this, aLevel](cocos2d::Ref*)
        {
            //cocos2d::log(mParameter.c_str());
            cocos2d::log(std::to_string(aLevel).c_str());
            auto director = Director::getInstance();
            auto scene = CTestScene::createScene();
            auto transition = TransitionFade::create(0.5, scene);
            director->replaceScene(transition);
        };
}