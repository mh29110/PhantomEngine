#version 410 core

layout (location = 0) out vec4 outputColor;


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
in vec4 FragPosLightSpace;


float ShadowCalculation (vec4 fragPosLightSpace) {
    //归一化坐标
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //转换到[0,1]范围
    projCoords = (projCoords + 1) * 0.5;
    //采样最近点
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    //当前的深度
    float currentDepth = projCoords.z;
    //比较当前深度和最近采样点深度
    float shadow = currentDepth > closestDepth? 1.0 : 0.0;

    return shadow;
}


void main()
{
	vec3 color = texture(diffuseColor, texc.xy).rgb;
    vec3 normal = normalize(normal);
    vec3 lightColor = light.lightColor.xyz;

    vec3 ambient = 0.02 * color;

    //vec3 lightDir = normalize((light.lightPos - vWorldPos).xyz);
	vec3 lightDir = normalize(light.lightDir.xyz);
	lightDir = -lightDir; //入射方向的反方向
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    
    float spec = 0.0;
   /* vec3 viewDir = normalize(viewPos - vWorldPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);*/
    vec3 specular = spec * lightColor; 
    // 计算阴影
	float shadow =  ShadowCalculation(FragPosLightSpace);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    outputColor = vec4(lighting, 1.0);



	// discard diffuse color
	/*float ambientStrength = 0.1f;
    vec4 ambient = ambientStrength * light.lightColor;

	vec4 diff = texture(diffuseColor, texc.xy);

	vec3 norm = normalize(normal);
	vec3 dir = normalize(light.lightDir.xyz);
	float diffFactor = max(dot(norm, dir), 0.0);
	vec4 diffuse = diffFactor * light.lightColor;

	float depth = texture( shadowMap, vWorldPos.xy ).z;

	outputColor = diff * (diffuse + ambient);*/
} 

