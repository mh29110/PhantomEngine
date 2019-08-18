#pragma clang diagnostic ignored "-Wmissing-prototypes"

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;


struct PerFrameConstants
{
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
    float4 camPos;
//    int numLights;
};

struct Light
{
    float lightIntensity;
    int lightType;
};

struct LightInfo
{
    Light lights[1];
};


struct pbr_frag_main_out
{
    float4 _entryPointOutput [[color(0)]];
};

struct pbr_frag_main_in
{
    float4 _entryPointOutput_normal [[user(locn0)]];
    float4 _entryPointOutput_normal_world [[user(locn1)]];
    float4 _entryPointOutput_v [[user(locn2)]];
    float4 _entryPointOutput_v_world [[user(locn3)]];
    float2 _entryPointOutput_uv [[user(locn6)]];
};


fragment pbr_frag_main_out pbr_frag_main(pbr_frag_main_in in [[stage_in]],
                                         constant PerFrameConstants& frameConst [[buffer(10)]],
                                         constant LightInfo& lights [[buffer(12)]],
                                          texture2d<float> diffuseMap [[texture(0)]],
                                          sampler samp0 [[sampler(0)]],
                                    float4 gl_FragCoord [[position]])

{
    pbr_frag_main_out out = {};
    out._entryPointOutput = diffuseMap.sample( samp0,in._entryPointOutput_uv);
    return out;
}

