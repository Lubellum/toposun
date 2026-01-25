#include "PlayLevelSelectScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"

USING_NS_CC;

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
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CPlayLevelSelectScene::createScene()
{
    return CPlayLevelSelectScene::create();
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
bool CPlayLevelSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto image = cocos2d::ui::ImageView::create("title_bg.png");
    image->setTouchEnabled(true);
    image->addClickEventListener(CreateDecisionEvent());
    image->setName("title_bg");
    image->setAnchorPoint(Vec2(0.0, 0.0));
    image->setPosition(Vec2(0.0, 0.0));
    this->addChild(image, 0);

    return true;
}

// ------------------------------------------------------------------------- //
// 更新
// ------------------------------------------------------------------------- //
void CPlayLevelSelectScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayLevelSelectScene::CreateDecisionEvent()
{
    return [](cocos2d::Ref*)
        {
            cocos2d::log("aaaaaaaaaaaaa");
        };
}