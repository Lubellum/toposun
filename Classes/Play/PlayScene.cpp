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
// プレイ画面
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
    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/play.json");
    this->addChild(root);
    SetupUI(root);

    auto mapStage = cocos2d::TMXTiledMap::create("map/stage1.tmx");
    auto panelStage = dynamic_cast<cocos2d::ui::Layout*>(
        root->getChildByName("panel_stage"));
    panelStage->addChild(mapStage);
    auto mapLogic = cocos2d::TMXTiledMap::create("map/stage1_logic.tmx");
    auto panelLogic = dynamic_cast<cocos2d::ui::Layout*>(
        root->getChildByName("panel_logic"));
    panelLogic->addChild(mapLogic);
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CreateKeyPressedEvent(root);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// ------------------------------------------------------------------------- //
// UI設定
// ------------------------------------------------------------------------- //
void CPlayScene::SetupUI(cocos2d::ui::Widget* aRoot)
{
    auto image = dynamic_cast<cocos2d::ui::ImageView*>(
        aRoot->getChildByName("image_bg"));
    image->addClickEventListener(CreateDecisionEvent());

    auto button = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_pause"));
    button->addClickEventListener(CreatePauseEvent());

    auto player = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_player"));
    player->setPosition(cocos2d::Vec2(1000, 400));
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
CPlayScene::tClickEvent CPlayScene::CreateDecisionEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto director = Director::getInstance();
            auto scene = CPlayResultScene::CreateScene("eeeeeeeee");
            auto transition = TransitionFade::create(0.5, scene);
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
            auto director = Director::getInstance();
            auto scene = CPlayPauseScene::CreateScene("eeeeeeeee");
            this->addChild(scene);
        };
}

// ------------------------------------------------------------------------- //
// 《キーボード》押下イベント生成
// ------------------------------------------------------------------------- //
CPlayScene::tKeyboardEvent CPlayScene::CreateKeyPressedEvent(
    cocos2d::ui::Widget* aRoot)
{
    // 画面のサイズ取得
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 原点位置取得
    auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto player = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_player"));

    auto playerDummy = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_player_dummy"));

    auto playerDummyLocator = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_player_dummy_locator"));

    // プレイヤーの移動・補正処理
    return[this, player, playerDummy, playerDummyLocator, visibleSize, visibleOrigin](
        cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event* aEvent)
    {
        // 移動処理
        Vec2 position = player->getPosition();
        Vec2 positionDummy = playerDummy->getPosition();

        switch (aKeyCode)
        {
        case cocos2d::EventKeyboard::KeyCode::KEY_W: // 上
            position.y += 40;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S: // 下
            position.y -= 40;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A: // 左
            position.x -= 40;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D: // 右
            position.x += 40;
            break;
        default:
            break;
        }

        // 補正処理
        // 上
        if (position.y + player->getContentSize().height > visibleSize.height)
        {
            position.y = visibleSize.height - player->getContentSize().height;
        }
        // 下
        if (position.y < visibleOrigin.y)
        {
            position.y = visibleOrigin.y;
        }
        // プレイヤー(左側の頂点)が左端を超えているかどうか
        if (position.x < visibleOrigin.x)
        {
            int dt = abs(position.x - visibleOrigin.x);
            positionDummy.y = position.y;
            positionDummy.x = visibleSize.width - dt;
            if ( (position.x + player->getContentSize().width) < visibleOrigin.x)
            {
                position.x = positionDummy.x;
                positionDummy = playerDummyLocator->getPosition();
            }
        }
        // プレイヤー(右側の頂点)が右端を超えているかどうか
        else if (position.x + player->getContentSize().width > visibleSize.width)
        {
            int dt = abs( (position.x + player->getContentSize().width) - visibleSize.width);
            positionDummy.y = position.y;
            positionDummy.x = visibleOrigin.x - playerDummy->getContentSize().width + dt;
            if ( position.x > visibleSize.width )
            {
                position.x = positionDummy.x;
                positionDummy = playerDummyLocator->getPosition();
            }
        }
        else
        {
            positionDummy = playerDummyLocator->getPosition();
        }

        player->setPosition(position);
        playerDummy->setPosition(positionDummy);
        return true;
    };
}