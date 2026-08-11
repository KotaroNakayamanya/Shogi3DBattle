#include"I_Vertices.h"

void I_Vertices::SetGameObjId     (unsigned char id){for(auto& vert : _datas) vert.gameObjId      = id;} // ゲームオブジェクトIDセット
void I_Vertices::SetBasicTexId    (unsigned char id){for(auto& vert : _datas) vert.basicTexId     = id;} // 基本テクスチャセット
void I_Vertices::SetMulDesignTexId(unsigned char id){for(auto& vert : _datas) vert.mulDesignTexId = id;} // 乗算デザインテクスチャセット
void I_Vertices::SetMulEffectTexId(unsigned char id){for(auto& vert : _datas) vert.mulEffectTexId = id;} // エフェクトテクスチャIDセット