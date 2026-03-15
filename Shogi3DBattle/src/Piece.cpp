#include"Piece.h"

// 駒の頂点集合作成
void Piece::CreatePieceVertices(CreatePieceVerticesArg arg)
{
    float bottomWidth  = arg.bottomWidth;
    float cornerWidth  = arg.cornerWidth;
    float height       = arg.height;
    float cornerHeight = arg.cornerHeight;
    float thickness    = arg.thickness;

    _vertices =
    {   // 上面図と考えて指定
        // 前面
        {{-bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左下
        {{ bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右下
        {{-cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上
        {{ cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右上
        {{ 0.0f,         height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 上    

        // 裏面
        {{-bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
        {{ bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 右下
        {{-cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左上
        {{ cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 右上
        {{ 0.0f,         height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 上
    };
}




// x軸方向に動くようにワールド行列を変換する
void Piece::MoveX(float x)
{
    _worldMat *= DirectX::XMMatrixTranslation(x, 0, 0);
}

// y軸方向に動くようにワールド行列を変換する
void Piece::MoveY(float y)
{
    _worldMat *= DirectX::XMMatrixTranslation(0, y, 0);
}




// ワールド行列を返す
DirectX::XMMATRIX Piece::GetWorldMat()
{
    return _worldMat;
}





Piece::Piece()
{
    enum VertexName // 頂点に名前を付ける
    {
        // 前面
        frontLeftBottom,  // 左下
        frontRightBottom, // 右下
        frontLeftTop,     // 左上
        frontRightTop,    // 右上
        frontTop,         // 上

        // 背面
        backLeftBottom,  // 左下
        backRightBottom, // 右下
        backLeftTop,     // 左上
        backRightTop,    // 右上
        backTop          // 上
    };

    _indices = // 頂点インデックス
    {
        // 前面
        frontRightBottom, frontLeftBottom, frontLeftTop,  // 右下　左下　左上
        frontRightBottom, frontLeftTop,    frontRightTop, // 右下　左上　右上
        frontRightTop,    frontLeftTop,    frontTop,      // 右上　左上　上

        //// 裏面
        backLeftBottom,  backRightBottom, backLeftTop, // 左下　右下　左上
        backRightBottom, backRightTop,    backLeftTop, // 右下　右上　左上
        backLeftTop,     backRightTop,    backTop,     // 左上　右上　上

        // 側面上左
        frontTop, frontLeftTop, backLeftTop, // 前面上　前面左上　背面左上
        backTop,  frontTop,     backLeftTop, // 背面上　前面上　　背面左上

        // 側面上右
        backTop,  backRightTop, frontRightTop, // 背面上　背面右上　前面右上
        frontTop, backTop,      frontRightTop, // 前面上　背面上　　前面右上　


        // 側面右
        frontRightBottom, frontRightTop, backRightBottom, // 背面右下　前面右上　背面右下
        frontRightTop,    backRightTop,  backRightBottom, // 背面右上　背面右上　背面右下

        // 側面左
        backLeftBottom, backLeftTop,  frontLeftBottom, // 背面左下　背面左上　前面左下
        backLeftTop,    frontLeftTop, frontLeftBottom, // 背面左上　前面左上　前面左下

        // 底面
        frontLeftBottom, frontRightBottom, backRightBottom, // 前面左下　前面右下　背面右下
        frontLeftBottom, backRightBottom, backLeftBottom    // 前面左下　背面右下　背面左下
    };

    _worldMat = DirectX::XMMatrixIdentity(); // 変換行列
}

Piece::~Piece(){}