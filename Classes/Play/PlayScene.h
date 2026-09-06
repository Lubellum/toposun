#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "cocos2d.h"

// ========================================================================= //
// プレイ画面
// ========================================================================= //
class CPlayScene : public cocos2d::Scene
{
    CREATE_FUNC(CPlayScene);
    static CPlayScene* create(const std::string& aParameter);
public:
    typedef std::function<void(Ref*)> tClickEvent;
    typedef std::function<bool(
        cocos2d::EventKeyboard::KeyCode,
        cocos2d::Event*)> tKeyboardEvent;

    static cocos2d::Scene* CreateScene(const std::string& aParameter);
    
    CPlayScene();
    virtual ~CPlayScene();

    virtual bool init() override;
    virtual void update(float delta) override;

private:
    void Initilize(const std::string& aParameter);
    void SetupUI(const cocos2d::ui::Widget* aRoot);
    void SetupPlayer(const cocos2d::ui::Widget* aRoot);
    cocos2d::Vec2 TileToWorld(const cocos2d::TMXTiledMap* aTiledMap, const cocos2d::Vec2 aCellPos);
    tKeyboardEvent CreateKeyPressedEvent(const cocos2d::ui::Widget* aRoot);
    tClickEvent CreateDecisionEvent();
    tClickEvent CreatePauseEvent();

    std::string mParameter;
};

#endif // PLAYSCENE_H
