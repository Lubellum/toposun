#include "stdafx.h"
#include "PlayHero.h"
#include "PlayField.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoStudio.h"

// todo: 消す
USING_NS_CC;

// ========================================================================= //
// 【プレイ】主人公
// ========================================================================= //

// ------------------------------------------------------------------------- //
// コンストラクタ
// ------------------------------------------------------------------------- //
CPlayHero::CPlayHero()
{
}

// ------------------------------------------------------------------------- //
// デストラクタ
// ------------------------------------------------------------------------- //
CPlayHero::~CPlayHero()
{
}

// ------------------------------------------------------------------------- //
// 初期化
// ------------------------------------------------------------------------- //
void CPlayHero::Initilize()
{

}

// ------------------------------------------------------------------------- //
// Hero設定
// ------------------------------------------------------------------------- //
void CPlayHero::SetupHero(const cocos2d::ui::Widget* aRoot)
{
    auto* hero = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_hero"));
    hero->setPosition(CPlayField::GetSpawnPosition(aRoot));
}

// ------------------------------------------------------------------------- //
// 移動処理
// ------------------------------------------------------------------------- //
void CPlayHero::MoveHero(cocos2d::ui::Layout* aHero,
    cocos2d::ui::Layout* aHeroDummy,
    const cocos2d::EventKeyboard::KeyCode aKeyCode,
    const cocos2d::ui::Widget* aRoot,
    const cocos2d::Size aVisibleSize,
    const cocos2d::Vec2 aVisibleOrigin,
    const cocos2d::ui::Layout* aHeroDummyLocator
)
{
    // 移動処理
    auto position = aHero->getPosition();
    auto positionDummy = aHeroDummy->getPosition();
    auto movePosition = cocos2d::Vec2::ZERO;

    switch (aKeyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_W: // 上
        movePosition.y = 40;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S: // 下
        movePosition.y = -40;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A: // 左
        movePosition.x = -40;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D: // 右
        movePosition.x = 40;
        break;
    default:
        break;
    }

    const auto* panelLogic = dynamic_cast<cocos2d::ui::Layout*>(
        aRoot->getChildByName("panel_logic"));
    const auto* mapLogic = dynamic_cast<cocos2d::TMXTiledMap*>(
        panelLogic->getChildByName("stage1_logic"));
    auto* mapLayer = mapLogic->getLayer("Layer1");

    auto gid = mapLayer->getTileGIDAt(CPlayField::WorldToTile(mapLogic, (position + movePosition)));
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
                // Heroの初期位置座標を取得
                movePosition = cocos2d::Vec2::ZERO;
            }
        }
    }

    position += movePosition;

    // 補正処理
    // 上
    if (position.y + aHero->getContentSize().height > aVisibleSize.height)
    {
        position.y = aVisibleSize.height - aHero->getContentSize().height;
    }
    // 下
    if (position.y < aVisibleOrigin.y)
    {
        position.y = aVisibleOrigin.y;
    }
    // プレイヤー(左側の頂点)が左端を超えているかどうか
    if (position.x < aVisibleOrigin.x)
    {
        const int dt = abs(position.x - aVisibleOrigin.x);
        positionDummy.y = position.y;
        positionDummy.x = aVisibleSize.width - dt;
        if ((position.x + aHero->getContentSize().width) < aVisibleOrigin.x)
        {
            position.x = positionDummy.x;
            positionDummy = aHeroDummyLocator->getPosition();
        }
    }
    // プレイヤー(右側の頂点)が右端を超えているかどうか
    else if (position.x + aHero->getContentSize().width > aVisibleSize.width)
    {
        const int dt = abs((position.x + aHero->getContentSize().width) - aVisibleSize.width);
        positionDummy.y = position.y;
        positionDummy.x = aVisibleOrigin.x - aHeroDummy->getContentSize().width + dt;
        if (position.x > aVisibleSize.width)
        {
            position.x = positionDummy.x;
            positionDummy = aHeroDummyLocator->getPosition();
        }
    }
    else
    {
        positionDummy = aHeroDummyLocator->getPosition();
    }

    aHero->setPosition(position);
    aHeroDummy->setPosition(positionDummy);
}