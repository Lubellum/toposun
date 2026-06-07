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

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this, player](cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event* aEvent)
        {
            Vec2 position = player->getPosition();
            switch (aKeyCode)
            {
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                player->setPositionY(position.y + 50);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
                player->setPositionY(position.y - 50);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                player->setPositionX(position.x - 50);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_D:
                player->setPositionX(position.x + 50);
                break;
            default:
                break;
            }
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