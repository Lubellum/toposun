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

// ------------------------------------------------------------------------- //
// 初期位置取得
// ------------------------------------------------------------------------- //
cocos2d::Vec2 CPlayField::GetSpawnPosition(const cocos2d::ui::Widget* aRoot)
{
    const auto* panelLogic = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_logic"));
    const auto* mapLogic = dynamic_cast<cocos2d::TMXTiledMap*>(
        panelLogic->getChildByName("stage1_logic"));
    const auto mapSize = mapLogic->getMapSize();
    const auto tileSize = mapLogic->getTileSize();
    auto* mapLayer = mapLogic->getLayer("Layer1");
    auto heroPosition = cocos2d::Vec2(cocos2d::Vec2::ZERO);
    for (size_t y = 0; y < mapSize.height; y++)
    {
        for (size_t x = 0; x < mapSize.width; x++)
        {
            auto gid = mapLayer->getTileGIDAt(cocos2d::Vec2(x, y));
            if (gid == 0)
            {
                continue;
            }
            const auto properties = mapLogic->getPropertiesForGID(gid); // タイルセット種の情報
            const auto propertiesDict = properties.asValueMap();
            const auto it = propertiesDict.find("type");
            if (it != propertiesDict.end())
            {
                const auto value = it->second.asInt();
                // Heroの初期位置マスの種別判定
                if (value == 1)
                {
                    // Heroの初期位置座標を取得
                    heroPosition = CPlayField::TileToWorld(mapLogic, cocos2d::Vec2(x, y));
                    break;
                }
            }
        }
    }

    return heroPosition;
}

// ------------------------------------------------------------------------- //
// 壁の当たり判定
// ------------------------------------------------------------------------- //
bool CPlayField::IsHitWall(cocos2d::ui::Layout* aTarget, const cocos2d::ui::Widget* aRoot)
{
    auto position = aTarget->getPosition();

    const auto* panelLogic = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_logic"));
    const auto* mapLogic = dynamic_cast<cocos2d::TMXTiledMap*>(
        panelLogic->getChildByName("stage1_logic"));
    auto* mapLayer = mapLogic->getLayer("Layer1");

    auto gid = mapLayer->getTileGIDAt(CPlayField::WorldToTile(mapLogic, position));
    if (gid != 0)
    {
        const auto properties = mapLogic->getPropertiesForGID(gid);
        const auto propertiesDict = properties.asValueMap();
        const auto it = propertiesDict.find("type");
        if (it != propertiesDict.end())
        {
            const auto value = it->second.asInt();
            // 壁の初期位置マスの種別判定
            if (value == 2)
            {
                return true;
            }
        }
    }
    return false;
}