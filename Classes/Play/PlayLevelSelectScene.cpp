#include "PlayLevelSelectScene.h"
#include "PlaySummaryScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "ui/UILayout.h"

USING_NS_CC;

// ========================================================================= //
// 難易度選択画面
// ========================================================================= //

// ------------------------------------------------------------------------- //
// 生成
// ------------------------------------------------------------------------- //
CPlayLevelSelectScene* CPlayLevelSelectScene::create(const std::string& aParameter)
{
    auto* instance = CPlayLevelSelectScene::create();
    instance->Initilize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CPlayLevelSelectScene::CreateScene(const std::string& aParameter)
{
    return CPlayLevelSelectScene::create(aParameter);
}

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CPlayLevelSelectScene::CPlayLevelSelectScene()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CPlayLevelSelectScene::~CPlayLevelSelectScene()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
bool CPlayLevelSelectScene::init()
{
    if ( Scene::init() == false )
    {
        return false;
    }

    return true;
}

// ------------------------------------------------------------------------- //
// 更新
// ------------------------------------------------------------------------- //
void CPlayLevelSelectScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlayLevelSelectScene::Initilize(const std::string& aParameter)
{
    mParameter = aParameter;
    auto image = cocos2d::ui::ImageView::create("playLevelSelect_bg.png");
    //image->setTouchEnabled(true);
    //image->addClickEventListener(CreateDecisionEvent());
    image->setName("playLevelSelect_bg");
    image->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
    image->setPosition(cocos2d::Vec2(0.0, 0.0));
    this->addChild(image, 0);

    auto touchPanel1 = cocos2d::ui::Layout::create();
    touchPanel1->setContentSize(cocos2d::Size(500, 900));
    touchPanel1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    touchPanel1->setColor(cocos2d::Color3B::GREEN);
    touchPanel1->setOpacity(50);
    touchPanel1->setTouchEnabled(true);
    touchPanel1->addClickEventListener(CreateDecisionEvent(0));
    touchPanel1->setPosition(cocos2d::Vec2(120, 90));
    this->addChild(touchPanel1);

    auto touchPanel2 = cocos2d::ui::Layout::create();
    touchPanel2->setContentSize(cocos2d::Size(500, 900));
    touchPanel2->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    touchPanel2->setColor(cocos2d::Color3B::GREEN);
    touchPanel2->setOpacity(50);
    touchPanel2->setTouchEnabled(true);
    touchPanel2->addClickEventListener(CreateDecisionEvent(1));
    touchPanel2->setPosition(cocos2d::Vec2(710, 90));
    this->addChild(touchPanel2);

    auto touchPanel3 = cocos2d::ui::Layout::create();
    touchPanel3->setContentSize(cocos2d::Size(500, 900));
    touchPanel3->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    touchPanel3->setColor(cocos2d::Color3B::GREEN);
    touchPanel3->setOpacity(50);
    touchPanel3->setTouchEnabled(true);
    touchPanel3->addClickEventListener(CreateDecisionEvent(2));
    touchPanel3->setPosition(cocos2d::Vec2(1310, 90));
    this->addChild(touchPanel3);
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayLevelSelectScene::CreateDecisionEvent(int aLevel)
{
    return [this, aLevel](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto director = Director::getInstance();
            auto scene = CPlaySummaryScene::CreateScene(std::to_string(aLevel));
            auto transition = TransitionFade::create(0.5, scene);
            director->replaceScene(transition);
        };
}