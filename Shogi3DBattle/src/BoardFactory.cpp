#include"BoardFactory.h"
#include"BoardVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"
#include"Board.h"
#include"VertStruct.h"

// 将棋盤作成
std::unique_ptr<I_GameObj> BoardFactory::CreateUniquePtr()
{   
    std::unique_ptr<Board> uniquePtr = std::make_unique<Board>();

    // ゲームオブジェクトタイプ　9×9将棋盤をセット
    uniquePtr->SetGameObjType(GameObjType::BOARD_99);

    // 頂点集合作成
    _verticesFactory.reset(new BoardVerticesFactory());
    auto vertices =
        FactoryMethod::GetDownCastUniquePtr<Vertices, IBufferedDataFactory>(_verticesFactory.get());
    auto verticesPtr = vertices.get();
    vertices.release();
    uniquePtr->SetVertices(verticesPtr);

    // ワールド行列作成
    _matFactory.reset(new WorldMatFactory());
    auto mat = 
        FactoryMethod::GetDownCastUniquePtr<WorldMat, IBufferedDataFactory>(_matFactory.get());
    auto matPtr = mat.get();
    mat.release();
    uniquePtr->SetWorldMat(matPtr);
    
    return uniquePtr;
}