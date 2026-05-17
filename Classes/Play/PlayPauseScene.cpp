#include "PlayScene.h"
#include "PlayLevelSelectScene.h"
#include "PlayPauseScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "ui/UIText.h"
#include "ui/UIHelper.h"
#include "cocostudio/CocoStudio.h"

// todo: 消す
USING_NS_CC;

// ========================================================================= //
// ゲーム内容確認画面
// ========================================================================= //

// ------------------------------------------------------------------------- //
// 生成
// ------------------------------------------------------------------------- //
CPlayPauseScene* CPlayPauseScene::create(const std::string& aParameter)
{
    auto* instance = CPlayPauseScene::create();
    instance->Initilize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CPlayPauseScene::CreateScene(const std::string& aParameter)
{
    return CPlayPauseScene::create(aParameter);
}

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CPlayPauseScene::CPlayPauseScene()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CPlayPauseScene::~CPlayPauseScene()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
bool CPlayPauseScene::init()
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
void CPlayPauseScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlayPauseScene::Initilize(const std::string& aParameter)
{
    mParameter = aParameter;
    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/playpause.json");
    this->addChild(root);
    
    auto textLevel = dynamic_cast<cocos2d::ui::Text*>(
        root->getChildByName("text_level"));
    auto beforeSentence = textLevel->getString();
    auto value = cocos2d::StringUtils::format(
        beforeSentence.c_str(), mParameter.c_str());
    textLevel->setString(value);

    auto touchPanelPlay = dynamic_cast<cocos2d::ui::Layout*>(
        cocos2d::ui::Helper::seekWidgetByName(root, "panel_touch_play"));
    touchPanelPlay->addClickEventListener(CreatePlayEvent());

    auto touchPanelLevelSelect = dynamic_cast<cocos2d::ui::Layout*>(
        cocos2d::ui::Helper::seekWidgetByName(root, "panel_touch_levelselect"));
    touchPanelLevelSelect->addClickEventListener(CreateLevelSelectEvent());
}

// ------------------------------------------------------------------------- //
// プレイ画面遷移イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayPauseScene::CreatePlayEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            this->removeFromParent();
        };
}

// ------------------------------------------------------------------------- //
// プレイ難易度選択画面遷移イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayPauseScene::CreateLevelSelectEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto director = Director::getInstance();
            auto scene = CPlayLevelSelectScene::CreateScene("eeeeeeeee");
            auto transition = TransitionFade::create(0.5, scene);
            director->replaceScene(transition);
        };
}