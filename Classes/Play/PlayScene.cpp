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
    auto image = dynamic_cast<cocos2d::ui::ImageView*>(
        root->getChildByName("image_bg"));
    image->addClickEventListener(CreateDecisionEvent());

    auto button = dynamic_cast<cocos2d::ui::Layout*>(
        root->getChildByName("panel_pause"));
    button->addClickEventListener(CreatePauseEvent());

    auto player = dynamic_cast<cocos2d::ui::Layout*>(
        root->getChildByName("panel_player"));
    player->setPosition(cocos2d::Vec2(1000, 400));

    // 画面のサイズ取得
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 原点位置取得
    auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto listener = EventListenerKeyboard::create();

    // プレイヤーの移動・補正処理
    listener->onKeyPressed = [this, player, visibleSize, visibleOrigin](cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event* aEvent)
        {
            // 移動処理
            Vec2 position = player->getPosition();

            switch (aKeyCode)
            {
            case cocos2d::EventKeyboard::KeyCode::KEY_W: // 上
                position.y += 50;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_S: // 下
                position.y -= 50;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_A: // 左
                position.x -= 50;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_D: // 右
                position.x += 50;
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
            // 左
            if (position.x < visibleOrigin.x)
            {
                position.x = visibleOrigin.x;
            }
            // 右
            if (position.x + player->getContentSize().width > visibleSize.width)
            {
                position.x = visibleSize.width - player->getContentSize().width;
            }

            player->setPosition(position);
            return true;
        };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayScene::CreateDecisionEvent()
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
std::function<void(Ref*)> CPlayScene::CreatePauseEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto director = Director::getInstance();
            auto scene = CPlayPauseScene::CreateScene("eeeeeeeee");
            this->addChild(scene);
        };
}