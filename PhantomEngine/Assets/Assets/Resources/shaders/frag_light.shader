#version 410 core

layout( std140) uniform ConstantsPerFrame
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    vec4 camPos;
} uboFrame;

layout( std140) uniform Light
{
    vec4 lightPos;
	vec4 lightColor;
	vec4 lightDir;
	mat4 lightVP;
} light;

uniform sampler2D diffuseColor;
uniform sampler2D shadowMap;

in vec4 vViewPos;
in vec3 normal;
in vec2 texc;
in vec4 vWorldPos;

layout (location = 0) out vec4 outputColor;

float ShadowCalculation (float cosTheta) {
    vec4 fragPosLightSpace = light.lightVP * vWorldPos;
    //归一化坐标
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //转换到[0,1]范围
    projCoords = (projCoords + 1) * 0.5;
    //采样最近点
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    //当前的深度
    float currentDepth = projCoords.z;
    //比较当前深度和最近采样点深度
    float bias = 0.005*tan(acos(cosTheta)); 
    bias = clamp(bias, 0.0,0.01);
    float shadow = currentDepth-bias > closestDepth? 1.0 : 0.0;

    return shadow;
}


void main()
{
	vec3 diffColor = texture(diffuseColor, texc.xy).rgb;
    vec3 normal = normalize(normal);
    vec3 lightColor = light.lightColor.xyz;

    vec3 ambient = 0.02 * diffColor;

    //vec3 lightDir = normalize((light.lightPos - vWorldPos).xyz);
	vec3 lightDir = normalize(light.lightDir.xyz);
	lightDir = -lightDir; //入射方向的反方向
    float cosTheta = max(dot(lightDir, normal), 0.0);
    vec3 diffLight = cosTheta * lightColor;
    
    float spec = 0.0;
    vec3 viewDir = normalize((uboFrame.camPos - vWorldPos).xyz);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor; 
    // 计算阴影
	float shadow =  ShadowCalculation(cosTheta);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffLight + specular)) * diffColor;    
    
    outputColor = vec4(lighting, 1.0);

} 

