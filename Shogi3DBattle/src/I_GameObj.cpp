#include"I_GameObj.h"

void        I_GameObj::SetVertices(std::unique_ptr<I_Vertices> uniquePtr){_vertices.swap(uniquePtr);} // 頂点集合セット
I_Vertices* I_GameObj::GetVertices()                                     {return _vertices.get();}    // 頂点集合を返す

WorldMat* I_GameObj::GetWorldMat()                    {return _worldMat.get();}    // ワールド行列セット 

GameObjType I_GameObj::GetGameObjType(){return _gameObjType;} // ゲームオブジェクトタイプを返す

I_GameObj::I_GameObj(GameObjType gameObjType) : _gameObjType(gameObjType)
{
    _worldMat = std::make_unique<WorldMat>();
}