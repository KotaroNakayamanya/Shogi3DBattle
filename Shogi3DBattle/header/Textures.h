#pragma once

#include"I_Texture.h"
#include<memory>
#include"I_Piece.h"

class Textures
{
private:
    std::vector<std::unique_ptr<I_Texture>> _woodTextures;   // 木材テクスチャ
    std::vector<std::unique_ptr<I_Texture>> _designTextures; // オブジェクトごとのテクスチャ
    std::vector<std::unique_ptr<I_Texture>> _effectTextures; // エフェクトのテクスチャ

    void CreateWoodTextures();   // 木材テクスチャ作成
    void CreateDesignTextures(); // オブジェクトごとのテクスチャ作成
    void CreateEffectTextures(); // オブジェクトごとのテクスチャ作成

public:
    void CreateTextures(); // テクスチャ作成
    void CreateCanMoveEffectTextures(I_Piece* piece); // 駒の動く範囲を色付けするテクスチャを作成

    std::vector<I_Texture*> GetWoodTextures();   // 木材テクスチャを返す
    std::vector<I_Texture*> GetDesignTextures(); // オブジェクトごとのテクスチャを返す
    std::vector<I_Texture*> GetEffectTextures(); // エフェクトのテクスチャを返す
};