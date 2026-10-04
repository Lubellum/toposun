#include "stdafx.h"
#include "PlayScene.h"
#include "PlayResultScene.h"
#include "PlayPauseScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoStudio.h"

// todo: 消す
USING_NS_CC;

// ========================================================================= //
// 【プレイ】画面
// ========================================================================= //

// ------------------------------------------------------------------------- //
// 生成
// ------------------------------------------------------------------------- //
CPlayScene* CPlayScene::create(const std::string& aParameter)
{
    auto* instance = CPlayScene::create();
    instance->Initilize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CPlayScene::CreateScene(const std::string& aParameter)
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
void CPlayScene::Initilize(const std::string& aParameter)
{
    mParameter = aParameter;
    auto* guiReader = cocostudio::GUIReader::getInstance();
    auto* root = guiReader->widgetFromJsonFile("json/play.json");
    this->addChild(root);
    SetupUI(root);

    mPlayField.Initilize(aParameter, root);

    mPlayHero.SetupPlayer(root);
    auto* listener = EventListenerKeyboard::create();
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
// TiledMap座標からWorld座標への変換
// ------------------------------------------------------------------------- //
cocos2d::Vec2 CPlayScene::TileToWorld(const cocos2d::TMXTiledMap* aTiledMap,
    const cocos2d::Vec2 aCellPos)
{
    const auto mapSize = aTiledMap->getMapSize();
    const auto tileSize = aTiledMap->getTileSize();

    return cocos2d::Vec2(
        tileSize.width * aCellPos.x,
        tileSize.height * ((mapSize.height - aCellPos.y) - 1)
    );
}

// ------------------------------------------------------------------------- //
// World座標からTiledMap座標への変換
// ------------------------------------------------------------------------- //
cocos2d::Vec2 CPlayScene::WorldToTile(const cocos2d::TMXTiledMap* aTiledMap,
    const cocos2d::Vec2 aWorldPos)
{
    const auto mapSize = aTiledMap->getMapSize();
    const auto tileSize = aTiledMap->getTileSize();

    return cocos2d::Vec2(
        std::floor(aWorldPos.x / tileSize.width),
        ( (mapSize.height - 1) - std::floor(aWorldPos.y / tileSize.height) )
    );
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
CPlayScene::tClickEvent CPlayScene::CreateDecisionEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto* director = Director::getInstance();
            auto* scene = CPlayResultScene::CreateScene("eeeeeeeee");
            auto* transition = TransitionFade::create(0.5, scene);
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

    auto* player = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_player"));

    auto* playerDummy = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_player_dummy"));

    const auto* playerDummyLocator = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_player_dummy_locator"));

    // プレイヤーの移動・補正処理
    return[this, player, playerDummy, playerDummyLocator, visibleSize, visibleOrigin, aRoot](
        cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event* aEvent)
    {
            mPlayHero.MovePlayer(player, playerDummy, aKeyCode, aRoot, visibleSize, visibleOrigin, playerDummyLocator);
            return true;
    };
}