#include "stdafx.h"
#include "PlayHero.h"
#include "PlayField.h"
#include "SimpleAudioEngine.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoStudio.h"


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
void CPlayHero::Initialize()
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
    const cocos2d::EventKeyboard::KeyCode aKeyCode,
    const cocos2d::ui::Widget* aRoot,
    const cocos2d::Size aVisibleSize,
    const cocos2d::Vec2 aVisibleOrigin
)
{
    // 移動処理
    auto position = aHero->getPosition();
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

    if (CPlayField::IsHitWall( (position + movePosition), aRoot))
    {
        movePosition = cocos2d::Vec2::ZERO;
    }

    position += movePosition;

    aHero->setPosition(position);
}