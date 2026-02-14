#ifndef PLAYLEVELSELECTSCENE_H
#define PLAYLEVELSELECTSCENE_H

#include "cocos2d.h"

// ========================================================================= //
// 難易度選択画面
// ========================================================================= //
class CPlayLevelSelectScene : public cocos2d::Scene
{
    CREATE_FUNC(CPlayLevelSelectScene);
    static CPlayLevelSelectScene* create(const std::string& aParameter);
public:
    static cocos2d::Scene* CreateScene(const std::string& aParameter);
    
    CPlayLevelSelectScene();
    virtual ~CPlayLevelSelectScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    void Initilize(const std::string& aParameter);
    std::function<void(Ref*)> CreateDecisionEvent();

private:
    std::string mParameter;
};

#endif // PLAYLEVELSELECTSCENE_H
