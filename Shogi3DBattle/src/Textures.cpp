#include"Textures.h"
#include"WoodTexture.h"
#include"Board5x5Texture.h"
#include"Board9x9Texture.h"
#include"WhiteTexture.h"
#include"CanMoveSquareEffectTexture.h"

// 木材テクスチャ作成
void Textures::CreateWoodTextures()
{
    _woodTextures.push_back(std::make_unique<WoodTexture>(226, 232,  75)); // 黄色
    _woodTextures.push_back(std::make_unique<WoodTexture>(220, 220, 220)); // 灰色
    _woodTextures.push_back(std::make_unique<WoodTexture>(140,  80,  36)); // 茶色
}

// オブジェクトごとのテクスチャ作成
void Textures::CreateDesignTextures()
{
    _designTextures.push_back(std::make_unique<Board5x5Texture>());
    _designTextures.push_back(std::make_unique<Board9x9Texture>());
    _designTextures.push_back(std::make_unique<I_Texture>());
}

// エフェクトのテクスチャ作成
void Textures::CreateEffectTextures()
{
    _effectTextures.push_back(std::make_unique<WhiteTexture>());
    _effectTextures.push_back(std::make_unique<CanMoveSquareEffectTexture>(nullptr));
}





// テクスチャ作成
void Textures::CreateTextures()
{
    CreateWoodTextures();
    CreateDesignTextures();
    CreateEffectTextures();
}

// 駒の動く範囲を色付けするテクスチャを作成
void Textures::CreateCanMoveEffectTextures(I_Piece* piece)
{
    _effectTextures.pop_back();
    _effectTextures.push_back(std::make_unique<CanMoveSquareEffectTexture>(piece));
}


// 木材テクスチャを返す
std::vector<I_Texture*> Textures::GetWoodTextures()
{
    std::vector<I_Texture*> woodTextures;
    for(auto& woodTexture : _woodTextures) woodTextures.push_back(woodTexture.get());

    return woodTextures;
}

// オブジェクトごとのテクスチャを返す
std::vector<I_Texture*> Textures::GetDesignTextures()
{
    std::vector<I_Texture*> boardLineTextures;
    for(auto& boardLineTexture : _designTextures) boardLineTextures.push_back(boardLineTexture.get());

    return boardLineTextures;
}

// エフェクトのテクスチャを返す
std::vector<I_Texture*> Textures::GetEffectTextures()
{
    std::vector<I_Texture*> effectTextures;
    for(auto& effectTexture : _effectTextures) effectTextures.push_back(effectTexture.get());

    return effectTextures;
}