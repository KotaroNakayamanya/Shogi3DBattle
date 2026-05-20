#pragma once

#include"I_Texture.h"
#include<memory>

class Textures
{
private:
    std::vector<std::unique_ptr<I_Texture>> _woodTextures;      // 木材テクスチャ
    std::vector<std::unique_ptr<I_Texture>> _boardLineTextures; // 将棋盤黒線テクスチャ

    void CreateWoodTextures();      // 木材テクスチャ作成
    void CreateBoardLineTextures(); // 将棋盤黒線テクスチャ作成

public:
    void CreateTextures(); // テクスチャ作成

    std::vector<I_Texture*> GetWoodTextures();      // 木材テクスチャを返す
    std::vector<I_Texture*> GetBoardLineTextures(); // 将棋盤黒線テクスチャを返す
};