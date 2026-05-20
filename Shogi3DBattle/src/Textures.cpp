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

// 将棋盤黒線テクスチャ作成
void Textures::CreateBoardLineTextures()
{
    _boardLineTextures.push_back(std::make_unique<Board5x5Texture>());
    _boardLineTextures.push_back(std::make_unique<Board9x9Texture>());
}




// テクスチャ作成
void Textures::CreateTextures()
{
    CreateWoodTextures();
    CreateBoardLineTextures();
}



// 木材テクスチャを返す
std::vector<I_Texture*> Textures::GetWoodTextures()
{
    std::vector<I_Texture*> woodTextures;
    for(auto& woodTexture : _woodTextures) woodTextures.push_back(woodTexture.get());

    return woodTextures;
}

// 将棋盤黒線テクスチャを返す
std::vector<I_Texture*> Textures::GetBoardLineTextures()
{
    std::vector<I_Texture*> boardLineTextures;
    for(auto& boardLineTexture : _boardLineTextures) boardLineTextures.push_back(boardLineTexture.get());

    return boardLineTextures;
}