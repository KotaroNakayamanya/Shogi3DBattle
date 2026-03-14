#include"Pipeline.h"

// パイプラインステートを返す
ID3D12PipelineState* Pipeline::GetPipelineState(){return _pipelineState.Get();}

Pipeline::Pipeline(){}
Pipeline::~Pipeline(){}