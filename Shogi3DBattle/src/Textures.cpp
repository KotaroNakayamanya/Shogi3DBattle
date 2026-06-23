#include"Textures.h"
#include"WoodTexture.h"
#include"Board5x5Texture.h"
#include"Board9x9Texture.h"

// 木材テクスチャ作成
void Textures::CreateWoodTextures()
{
    _woodTextures.push_back(std::make_unique<WoodTexture>(226, 232,  75)); // 黄色
    _woodTextures.push_back(std::make_unique<WoodTexture>(220, 220, 220)); // 灰色
}

// オブジェクトごとのテクスチャ作成
void Textures::CreateDesignTextures()
{
    _designTextures.push_back(std::make_unique<Board5x5Texture>());
    _designTextures.push_back(std::make_unique<Board9x9Texture>());
    _designTextures.push_back(std::make_unique<I_Texture>());
}




// テクスチャ作成
void Textures::CreateTextures()
{
    CreateWoodTextures();
    CreateDesignTextures();
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