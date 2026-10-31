#ifndef PLAYHERO_H
#define PLAYHERO_H

#include "cocos2d.h"

// ========================================================================= //
// 【プレイ】主人公
// ========================================================================= //
class CPlayHero
{
public:
    CPlayHero();
    virtual ~CPlayHero();

    void Initialize();

    void SetupHero(const cocos2d::ui::Widget* aRoot);
    void MoveHero(cocos2d::ui::Layout* aHero,
        const cocos2d::EventKeyboard::KeyCode aKeyCode,
        const cocos2d::ui::Widget* aRoot,
        const cocos2d::Size aVisibleSize,
        const cocos2d::Vec2 aVisibleOrigin
    );
};

#endif // PLAYHERO_H
