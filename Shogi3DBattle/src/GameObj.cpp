//#include"GameObj.h"
//
//void GameObj::InitGameObj()
//{
//    CreateBoard();
//    CreatePawn();
//}
//
//void GameObj::CreateBoard()
//{
//    _board->_vertices =
//    {   // 上面図
//
//        // 前面
//        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左下
//        {{0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右下
//        {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上
//        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右上
//
//        // 背面
//        {{0.0f, 0.0f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
//        {{0.5f, 0.0f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 右下
//        {{0.0f, 0.5f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左上
//        {{0.5f, 0.5f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}  // 右上
//    };
//
//    enum BoardVertName // 将棋盤の頂点に名前を付ける
//    {
//        // 前面
//        frontLeftBottom,  // 左下
//        frontRightBottom, // 右下
//        frontLeftTop,     // 左上
//        frontRightTop,    // 右上
//
//        // 背面
//        backLeftBottom,  // 左下
//        backRightBottom, // 右下
//        backLeftTop,     // 左上
//        backRightTop,    // 右上
//    };
//
//    _board->_indices =
//    {
//        // 前面
//        frontRightBottom, frontLeftBottom,  frontLeftTop,
//        frontLeftTop,     frontRightTop,    frontRightBottom,     
//        
//        // 上側面
//        frontRightTop, frontLeftTop, backLeftTop, 
//        backLeftTop,   backRightTop, frontRightTop,
//
//        // 右側面
//        frontRightBottom, frontRightTop,   backRightTop,
//        backRightTop,     backRightBottom, frontRightBottom,
//
//        // 下側面
//        frontLeftBottom, frontRightBottom, backRightBottom,
//        backRightBottom, backLeftBottom,   frontLeftBottom,
//
//        // 左側面
//        frontLeftTop, frontLeftBottom, backLeftBottom,
//        backLeftBottom, backLeftTop, frontLeftTop,
//
//        // 背面
//        backRightBottom, backLeftBottom, backLeftTop,
//        backLeftTop,     backRightTop,   backRightBottom
//    };
//}
//
//void GameObj::CreatePawn()
//{
//    float bottomWidth  = 0.9f;          // 底面の横の長さ
//    float cornerWidth  = 0.7f;          // 角部分の横の長さ
//    float height       = 0.9f;          // 高さ
//    float cornerHeight = height * 0.7f; // 角部分の高さ（高さを基準に調整）
//    float thickness    = 0.4f;          // 駒の厚み
//
//    _pawn->_vertices = // 頂点集合
//    {   // 上面図と考えて指定
//        // 前面
//        {{-bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左下
//        {{ bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右下
//        {{-cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上
//        {{ cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右上
//        {{ 0.0f,         height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 上    
//
//        // 裏面
//        {{-bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
//        {{ bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 右下
//        {{-cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左上
//        {{ cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 右上
//        {{ 0.0f,         height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 上
//    };
//
//    enum PieceVertName // 駒の頂点に名前を付ける
//    {
//        // 前面
//        frontLeftBottom,  // 左下
//        frontRightBottom, // 右下
//        frontLeftTop,     // 左上
//        frontRightTop,    // 右上
//        frontTop,         // 上
//
//        // 背面
//        backLeftBottom,  // 左下
//        backRightBottom, // 右下
//        backLeftTop,     // 左上
//        backRightTop,    // 右上
//        backTop          // 上
//    };
//
//    _pawn->_indices = // インデックス集合
//    {
//        // 前面
//        frontRightBottom, frontLeftBottom, frontLeftTop,     // 右下　左下　左上
//        frontLeftTop,     frontRightTop,   frontRightBottom, // 左上　右上 右下
//        frontTop,         frontRightTop,   frontLeftTop,     // 右上　左上　上
//
//        // 裏面
//        backLeftBottom,  backRightBottom, backLeftTop, // 左下　右下　左上
//        backRightBottom, backRightTop,    backLeftTop, // 右下　右上　左上
//        backLeftTop,     backRightTop,    backTop,     // 左上　右上　上
//
//        // 側面上左
//        frontTop, frontLeftTop, backLeftTop, // 前面上　前面左上　背面左上
//        backTop,  frontTop,     backLeftTop, // 背面上　前面上　　背面左上
//
//        // 側面上右
//        backTop,  backRightTop, frontRightTop, // 背面上　背面右上　前面右上
//        frontTop, backTop,      frontRightTop, // 前面上　背面上　　前面右上　
//
//
//        // 側面右
//        frontRightBottom, frontRightTop, backRightBottom, // 背面右下　前面右上　背面右下
//        frontRightTop,    backRightTop,  backRightBottom, // 背面右上　背面右上　背面右下
//
//        // 側面左
//        backLeftBottom, backLeftTop,  frontLeftBottom, // 背面左下　背面左上　前面左下
//        backLeftTop,    frontLeftTop, frontLeftBottom, // 背面左上　前面左上　前面左下
//
//        // 底面
//        frontLeftBottom, frontRightBottom, backRightBottom, // 前面左下　前面右下　背面右下
//        frontLeftBottom, backRightBottom, backLeftBottom    // 前面左下　背面右下　背面左下
//    };
//}
//
//
//Board* GameObj::GetBoard(){return _board.get();} // 将棋盤を返す
//Pawn*  GameObj::GetPawn() {return _pawn.get();}  // 歩を返す
//
//GameObj::GameObj()
//{
//    _board = std::make_unique<Board>();
//    _pawn  = std::make_unique<Pawn>();
//}
//
//GameObj::~GameObj(){}