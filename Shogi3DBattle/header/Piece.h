#pragma once

#include<vector>
#include"VertexStruct.h"

class Piece
{
private:
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

    std::vector<VertexStruct::Vertex> _vertices; // 頂点集合（派生クラスでVertexNameの順番に頂点データを代入）
    std::vector<unsigned short>       _indices = // 頂点インデックス
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

protected:
    typedef struct CreateVerticesArg // 頂点集合作成用引数
    {
        float bottomWidth;  // 底面の横の長さ
        float cornerWidth;  // 角部分の横の長さ
        float height;       // 高さ
        float cornerHeight; // 角部分の高さ
        float thickness;   // 駒の厚み

    }CreateVerticesArg;

    void SetVertices(CreateVerticesArg arg); // 頂点集合作成

public:
    std::vector<VertexStruct::Vertex> GetVerticesPtr();
    std::vector<unsigned short> GetIndicesPtr();

    unsigned int GetVertexByteSize();
    unsigned int GetVerticesByteSize();

    unsigned int GetIndicesNum();
    unsigned int GetIndexByteSize();
    unsigned int GetIndicesByteSize();

    Piece() = default;
    ~Piece();
};