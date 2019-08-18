#include <metal_stdlib>

#include "GfxStructMetal.h"

using namespace metal;


typedef struct
{
    float4 position;
    float4 texCoords;
} VertexIn;


typedef struct
{
    float4 position [[position]];
    float4 texCoords;
}VertexOut;



vertex VertexOut myVertexShader(const device VertexIn* vertexArray [[buffer(0)]],
                                unsigned int vid  [[vertex_id]]){

    VertexOut verOut;
    verOut.position = vertexArray[vid].position;
    verOut.texCoords = vertexArray[vid].position;
    return verOut;

}


fragment float4 myFragmentShader(
                                VertexOut vertexIn [[stage_in]],
                                 texturecube<float>  cubeTexture [[texture(10)]]
                             )
{

    constexpr sampler linear_sampler(min_filter::linear, mag_filter::linear);
    float4 color = cubeTexture.sample(linear_sampler,float3(vertexIn.texCoords.x,vertexIn.texCoords.y,vertexIn.texCoords.z));
    return color;

}
