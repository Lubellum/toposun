#include "PlayResultScene.h"
#include "PlayScene.h"
#include "PlayLevelSelectScene.h"
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
CPlayResultScene* CPlayResultScene::create(const std::string& aParameter)
{
    auto* instance = CPlayResultScene::create();
    instance->Initilize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CPlayResultScene::CreateScene(const std::string& aParameter)
{
    return CPlayResultScene::create(aParameter);
}

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CPlayResultScene::CPlayResultScene()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CPlayResultScene::~CPlayResultScene()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
bool CPlayResultScene::init()
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
void CPlayResultScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlayResultScene::Initilize(const std::string& aParameter)
{
    mParameter = aParameter;
    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/playresult.json");
    this->addChild(root);
    auto image = dynamic_cast<cocos2d::ui::ImageView*>(
        root->getChildByName("image_bg"));
    
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
std::function<void(Ref*)> CPlayResultScene::CreatePlayEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto director = Director::getInstance();
            auto scene = CPlayScene::CreateScene("eeeeeeeee");
            auto transition = TransitionFade::create(0.5, scene);
            director->replaceScene(transition);
        };
}

// ------------------------------------------------------------------------- //
// プレイ難易度選択画面遷移イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayResultScene::CreateLevelSelectEvent()
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