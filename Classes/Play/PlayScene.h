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
    typedef std::function<bool(
        cocos2d::EventKeyboard::KeyCode,
        cocos2d::Event*)> tKeyboardEvent;

    static cocos2d::Scene* CreateScene(const std::string& aParameter);
    
    CPlayScene();
    virtual ~CPlayScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    void Initilize(const std::string& aParameter);
    std::function<void(Ref*)> CreateDecisionEvent();
    std::function<void(Ref*)> CreatePauseEvent();
    tKeyboardEvent CreateKeyPressedEvent(
        cocos2d::ui::Layout* aPlayer,
        cocos2d::Size aVisibleSize,
        cocos2d::Vec2 aVisibleOrigin);

private:
    std::string mParameter;
};

#endif // PLAYSCENE_H
