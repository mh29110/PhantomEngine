//
//  GfxStructMetal.h
//  PhantomEngine
//
//  Created by phantom on 2019/8/17.
//

#ifndef GfxStructMetal_h
#define GfxStructMetal_h

#include <metal_stdlib>

using namespace metal;


struct ConstantsPerFrame
{
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
    float4 camPos;
};
struct Light
{
    float4 lightPos;
    float4 lightColor;
    float4 lightDir;
    float4x4 lightVP;
};

struct ConstantsPerBatch
{
    float4x4 modelMatrix;
};


#endif /* GfxStructMetal_h */
