#pragma once

#include"I_PieceButton.h"

class SelectPieceButton : public I_PieceButton
{
public:
    void                          ExeSelectedStateProcess() override; // 選択状態に合わせた処理実行
    std::unique_ptr<I_SceneState> ExePushButtonProcess   () override; // ボタン押下処理実行
};