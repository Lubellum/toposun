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

    void Initilize();
    cocos2d::Vec2 CPlayHero::TileToWorld(const cocos2d::TMXTiledMap* aTiledMap,
        const cocos2d::Vec2 aCellPos);
    cocos2d::Vec2 CPlayHero::WorldToTile(const cocos2d::TMXTiledMap* aTiledMap,
        const cocos2d::Vec2 aWorldPos);
    void SetupHero(const cocos2d::ui::Widget* aRoot);
    void MoveHero(cocos2d::ui::Layout* aHero,
        cocos2d::ui::Layout* aHeroDummy,
        const cocos2d::EventKeyboard::KeyCode aKeyCode,
        const cocos2d::ui::Widget* aRoot,
        const cocos2d::Size aVisibleSize,
        const cocos2d::Vec2 aVisibleOrigin,
        const cocos2d::ui::Layout* aHeroDummyLocator
    );
};

#endif // PLAYHERO_H
