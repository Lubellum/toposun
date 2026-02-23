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
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CTitleScene::createScene()
{
    return CTitleScene::create();
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

    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/title.json");
    this->addChild(root);
    auto image = dynamic_cast<cocos2d::ui::ImageView*>(root->getChildByName("title_bg"));
    image->addClickEventListener(CreateDecisionEvent());

#if 0
    auto image = cocos2d::ui::ImageView::create("title_bg.png");
    image->setTouchEnabled(true);
    image->addClickEventListener(CreateDecisionEvent());
    image->setName("title_bg");
    image->setAnchorPoint(Vec2(0.0, 0.0));
    image->setPosition(Vec2(0.0, 0.0));
    this->addChild(image, 0);
#endif

    return true;
}

// ------------------------------------------------------------------------- //
// 更新
// ------------------------------------------------------------------------- //
void CTitleScene::update(float delta)
{

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