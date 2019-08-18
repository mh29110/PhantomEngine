#pragma once 
#include "maths/mat4.h"
#include "maths/vector.h"
#include "scene/SceneGeometryNode.h"
namespace Phantom {

typedef maths::vec4 float4;
typedef maths::vec3 float3;
typedef maths::vec2 float2;
typedef maths::mat4x4 mat4x4f;

	const size_t kSizeOfFrameConstantBuffer = 256;
	const size_t kSizeOfBatchConstantBuffer = 256;
	const size_t kSizeOfLightBuffer = 256;

	struct Light
	{
		float4    lightPos;   
		float4    lightColor;  
		float4    lightDir;   
		mat4x4f	  lightVP;
	};
    
  

#pragma region constants per dc
    
    struct material_textures
    {
        int32_t diffuseMap = -1;
        int32_t normalMap = -1;
        int32_t metallicMap = -1;
        int32_t roughnessMap = -1;
        int32_t aoMap = -1;
        int32_t heightMap = -1;
    };
    
	//每渲染批次常量
	struct ConstantsPerBatch
	{
		maths::mat4x4 modelMatrix;
	};

	struct ContextPerDrawBatch :ConstantsPerBatch {
		uint32_t batchIndex;
		std::shared_ptr<SceneGeometryNode> node;
        material_textures matTextures;
		virtual ~ContextPerDrawBatch() = default;
	};
  

#pragma endregion


#pragma region constants per frame

	//每帧所需纹理id
	struct texturesForFrame
	{
		int32_t skybox = -1;
        int32_t shadowMap = -1;//todo
	};
	
	struct ConstantsPerFrame
	{
		mat4x4f  	viewMatrix;						// 64 bytes
		mat4x4f  	projectionMatrix;				// 64 bytes
		float4   	camPos;							// 16 bytes
	};
	
	struct ContextPerFrame : ConstantsPerFrame, texturesForFrame {
	};
    
#pragma endregion
    
    struct global_textures
    {
        int32_t brdfLUT;
    };

	//每帧的以上全数据集合
    struct Frame {
		ContextPerFrame frameContext;
		std::vector<std::shared_ptr<ContextPerDrawBatch>> batchContexts;
		Light light;
	};

}
