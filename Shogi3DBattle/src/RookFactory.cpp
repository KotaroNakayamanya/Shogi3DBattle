#include"RookFactory.h"
#include"Rook.h"
#include"RookVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"

// 飛　作成
std::unique_ptr<GameObj> RookFactory::CreateUniquePtr()
{
    std::unique_ptr<Rook> uniquePtr = std::make_unique<Rook>();

    // 頂点集合作成
    _verticesFactory.reset(new RookVerticesFactory());
    auto kingVerticesUniquePtr =
        FactoryMethod::GetDownCastUniquePtr<Vertices, IBufferedDataFactory<Vert>>(_verticesFactory.get());
    auto kingVerticesPtr = kingVerticesUniquePtr.get();
    kingVerticesUniquePtr.release();
    uniquePtr->SetVertices(kingVerticesPtr);

    // ワールド行列作成
    _matFactory.reset(new WorldMatFactory());
    auto worldMatUniquePtr = 
        FactoryMethod::GetDownCastUniquePtr<WorldMat, IBufferedDataFactory<DirectX::XMMATRIX>>(_matFactory.get());
    auto worldMatPtr = worldMatUniquePtr.get();
    worldMatUniquePtr.release();
    uniquePtr->SetWorldMat(worldMatPtr);

    return uniquePtr;
}