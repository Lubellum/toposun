#include "stdafx.h"
#include "PlayField.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoStudio.h"

// todo: 消す
USING_NS_CC;

// ========================================================================= //
// 【プレイ】フィールド
// ========================================================================= //

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CPlayField::CPlayField()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CPlayField::~CPlayField()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlayField::Initilize(const std::string& aParameter, cocos2d::ui::Widget* aRoot)
{
    auto* mapStage = cocos2d::TMXTiledMap::create("map/stage1.tmx");
    auto* panelStage = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_stage"));
    panelStage->addChild(mapStage);
    auto* mapLogic = cocos2d::TMXTiledMap::create("map/stage1_logic.tmx");
    mapLogic->setName("stage1_logic");
    auto* panelLogic = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_logic"));
    panelLogic->addChild(mapLogic);
}

// ------------------------------------------------------------------------- //
// TiledMap座標からWorld座標への変換
// ------------------------------------------------------------------------- //
cocos2d::Vec2 CPlayField::TileToWorld(const cocos2d::TMXTiledMap* aTiledMap,
    const cocos2d::Vec2 aCellPos)
{
    const auto mapSize = aTiledMap->getMapSize();
    const auto tileSize = aTiledMap->getTileSize();

    return cocos2d::Vec2(
        tileSize.width * aCellPos.x,
        tileSize.height * ((mapSize.height - aCellPos.y) - 1)
    );
}

// ------------------------------------------------------------------------- //
// World座標からTiledMap座標への変換
// ------------------------------------------------------------------------- //
cocos2d::Vec2 CPlayField::WorldToTile(const cocos2d::TMXTiledMap* aTiledMap,
    const cocos2d::Vec2 aWorldPos)
{
    const auto mapSize = aTiledMap->getMapSize();
    const auto tileSize = aTiledMap->getTileSize();

    return cocos2d::Vec2(
        std::floor(aWorldPos.x / tileSize.width),
        ((mapSize.height - 1) - std::floor(aWorldPos.y / tileSize.height))
    );
}