#include"LanceVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// çÅÅ@í∏ì_èWçáçÏê¨
std::unique_ptr<I_Vertices> LanceVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 225.0f;
    float mmHeight       = 280.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}