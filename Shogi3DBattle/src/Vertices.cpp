#include"Vertices.h"

void Vertices::SetGameObjId     (unsigned char id){for(auto& vert : _datas) vert.gameObjId      = id;} // ゲームオブジェクトIDセット
void Vertices::SetBasicTexId    (unsigned char id){for(auto& vert : _datas) vert.basicTexId     = id;} // 基本テクスチャセット
void Vertices::SetMulDesignTexId(unsigned char id){for(auto& vert : _datas) vert.mulDesignTexId = id;} // 乗算デザインテクスチャセット