#pragma once 
#include "mat4.h"
#include "vector.h"
#include "SceneGeometryNode.h"
namespace Phantom {

typedef maths::vec4 float4;
typedef maths::vec3 float3;
typedef maths::vec2 float2;
typedef maths::mat4x4 mat4x4f;
	class SceneGeometryNode;
	//每渲染批次常量
	struct ConstantsPerBatch 
	{ 
		maths::mat4x4 modelMatrix;
	};
	const size_t kSizeOfFrameConstantBuffer = 256;
	const size_t kSizeOfBatchConstantBuffer = 256;
	//渲染中每帧内固定常量
	struct ConstantsPerFrame  
	{
		mat4x4f  	viewMatrix;						// 64 bytes
		mat4x4f  	projectionMatrix;				// 64 bytes
		float4   	camPos;							// 16 bytes
	};

	//渲染批次上下文
	struct ContextPerDrawBatch:ConstantsPerBatch {
		uint32_t batchIndex;
		std::shared_ptr<SceneGeometryNode> node;
		virtual ~ContextPerDrawBatch() = default;
	};

	//渲染每帧的上下文
	struct ContextPerFrame : ConstantsPerFrame {
	};

	//每帧的数据集合
	struct Frame {
		ContextPerFrame frameContext;
		std::vector<std::shared_ptr<ContextPerDrawBatch>> batchContexts;
	};
}