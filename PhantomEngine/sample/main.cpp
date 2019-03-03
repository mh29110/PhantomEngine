#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileUtils.h"

using namespace phantom::maths;
using namespace phantom;
using namespace graphics;

GLuint m_ShaderID;
double mouse_x = 0.0;
double mouse_y = 0.0;

GLint getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(m_ShaderID, name);
}

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
 

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

GLuint setupShaders() {
 
    char *vs = NULL,*fs = NULL,*fs2 = NULL;
 
    GLuint p,v,f;
 
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
 
    vs = read_file("shaders/vert.shader");
    fs = read_file("shaders/frag.shader");
 
    const char * vv = vs;
    const char * ff = fs;
 
    glShaderSource(v, 1, &vv,NULL);
    glShaderSource(f, 1, &ff,NULL);
 	
    free(vs);free(fs);
 
    glCompileShader(v);
    glCompileShader(f);


 	printShaderInfoLog(v);
 	printShaderInfoLog(f);
 
 
    p = glCreateProgram();
    glAttachShader(p,v);
    glAttachShader(p,f);
    glLinkProgram(p);
 	printProgramInfoLog(p);

 	glDeleteShader(v);
    glDeleteShader(f);
    return(p);
}

int main()
{
	Window window("phantom!", 960, 540);

    m_ShaderID = setupShaders();
	glUseProgram(m_ShaderID);

	GLfloat vertices[] = {
	    -0.5f, -0.5f, 0.0f,
	     0.5f, -0.5f, 0.0f,
	     0.0f,  0.5f, 0.0f
	};
	GLuint vaoId,vboId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1,&vboId);
	glBindBuffer(GL_ARRAY_BUFFER,vboId);

	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


// 	mat4x4 oro ;
 	mat4x4 ortho = mat4x4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
 	// mat4x4 ortho = mat4x4::identity();
// 	std::cout << ortho;

// 	glUniformMatrix4fv(getUniformLocation("pr_matrix"),1,GL_FALSE, ortho.elements);

// 	glUniform2f(getUniformLocation("light_pos"), 4.0f, 1.5f);
// 	glUniform4f(getUniformLocation("colour"), 1.0f, 0.7f, 0.8f, 1.0f);
   

//当前程序运行根目录
    const int MAXPATH=250;
    char buffer[MAXPATH];
    getcwd(buffer, MAXPATH);
    printf("The current directory is: %s", buffer);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!window.closed())
	{
        window.clear();

        // Draw our first triangle
        glUseProgram(m_ShaderID);
	    glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the screen buffers
		window.update();
	}

    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
	window.terminate();

	return 0;
} 