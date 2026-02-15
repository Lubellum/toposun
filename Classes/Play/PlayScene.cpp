#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"

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
    auto image = cocos2d::ui::ImageView::create("play_bg.png");
    image->setTouchEnabled(true);
    image->addClickEventListener(CreateDecisionEvent());
    image->setName("play_bg");
    image->setAnchorPoint(Vec2(0.0, 0.0));
    image->setPosition(Vec2(0.0, 0.0));
    this->addChild(image, 0);
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayScene::CreateDecisionEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
        };
}