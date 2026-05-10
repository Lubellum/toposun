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
    static cocos2d::Scene* CreateScene(const std::string& aParameter);
    
    CPlayScene();
    virtual ~CPlayScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    void Initilize(const std::string& aParameter);
    std::function<void(Ref*)> CreateDecisionEvent();
    std::function<void(Ref*)> CreatePauseEvent();

private:
    std::string mParameter;
};

#endif // PLAYSCENE_H
