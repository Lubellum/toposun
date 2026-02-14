#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "cocos2d.h"

class CTitleScene : public cocos2d::Scene
{
    CREATE_FUNC(CTitleScene);
public:
    static cocos2d::Scene* createScene();
    
    CTitleScene();
    virtual ~CTitleScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    std::function<void(Ref*)> CreateDecisionEvent();
};

#endif // TITLESCENE_H
