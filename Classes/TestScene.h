#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "cocos2d.h"

class CTestScene : public cocos2d::Scene
{
    CREATE_FUNC(CTestScene);
public:
    static cocos2d::Scene* createScene();
    
    CTestScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    std::function<void(Ref*)> CreateDecisionEvent(int aLevel);

private:
    // 難易度
    enum class tLevel : int
    {
        nEasy,
        nNormal,
        nHard,
        nNum
    };

    cocos2d::Size mVisibleSize;
    cocos2d::Vec2 mOrigin;
    float mRemainingTime;
    std::string mParameter;
};

#endif // TESTSCENE_H
