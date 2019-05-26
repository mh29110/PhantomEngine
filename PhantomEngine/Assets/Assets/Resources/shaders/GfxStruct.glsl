#define UNIFORM_BLOCK    \
	struct Light         \
	{                     \
		float    lightPos;   \
		float    lightColor;  \
		float    lightDir;   \
		mat4	  lightVP;			\
	};								\
	struct ConstantsPerBatch		\
	{								\
		mat4 modelMatrix;				\
	};									\
	struct texturesForFrame				\
	{									\
		int skybox = -1;			\
        int shadowMap = -1;//todo		\
	};										\
	struct ConstantsPerFrame			\
	{									\
		mat4x4  	viewMatrix;						// 64 bytes		\
		mat4x4  	projectionMatrix;				// 64 bytes			\
		float   	camPos;							// 16 bytes			\
	};									\
	struct ContextPerFrame : ConstantsPerFrame, texturesForFrame {		\

	};
