#include "stdafx.h"
#include "PlayScene.h"
#include "PlayResultScene.h"
#include "PlayPauseScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoStudio.h"


// ========================================================================= //
// 【プレイ】画面
// ========================================================================= //

// ------------------------------------------------------------------------- //
// 生成
// ------------------------------------------------------------------------- //
CPlayScene* CPlayScene::create(const std::string& aParameter)
{
    auto* instance = CPlayScene::create();
    instance->Initialize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
cocos2d::Scene* CPlayScene::CreateScene(const std::string& aParameter)
{
    return CPlayScene::create(aParameter);
}

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CPlayScene::CPlayScene()
    : mParameter()
    , mPlayField()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CPlayScene::~CPlayScene()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
bool CPlayScene::init()
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
void CPlayScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlayScene::Initialize(const std::string& aParameter)
{
    mParameter = aParameter;
    auto* guiReader = cocostudio::GUIReader::getInstance();
    auto* root = guiReader->widgetFromJsonFile("json/play.json");
    this->addChild(root);
    SetupUI(root);

    mPlayField.Initialize(aParameter, root);

    mPlayHero.SetupHero(root);
    auto* listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CreateKeyPressedEvent(root);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// ------------------------------------------------------------------------- //
// UI設定
// ------------------------------------------------------------------------- //
void CPlayScene::SetupUI(const cocos2d::ui::Widget* aRoot)
{
    auto* image = dynamic_cast<cocos2d::ui::ImageView*>(
        aRoot->getChildByName("image_bg"));
    image->addClickEventListener(CreateDecisionEvent());

    auto* button = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_pause"));
    button->addClickEventListener(CreatePauseEvent());
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
CPlayScene::tClickEvent CPlayScene::CreateDecisionEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto* director = cocos2d::Director::getInstance();
            auto* scene = CPlayResultScene::CreateScene("eeeeeeeee");
            auto* transition = cocos2d::TransitionFade::create(0.5, scene);
            director->replaceScene(transition);
        };
}

// ------------------------------------------------------------------------- //
// ポーズ画面遷移イベント生成
// ------------------------------------------------------------------------- //
CPlayScene::tClickEvent CPlayScene::CreatePauseEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto* scene = CPlayPauseScene::CreateScene("eeeeeeeee");
            this->addChild(scene);
        };
}

// ------------------------------------------------------------------------- //
// 《キーボード》押下イベント生成
// ------------------------------------------------------------------------- //
CPlayScene::tKeyboardEvent CPlayScene::CreateKeyPressedEvent(
    const cocos2d::ui::Widget* aRoot)
{
    // 画面のサイズ取得
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 原点位置取得
    const auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto* hero = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_hero"));

    // プレイヤーの移動・補正処理
    return[this, hero, visibleSize, visibleOrigin, aRoot](
        cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event* aEvent)
    {
            mPlayHero.MoveHero(hero, aKeyCode, aRoot, visibleSize, visibleOrigin);
            return true;
    };
}