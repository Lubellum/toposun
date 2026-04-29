#ifndef PLAYPAUSESCENE_H
#define PLAYPAUSESCENE_H

#include "cocos2d.h"

// ========================================================================= //
// ゲーム内容確認画面
// ========================================================================= //
class CPlayPauseScene : public cocos2d::Scene
{
    CREATE_FUNC(CPlayPauseScene);
    static CPlayPauseScene* create(const std::string& aParameter);
public:
    static cocos2d::Scene* CreateScene(const std::string& aParameter);
    
    CPlayPauseScene();
    virtual ~CPlayPauseScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    void Initilize(const std::string& aParameter);
    std::function<void(Ref*)> CreatePlayEvent();
    std::function<void(Ref*)> CreateLevelSelectEvent();

private:
    std::string mParameter;
};

#endif // PLAYPAUSESCENE_H
