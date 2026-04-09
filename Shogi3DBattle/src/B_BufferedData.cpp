#include"B_BufferedData.h"

void         B_BufferedData::SetStartDataIdx(unsigned int idx){_startDataIdx = idx;}  // データスタート位置セット
unsigned int B_BufferedData::GetStartDataIdx()                {return _startDataIdx;} // データスタート位置を返す