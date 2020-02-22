
//#define GL_GLEXT_PROTOTYPES //it ignores all the warnings
#include <GL/glew.h>
#include <GL/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned int CompileShader(unsigned int type,const char* source)
{
		unsigned int id = glCreateShader(type);
		const char* src = source;
		glShaderSource(id,1,&src,NULL);
		glCompileShader(id);

		return id;
}
static unsigned int CreateShader(const char* vertexShader, const char* fragmentShader)
{

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);
	glAttachShader(program,vs);
	glAttachShader(program,fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if(glewInit()!=GLEW_OK)
    	printf("glew!");
    
    float positions[6]={
    	-0.5f, -0.5f,
    	 0.0f,  0.5f,
    	 0.5f, -0.5f

    };


    unsigned int buffer;
    glGenBuffers(1,&buffer); 
    glBindBuffer(GL_ARRAY_BUFFER,buffer); //binds buffer variable to the GPU buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW); //passes vertex vector to GPU buffer

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //tells the GPU what the layout of the buffer is
    


	GLchar* vertexShader=
	"#version 330 core\n"
	"layout(location = 0 ) in vec4 positions;\n"
	"void main()\n"
	"{\n"
	"gl_Position = positions;\n"
	"}\n\0";
		
		
		//printf("why\n");
	GLchar* fragmentShader=
		"#version 330 core\n"
		"layout( location = 0 ) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4( 0.0, 1.0, 0.0, 1.0 );\n"
		"}\n\0";

	
    unsigned int shader = CreateShader(vertexShader,fragmentShader);

    glUseProgram(shader);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, //shape being drawn
        	0, //starting vertex
        	3);  //number of vertices
        //if glBindBuffer fails this will also fail ^^^

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}