#pragma once

enum class HeapType
{
    RTV, // レンダーターゲットビュー
    DSV, // デプスステンシルビュー
    CSU  // コンスタントバッファビュー、シェーダーリソースビュー、アンオーダーアクセスビュー
};