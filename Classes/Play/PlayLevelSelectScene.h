#ifndef PLAYLEVELSELECTSCENE_H
#define PLAYLEVELSELECTSCENE_H

#include "cocos2d.h"

class CPlayLevelSelectScene : public cocos2d::Scene
{
    CREATE_FUNC(CPlayLevelSelectScene);
public:
    static cocos2d::Scene* createScene();
    
    CPlayLevelSelectScene();
    virtual ~CPlayLevelSelectScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    

    std::function<void(Ref*)> CreateDecisionEvent();
};

#endif // PLAYLEVELSELECTSCENE_H
