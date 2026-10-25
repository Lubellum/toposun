#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "cocos2d.h"

// ========================================================================= //
// 【プレイ】フィールド
// ========================================================================= //
class CPlayField : public cocos2d::Scene
{
public:
    CPlayField();
    virtual ~CPlayField();

    void Initilize(const std::string& aParameter, cocos2d::ui::Widget* aRoot);
    static cocos2d::Vec2 TileToWorld(const cocos2d::TMXTiledMap* aTiledMap,
        const cocos2d::Vec2 aCellPos);
    static cocos2d::Vec2 WorldToTile(const cocos2d::TMXTiledMap* aTiledMap,
        const cocos2d::Vec2 aWorldPos);
    static cocos2d::Vec2 GetSpawnPosition(const cocos2d::ui::Widget* aRoot);
    bool IsHitWall(cocos2d::ui::Layout* aTarget, const cocos2d::ui::Widget* aRoot);


private:

    std::string mParameter;
};

#endif // PLAYFIELD_H
