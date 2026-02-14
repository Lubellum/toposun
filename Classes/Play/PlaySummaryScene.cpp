#include "PlaySummaryScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"

USING_NS_CC;

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
    if ( !Scene::init() )
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
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlaySummaryScene::CreateDecisionEvent()
{
    return [this](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
        };
}