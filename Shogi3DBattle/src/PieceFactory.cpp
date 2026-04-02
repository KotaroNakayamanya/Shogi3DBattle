#include"PieceFactory.h"
#include<array>
#include<algorithm>
#include"VecCalc.h"

// 駒作成
void PieceFactory::CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UCHAR objId)
{
    // 将棋オブジェクトIDセット
    shogiObj->SetObjId(objId);

    // 使用する文字テクスチャのIDをセット
    UCHAR texId = shogiObjType;
    shogiObj->SetTexId(texId);   

    // 駒の種類ごとの大きさをミリメートルで格納
    float mmBottomWidth;
    float mmHeight;
    switch (shogiObjType)
    {
    case ShogiObj::KING:
        mmBottomWidth  = 285.0f;
        mmHeight = 320.0f;
        break;
    
    case ShogiObj::ROOK:
    case ShogiObj::BISHOP:
        mmBottomWidth  = 260.0f;
        mmHeight = 300.0f;
        break;

    case ShogiObj::GOLD:
    case ShogiObj::SILVER:
        mmBottomWidth  = 250.0f;
        mmHeight = 285.0f;
        break;
    
    case ShogiObj::KNIGHT:
        mmBottomWidth  = 235.0f;
        mmHeight = 275.0f;
        break;

    case ShogiObj::LANCE:
        mmBottomWidth  = 225.0f;
        mmHeight = 275.0f;
        break;

    case ShogiObj::PAWN:
        mmBottomWidth  = 225.0f;
        mmHeight = 260.0f;
        break;

    default:
        return;
    }

    // 10.0fで約400mm
    float mmPerFloat = 600.0f / 10.0f;

    // マスの1辺を1.0fとして、駒をfloatの長さに直す
    float bottomWidth  = mmBottomWidth  / mmPerFloat; // 底面横の長さ
    float height = mmHeight / mmPerFloat; // 縦の長さ

    float cornerWidthRate  = 0.7;  // 底面横に対する角横長さの比率
    float cornerHeightRate = 0.85; // 駒の高さに対する角縦長さの比率

    float cornerWidth  = bottomWidth  * cornerWidthRate;    // 角部分の横の長さ
    float cornerHeight = height * cornerHeightRate;   // 角部分縦の底面からの高さ
    float thickness    = height / 8.0f;  // 駒の厚み

    // UV座標使用のため、駒の高さを1.0fとした時のそれぞれの頂点のUV座標を取得する
    float quarterCornerWidth = (cornerWidth / height) / 2 / 2;
    float quarterBottomWidth = (bottomWidth / height) / 2 / 2;

    float frontCenterU = 0.25f;

    // 表面
    float frontTopU = frontCenterU;
    float topV = 0.0f;

   
    float frontLeftCornerU  = frontCenterU - quarterCornerWidth;
    float frontRightCornerU = frontCenterU + quarterCornerWidth;
    float cornerV = (1.0f - cornerHeightRate) / 2;

    
    float frontLeftBottomU  = frontCenterU - quarterBottomWidth;
    float frontRightBottomU = frontCenterU + quarterBottomWidth;
    float bottomV = 0.5f;

    // 裏面
    float backTopU = frontTopU + 0.5f;
    float backLeftCornerU  = frontLeftCornerU + 0.5f;
    float backRightCornerU = frontRightCornerU + 0.5f;
    float backLeftBottomU  = frontLeftBottomU + 0.5f;
    float backRightBottomU = frontRightBottomU + 0.5f;
    

    // (0,0)を基準とした頂点座標にするため,それぞれの位置をずらす
    bottomWidth  /= 2;
    height       /= 2;
    cornerWidth  /= 2;
    cornerHeight -= height;


    // 側面の法線（右と上を正）を
    DirectX::XMFLOAT2 normalizedVec;

    // 頂点上　→　頂点角右のベクトルを正規化する
    DirectX::XMFLOAT2 topToRightCornerVec;
    topToRightCornerVec.x = cornerWidth;
    topToRightCornerVec.y = cornerHeight - height;
    normalizedVec = VecCalc::GetNormFloat(topToRightCornerVec);

    // 正規化したベクトルのxyを反対に格納し、どちらかの符号を逆にしたものは法線
    float cornerNormalX = -normalizedVec.y;
    float cornerNormalY =  normalizedVec.x;


    // 頂点角右　→　頂点底面右のベクトルを正規化する
    DirectX::XMFLOAT2 rightCornerToRightBottomVec;
    rightCornerToRightBottomVec.x =  bottomWidth - cornerWidth;
    rightCornerToRightBottomVec.y = -height      - cornerHeight;
    normalizedVec = VecCalc::GetNormFloat(rightCornerToRightBottomVec);

    // 正規化したベクトルのxyを反対に格納し、どちらかの符号を逆にしたものは法線
    float normalX = -normalizedVec.y;
    float normalY =  normalizedVec.x;

    

    

    std::vector<ShogiObj::Vert> vertices;

    vertices = // 頂点集合
    {
        // 前面
        {{ cornerWidth, cornerHeight, -thickness}, {0.0f,  0.0f, -1.0f}, {frontRightCornerU, cornerV}}, // 右上
        {{ bottomWidth,      -height, -thickness}, {0.0f,  0.0f, -1.0f}, {frontRightBottomU, bottomV}}, // 右下
        {{-bottomWidth,      -height, -thickness}, {0.0f,  0.0f, -1.0f}, {frontLeftBottomU,  bottomV}}, // 左下 
        {{-cornerWidth, cornerHeight, -thickness}, {0.0f,  0.0f, -1.0f}, {frontLeftCornerU,  cornerV}}, // 左上
        {{        0.0f,       height, -thickness}, {0.0f,  0.0f, -1.0f}, {frontTopU,         topV   }}, // 上    

        // 裏面
        {{-cornerWidth, cornerHeight,       0.0f}, {0.0f,  0.0f,  1.0f}, {backRightCornerU,  cornerV}}, // 右上
        {{-bottomWidth,      -height,       0.0f}, {0.0f,  0.0f,  1.0f}, {backRightBottomU,  bottomV}}, // 右下
        {{ bottomWidth,      -height,       0.0f}, {0.0f,  0.0f,  1.0f}, {backLeftBottomU,   bottomV}}, // 左下
        {{ cornerWidth, cornerHeight,       0.0f}, {0.0f,  0.0f,  1.0f}, {backLeftCornerU,   cornerV}}, // 左上
        {{        0.0f,       height,       0.0f}, {0.0f,  0.0f,  1.0f}, {backTopU,          topV   }}, // 上

        // 底面
        {{ bottomWidth,      -height, -thickness}, {0.0f, -1.0f,  0.0f}, {0, 0}}, // 右上
        {{ bottomWidth,      -height,       0.0f}, {0.0f, -1.0f,  0.0f}, {0, 0}}, // 右下
        {{-bottomWidth,      -height,       0.0f}, {0.0f, -1.0f,  0.0f}, {0, 0}}, // 左下
        {{-bottomWidth,      -height, -thickness}, {0.0f, -1.0f,  0.0f}, {0, 0}}, // 左上

        // 側面右
        {{ cornerWidth, cornerHeight, -thickness}, { normalX,  normalY,  1.0f}, {0, 0}}, // 右上
        {{ cornerWidth, cornerHeight,       0.0f}, { normalX,  normalY,  1.0f}, {0, 0}}, // 右下
        {{ bottomWidth,      -height,       0.0f}, { normalX,  normalY,  1.0f}, {0, 0}}, // 左下
        {{ bottomWidth,      -height, -thickness}, { normalX,  normalY,  1.0f}, {0, 0}}, // 左上

        // 側面左
        {{-bottomWidth,      -height, -thickness}, {-normalX,  normalY,  1.0f}, {0, 0}}, // 右上
        {{-bottomWidth,      -height,       0.0f}, {-normalX,  normalY,  1.0f}, {0, 0}}, // 右下
        {{-cornerWidth, cornerHeight,       0.0f}, {-normalX,  normalY,  1.0f}, {0, 0}}, // 左下
        {{-cornerWidth, cornerHeight, -thickness}, {-normalX,  normalY,  1.0f}, {0, 0}}, // 左上

        // 側面右上
        {{           0,       height, -thickness}, { cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 右上
        {{           0,       height,       0.0f}, { cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 右下
        {{ cornerWidth, cornerHeight,       0.0f}, { cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 左下
        {{ cornerWidth, cornerHeight, -thickness}, { cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 左上

        // 側面左上
        {{-cornerWidth, cornerHeight, -thickness}, {-cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 右上
        {{-cornerWidth, cornerHeight,       0.0f}, {-cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 右下
        {{           0,       height,       0.0f}, {-cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 左下
        {{           0,       height, -thickness}, {-cornerNormalX,  cornerNormalY,  1.0f}, {0, 0}}, // 左上  
    };

    for (auto& vertex : vertices)
    {
        vertex.objId = objId;
        vertex.designTexId = texId;
    }

    NaturalBufferedData<GameObj::Vert> vertData;
    vertData.SetDatas(vertices);
    shogiObj->SetVertices(vertData);


    // ワールド行列セット
    WorldMat worldMatObj;
    worldMatObj.SetWorldMat(DirectX::XMMatrixIdentity());
    shogiObj->SetWorldMat(worldMatObj);
}

PieceFactory::~PieceFactory(){}