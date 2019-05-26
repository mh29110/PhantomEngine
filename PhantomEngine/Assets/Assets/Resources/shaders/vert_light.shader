#version 410 core

layout(location = 0) in vec4 inputPosition;
layout(location = 1) in vec3 inputNormal;
layout(location = 2) in vec2 inputUV;


UNIFORM_BLOCK_MACRO

out vec4 vViewPos;//在视图空间坐标
out vec3 normal;  //从模型空间转到世界坐标系
out vec2 texc;
out vec4 vWorldPos;//在世界空间

void main()
{
    vWorldPos = uboBatch.modelMatrix * inputPosition;
    vViewPos = uboFrame.viewMatrix * vWorldPos;
    gl_Position = uboFrame.projectionMatrix * vViewPos;


    //--目前我们的法线是在模型空间下，可以打开.OGEX文件确认。
    //法线可以转换到视图空间中，参与视点方向的高光计算，            |||正交矩阵简化： (M \-1) \t  = M 
    //http://www.songho.ca/opengl/gl_normaltransform.html
    //但是我们现在的平行光是写死在世界坐标系空间下，暂时先都转到世界坐标空间下吧。
    normal = (  uboBatch.modelMatrix * vec4(inputNormal, 0.0f) ).xyz;

    texc = vec2 (inputUV.x , 1-inputUV.y);
}