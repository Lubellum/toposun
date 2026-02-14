#ifndef PLAYSUMMARYSCENE_H
#define PLAYSUMMARYSCENE_H

#include "cocos2d.h"

class CPlaySummaryScene : public cocos2d::Scene
{
    CREATE_FUNC(CPlaySummaryScene);
    static CPlaySummaryScene* create(const std::string& aParameter);
public:
    static cocos2d::Scene* CreateScene(const std::string& aParameter);
    
    CPlaySummaryScene();
    virtual ~CPlaySummaryScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    void Initilize(const std::string& aParameter);
    std::function<void(Ref*)> CreateDecisionEvent();

private:
    std::string mParameter;
};

#endif // PLAYSUMMARYSCENE_H
