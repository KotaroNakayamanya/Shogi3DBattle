#include"Piece.h"

// 頂点集合作成
void Piece::SetVertices(CreateVerticesArg arg)
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

// 頂点集合ポインタを返す
std::vector<VertexStruct::Vertex> Piece::GetVerticesPtr()
{
    return _vertices;
}

// 頂点１つ分のバイトサイズを返す
unsigned int Piece::GetVertexByteSize()
{
    return sizeof(_vertices[0]);
}

// 頂点集合全体のバイトサイズを返す
unsigned int Piece::GetVerticesByteSize()
{
    return GetVertexByteSize() * _vertices.size();
}




// 頂点インデックスポインタを返す
std::vector<unsigned short> Piece::GetIndicesPtr()
{
    return _indices;
}

unsigned int Piece::GetIndicesNum()
{
    return _indices.size();
}

// 頂点インデックス１つ分のバイトサイズを返す
unsigned int Piece::GetIndexByteSize()
{
    return sizeof(_indices[0]);
}

// 頂点インデックス全体のバイトサイズを返す
unsigned int Piece::GetIndicesByteSize()
{
    return GetIndexByteSize() * _indices.size();
}




Piece::~Piece(){}