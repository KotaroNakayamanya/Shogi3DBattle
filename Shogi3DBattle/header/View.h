#pragma once

class View
{
public:
    enum ViewType // ビュータイプ　ビュー作成時に使用
    {
        RTV, // レンダーターゲットビュー
        DSV, // デプスステンシルビュー
        CBV, // コンスタントバッファビュー
        SRV, // シェーダーリソースビュー
        UAV  // アンオーダーアクセスビュー
    };

    View(){}
    ~View(){}
};