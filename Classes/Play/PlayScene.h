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
    void Initilize(const std::string& aParameter);
    void SetupUI(cocos2d::ui::Widget* aRoot);
    void SetupPlayer(cocos2d::ui::Widget* aRoot);
    tKeyboardEvent CreateKeyPressedEvent(cocos2d::ui::Widget* aRoot);
    tClickEvent CreateDecisionEvent();
    tClickEvent CreatePauseEvent();

private:
    std::string mParameter;
};

#endif // PLAYSCENE_H
