#include "PlayLevelSelectScene.h"
#include "PlaySummaryScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

// ========================================================================= //
// 難易度選択画面
// ========================================================================= //

// ------------------------------------------------------------------------- //
// 生成
// ------------------------------------------------------------------------- //
CPlayLevelSelectScene* CPlayLevelSelectScene::create(const std::string& aParameter)
{
    auto* instance = CPlayLevelSelectScene::create();
    instance->Initilize(aParameter);
    return instance;
}

// ------------------------------------------------------------------------- //
// シーン生成
// ------------------------------------------------------------------------- //
Scene* CPlayLevelSelectScene::CreateScene(const std::string& aParameter)
{
    return CPlayLevelSelectScene::create(aParameter);
}

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
// 初期化
// ------------------------------------------------------------------------- //
bool CPlayLevelSelectScene::init()
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
void CPlayLevelSelectScene::update(float delta)
{

}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlayLevelSelectScene::Initilize(const std::string& aParameter)
{
    mParameter = aParameter;

    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/playlevelselect.json");
    this->addChild(root);

    auto touchPanels = dynamic_cast<cocos2d::ui::Layout*>(root->getChildByName("panel_touches"));
    auto children = touchPanels->getChildren();
    for (int i = 0; i < children.size(); ++i)
    {
        auto child = dynamic_cast<cocos2d::ui::Layout*>(children.at(i));
        child->addClickEventListener(CreateDecisionEvent(i));
    }
}

// ------------------------------------------------------------------------- //
// 決定イベント生成
// ------------------------------------------------------------------------- //
std::function<void(Ref*)> CPlayLevelSelectScene::CreateDecisionEvent(int aLevel)
{
    return [this, aLevel](cocos2d::Ref*)
        {
            cocos2d::log(mParameter.c_str());
            auto director = Director::getInstance();
            auto scene = CPlaySummaryScene::CreateScene(std::to_string(aLevel));
            auto transition = TransitionFade::create(0.5, scene);
            director->replaceScene(transition);
        };
}