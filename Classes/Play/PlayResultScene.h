#ifndef PLAYRESULTSCENE_H
#define PLAYRESULTSCENE_H

#include "cocos2d.h"

// ========================================================================= //
// ゲーム内容確認画面
// ========================================================================= //
class CPlayResultScene : public cocos2d::Scene
{
    CREATE_FUNC(CPlayResultScene);
    static CPlayResultScene* create(const std::string& aParameter);
public:
    static cocos2d::Scene* CreateScene(const std::string& aParameter);
    
    CPlayResultScene();
    virtual ~CPlayResultScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    void Initilize(const std::string& aParameter);
    std::function<void(Ref*)> CreatePlayEvent();
    std::function<void(Ref*)> CreateLevelSelectEvent();

private:
    std::string mParameter;
};

#endif // PLAYRESULTSCENE_H
