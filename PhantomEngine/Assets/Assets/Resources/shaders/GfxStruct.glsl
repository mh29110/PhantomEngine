#define UNIFORM_BLOCK_MACRO    \
layout( std140) uniform ConstantsPerFrame	\
{									\
    mat4 viewMatrix;	\
    mat4 projectionMatrix;	\
    vec4 camPos;	\
} uboFrame;	\
layout( std140) uniform Light    \
{							\
    vec4 lightPos;	\
	vec4 lightColor;	\
	vec4 lightDir;	\
	mat4 lightVP;	\
} light;	\
layout( std140) uniform ConstantsPerBatch	\
{						\
    mat4 modelMatrix;   \
} uboBatch;
UNIFORM_BLOCK_MACRO