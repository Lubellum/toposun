#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "cocos2d.h"

// ========================================================================= //
// タイトル画面
// ========================================================================= //
class CTitleScene : public cocos2d::Scene
{
    CREATE_FUNC(CTitleScene);
    static CTitleScene* create(const std::string& aParameter);
public:
    static cocos2d::Scene* CreateScene();
    
    CTitleScene();
    virtual ~CTitleScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    void Initilize(const std::string& aParameter);
    std::function<void(Ref*)> CreateDecisionEvent();

private:
    std::string mParameter;
};

#endif // TITLESCENE_H
