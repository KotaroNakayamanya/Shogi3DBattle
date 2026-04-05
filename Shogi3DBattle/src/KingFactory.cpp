#include"KingFactory.h"
#include"Piece.h"
#include"KingVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"

// 王　作成
std::unique_ptr<GameObj> KingFactory::CreateUniquePtr()
{
    std::unique_ptr<Piece> uniquePtr = std::make_unique<Piece>();

    // 頂点集合作成
    _verticesFactory.reset(new KingVerticesFactory());
    auto vertices =
        FactoryMethod::GetDownCastUniquePtr<Vertices, IBufferedDataFactory<Vert>>(_verticesFactory.get());
    auto verticesPtr = vertices.get();
    vertices.release();
    uniquePtr->SetVertices(verticesPtr);

    // ワールド行列作成
    _matFactory.reset(new WorldMatFactory());
    auto mat = 
        FactoryMethod::GetDownCastUniquePtr<WorldMat, IBufferedDataFactory<DirectX::XMMATRIX>>(_matFactory.get());
    auto matPtr = mat.get();
    mat.release();
    uniquePtr->SetWorldMat(matPtr);

    return uniquePtr;
}