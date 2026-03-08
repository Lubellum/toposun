#include "PlayLevelSelectScene.h"
#include "PlaySummaryScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoStudio.h"

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
#if 0
    auto image = cocos2d::ui::ImageView::create("playLevelSelect_bg.png");
    //image->setTouchEnabled(true);
    //image->addClickEventListener(CreateDecisionEvent());
    image->setName("playLevelSelect_bg");
    image->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
    image->setPosition(cocos2d::Vec2(0.0, 0.0));
    this->addChild(image, 0);
#else
    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/playlevelselect.json");
    this->addChild(root);
#endif

#if 0
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
#else
    #if 0
    // タッチイベントを作りたい
    auto touchPanels = dynamic_cast<cocos2d::ui::Layout*>(root->getChildByName("touchPanels"));

    auto touchPanel01 = dynamic_cast<cocos2d::ui::Layout*>(touchPanels->getChildByName("touchPanel01"));
    touchPanel01->addClickEventListener(CreateDecisionEvent(0)); // rootをaddchildしているのでここでのaddchildは不要

    auto touchPanel02 = dynamic_cast<cocos2d::ui::Layout*>(touchPanels->getChildByName("touchPanel02"));
    touchPanel02->addClickEventListener(CreateDecisionEvent(1)); // rootをaddchildしているのでここでのaddchildは不要

    auto touchPanel03 = dynamic_cast<cocos2d::ui::Layout*>(touchPanels->getChildByName("touchPanel03"));
    touchPanel03->addClickEventListener(CreateDecisionEvent(2)); // rootをaddchildしているのでここでのaddchildは不要
    #else
    auto touchPanels = dynamic_cast<cocos2d::ui::Layout*>(root->getChildByName("touchPanels"));
    auto children = touchPanels->getChildren();
    for (int i = 0; i < children.size(); ++i)
    {
        auto child = dynamic_cast<cocos2d::ui::Layout*>(children.at(i));
        child->addClickEventListener(CreateDecisionEvent(i));
    }
    #endif
#endif
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