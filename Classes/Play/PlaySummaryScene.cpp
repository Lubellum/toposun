#include "PlaySummaryScene.h"
#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"

// todo: 消す
USING_NS_CC;

// ========================================================================= //
// ゲーム内容確認画面
// ========================================================================= //

// ------------------------------------------------------------------------- //
// 生成
// ------------------------------------------------------------------------- //
CPlaySummaryScene* CPlaySummaryScene::create(const std::string& aParameter)
{
    auto* instance = CPlaySummaryScene::create();
    instance->Initilize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CPlaySummaryScene::CreateScene(const std::string& aParameter)
{
    return CPlaySummaryScene::create(aParameter);
}

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CPlaySummaryScene::CPlaySummaryScene()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CPlaySummaryScene::~CPlaySummaryScene()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
bool CPlaySummaryScene::init()
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
void CPlaySummaryScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlaySummaryScene::Initilize(const std::string& aParameter)
{
    mParameter = aParameter;
    auto image = cocos2d::ui::ImageView::create("playSummary_bg.png");
    image->setTouchEnabled(true);
    image->addClickEventListener(CreateDecisionEvent());
    image->setName("playSummary_bg");
    image->setAnchorPoint(Vec2(0.0, 0.0));
    image->setPosition(Vec2(0.0, 0.0));
    this->addChild(image, 0);
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlaySummaryScene::CreateDecisionEvent()
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