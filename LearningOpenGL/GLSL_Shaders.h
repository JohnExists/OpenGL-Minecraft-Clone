#ifndef GLSL_SHADER
#define GLSL_SHADER


#define DEF_VERTEX_SHADER "#version 330 core					 \n"\
"layout(location = 0) in vec3 aPos;								 \n"\
"layout(location = 1) in vec3 aNormal;							 \n"\
"layout(location = 2) in vec2 aTexCoord;						 \n"\
"																 \n"\
"uniform mat4 model;											 \n"\
"uniform mat4 view;												 \n"\
"uniform mat4 projection;										 \n"\
"																 \n"\
"out vec2 texCoord;												 \n"\
"																 \n"\
"void main()													 \n"\
"{																 \n"\
"	gl_Position = projection * view * model * vec4(aPos, 1.0);	 \n"\
"	texCoord = aTexCoord;										 \n"\
"																 \n"\
"}"

#define DEF_FRAG_SHADER	"#version 330 core						\n"\
"																\n"\
"out vec4 FragColor;											\n"\
"																\n"\
"in vec2 texCoord;												\n"\
"																\n"\
"uniform sampler2D texture1;									\n"\
"																\n"\
"void main()													\n"\
"{																\n"\
"	FragColor = texture(texture1, texCoord);					\n"\
"																\n"\
"}"

#define TEMP_VERTEX_SHADER "#version 330 core					 \n"\
"layout(location = 0) in vec3 aPos;								 \n"\
"layout(location = 1) in vec3 aNormal;							 \n"\
"layout(location = 2) in vec2 aTexCoord;						 \n"\
"																 \n"\
"uniform mat4 model;											 \n"\
"uniform mat4 view;												 \n"\
"uniform mat4 projection;										 \n"\
"																 \n"\
"out vec2 texCoord;												 \n"\
"																 \n"\
"void main()													 \n"\
"{																 \n"\
"	gl_Position = model * vec4(aPos, 1.0);						 \n"\
"	texCoord = aTexCoord;										 \n"\
"																 \n"\
"}"

#define TEMP_FRAG_SHADER	"#version 330 core					\n"\
"																\n"\
"out vec4 FragColor;											\n"\
"																\n"\
"in vec2 texCoord;												\n"\
"																\n"\
"uniform sampler2D texture1;									\n"\
"																\n"\
"void main()													\n"\
"{																\n"\
"	FragColor = texture(texture1, texCoord);					\n"\
"																\n"\
"}"

#endif // !GLSL_SHADER
