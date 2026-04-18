#include"I_GameObj.h"

void      I_GameObj::SetVertices(std::unique_ptr<Vertices> uniquePtr){_vertices.swap(uniquePtr);} // 頂点集合セット
Vertices* I_GameObj::GetVertices()                    {return _vertices.get();}    // 頂点集合を返す

WorldMat* I_GameObj::GetWorldMat()                    {return _worldMat.get();}    // ワールド行列セット 

// ゲームオブジェクトタイプセット
void I_GameObj::SetGameObjType(GameObjType type) 
{
    _gameObjType = type;
    _vertices->SetMulDesignTexId(static_cast<unsigned char>(type));

} 
GameObjType I_GameObj::GetGameObjType()                 {return _gameObjType;} // ゲームオブジェクトタイプを返す

I_GameObj::I_GameObj()
{
    _worldMat = std::make_unique<WorldMat>();
}