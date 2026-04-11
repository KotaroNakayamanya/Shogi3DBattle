#include"TextFormat.h"

void TextFormat::SetTextFormat(ComPtr<IDWriteTextFormat> textFormat){_textFormat = textFormat;} // テキストフォーマットセット
IDWriteTextFormat* TextFormat::GetTextFormat()                      {return _textFormat.Get();} // テキストフォーマットを返す