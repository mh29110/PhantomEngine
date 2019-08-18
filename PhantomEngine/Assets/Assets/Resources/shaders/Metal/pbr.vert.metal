#pragma clang diagnostic ignored "-Wmissing-prototypes"

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct VertexIn
{
    float3 a_inputPosition [[attribute(0)]];
    float3 a_inputNormal [[attribute(1)]];
    float2 a_inputUV [[attribute(2)]];
};

struct a2v
{
    float3 inputPosition;
    float3 inputNormal;
    float2 inputUV;
};

struct pbr_vert_output
{
    float4 pos;
    float4 normal;
    float4 normal_world;
    float4 v;
    float4 v_world;
    float3 v_tangent;
    float3 camPos_tangent;
    float2 uv;
    float3x3 TBN;
};

struct PerBatchConstants
{
    float4x4 modelMatrix;
};

struct PerFrameConstants
{
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
    float4 camPos;
//    int numLights;
};


struct VertexOutput
{
    float4 _entryPointOutput_normal [[user(locn0)]];
    float4 _entryPointOutput_normal_world [[user(locn1)]];
    float4 _entryPointOutput_v [[user(locn2)]];
    float4 _entryPointOutput_v_world [[user(locn3)]];
    float2 _entryPointOutput_uv [[user(locn6)]];
    float4 gl_Position [[position]];
};

pbr_vert_output _pbr_vert_main(thread const a2v& a,
                                constant PerBatchConstants& batchConst,
                               constant PerFrameConstants& frameConst)
{
    pbr_vert_output o;
    o.v_world = batchConst.modelMatrix * float4(a.inputPosition, 1.0);
    o.v = frameConst.viewMatrix * o.v_world;
    o.pos = frameConst.projectionMatrix * o.v;
    o.normal_world = normalize(batchConst.modelMatrix * float4(a.inputNormal, 0.0));
    o.normal = normalize(frameConst.viewMatrix * o.normal_world);
    o.uv.x = a.inputUV.x;
    o.uv.y = 1.0 - a.inputUV.y;
    return o;
}

vertex VertexOutput pbr_vert_main(VertexIn in [[stage_in]],
                                  constant PerFrameConstants& frameConst [[buffer(10)]],
                                  constant PerBatchConstants& batchConst [[buffer(11)]])
{
    VertexOutput out = {};
    a2v a;
    a.inputPosition = in.a_inputPosition;
    a.inputNormal = in.a_inputNormal;
    a.inputUV = in.a_inputUV;
    
    a2v param = a;
    pbr_vert_output flattenTemp = _pbr_vert_main(param, batchConst, frameConst);
    
    out.gl_Position = flattenTemp.pos;
    out._entryPointOutput_normal = flattenTemp.normal;
    out._entryPointOutput_normal_world = flattenTemp.normal_world;
    out._entryPointOutput_v = flattenTemp.v;
    out._entryPointOutput_v_world = flattenTemp.v_world;
    out._entryPointOutput_uv = flattenTemp.uv;
    return out;
}

