#include "PlaySummaryScene.h"
#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "ui/UIText.h"
#include "cocostudio/CocoStudio.h"

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
    auto guiReader = cocostudio::GUIReader::getInstance();
    auto root = guiReader->widgetFromJsonFile("json/playsummary.json");
    this->addChild(root);
    auto image = dynamic_cast<cocos2d::ui::ImageView*>(root->getChildByName("image_bg"));
    image->addClickEventListener(CreateDecisionEvent());
    
    auto textLevel = dynamic_cast<cocos2d::ui::Text*>(root->getChildByName("text_level"));
    auto beforeSentence = textLevel->getString();
    auto value = cocos2d::StringUtils::format(beforeSentence.c_str(), mParameter.c_str());
    textLevel->setString(value);
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