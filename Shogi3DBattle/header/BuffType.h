#pragma once

enum class BuffType
{
    DEPTH_STENCIL, // デプスステンシルバッファ
    VERTEX,        // 頂点バッファ
    INDEX,         // インデックスバッファ
    CONSTANT,      // コンスタントバッファ
    TEXTURE,       // テクスチャバッファ
    RENDER_TEX     // レンダーテクスチャバッファ
};