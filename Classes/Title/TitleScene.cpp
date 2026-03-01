#include "TitleScene.h"
#include "./Play/PlayLevelSelectScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

// ========================================================================= //
// タイトル画面
// ========================================================================= //

// ------------------------------------------------------------------------- //
// 生成
// ------------------------------------------------------------------------- //
CTitleScene* CTitleScene::create(const std::string& aParameter)
{
    auto* instance = CTitleScene::create();
    instance->Initilize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CTitleScene::CreateScene()
{
    return CTitleScene::create(std::string());
}

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CTitleScene::CTitleScene()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CTitleScene::~CTitleScene()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
bool CTitleScene::init()
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
void CTitleScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CTitleScene::Initilize(const std::string& aParameter)
{
    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/title.json");
    this->addChild(root);
    auto image = dynamic_cast<cocos2d::ui::ImageView*>(root->getChildByName("title_bg"));
    image->addClickEventListener(CreateDecisionEvent());
}


// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CTitleScene::CreateDecisionEvent()
{
    return [](cocos2d::Ref*)
        {
            // cocos2d::log("aaaaaaaaaaaaa");
            auto director = Director::getInstance();
            auto scene = CPlayLevelSelectScene::CreateScene("cccccccccc");
            auto transition = TransitionFade::create(0.5, scene);
            director->replaceScene(transition);
        };
}