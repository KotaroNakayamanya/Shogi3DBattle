#include"I_Piece.h"
#include"VecCalc.h"
#include"GameObjIdManager.h"
#include"BasicTexType.h"

// 移動
void I_Piece::Move(DirectX::XMFLOAT3 vec)
{
    auto worldMat = GetWorldMat();
    auto currentWorldMat = worldMat->GetMat();
    auto newWorldMat = currentWorldMat * DirectX::XMMatrixTranslation(vec.x, vec.y, vec.z);
    worldMat->SetMat(newWorldMat);
}

void I_Piece::SetPlayerSide(PlayerSide playerSide) // 駒所有プレイヤーセット
{
    _playerSide = playerSide;
    GetVertices()->SetBasicTexId(static_cast<unsigned char>(playerSide));
} 
PlayerSide I_Piece::GetPlayerSide(){return _playerSide;} // 駒所有プレイヤーを返す

void I_Piece::SetIsPromotion(bool b){_isPromotion = b;   } // 成っているかどうかセット
bool I_Piece::GetIsPromotion()      {return _isPromotion;} // 成っているかどうか返す

I_Piece::I_Piece(float mmBottomWidth, float mmHeight, GameObjType pieceType, PlayerSide playerSide)
    : I_GameObj(pieceType), _playerSide(playerSide), _isPromotion(false)
{
    // 指定されたサイズの駒の頂点集合作成

    // 10.0fで400mm
    float mmPerFloat = 400.0f / 10.0f;

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

    // 頂点上　→　頂点角右のベクトルを正規化する
    DirectX::XMFLOAT2 topToRightCornerVec;
    topToRightCornerVec.x = cornerWidth;
    topToRightCornerVec.y = cornerHeight - height;
    DirectX::XMFLOAT2 normalizedVec = VecCalc::GetNormFloat(topToRightCornerVec);

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

    std::vector<Vert> vertices;

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

    SetVertices(std::make_unique<I_Vertices>());
    // 頂点集合
    auto verticesPtr = GetVertices();
    verticesPtr->SetDatas(vertices);
    verticesPtr->SetGameObjId(GameObjIdManager::GetId());
    verticesPtr->SetBasicTexId(static_cast<unsigned char>(playerSide));

    // ワールド行列
    auto worldMatPtr = GetWorldMat();
    auto worldMat = DirectX::XMMatrixIdentity();
    if(playerSide == PlayerSide::PLAYER_2) worldMat *= DirectX::XMMatrixRotationZ(DirectX::XM_PI);
    worldMatPtr->SetMat(worldMat);

    verticesPtr->SetMulDesignTexId(static_cast<unsigned char>(pieceType));
}