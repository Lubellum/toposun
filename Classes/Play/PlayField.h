#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "cocos2d.h"

// ========================================================================= //
// プレイ画面
// ========================================================================= //
class CPlayField : public cocos2d::Scene
{
public:
    CPlayField();
    virtual ~CPlayField();

    void Initilize(const std::string& aParameter, cocos2d::ui::Widget* aRoot);
private:

    std::string mParameter;
};

#endif // PLAYFIELD_H
