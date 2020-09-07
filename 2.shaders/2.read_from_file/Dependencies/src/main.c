#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "glad/glad.h"

#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define shadermaxsize 1000

typedef struct ShaderProgramSource
{
	char vertexShader[shadermaxsize];
	char fragmentShader[shadermaxsize];
}ShaderProgramSource;

static ShaderProgramSource ParseShader(const char* filepath)
{
	ShaderProgramSource source;
	memset(source.fragmentShader, 0, shadermaxsize);
	memset(source.vertexShader, 0, shadermaxsize);

	FILE* f = fopen(filepath, "r");
	char* line = (char*)malloc(100 * sizeof(char));

	int mode = 0;
	while (fgets(line, 100, f))
	{
		
		if (!strcmp("#shader vertex\n", line))
		{
			mode = 0;
			continue;
		}
		if (!strcmp("#shader fragment\n", line))
		{
			mode = 1;
			continue;

		}

		if (!mode)
		{
			strcat(source.vertexShader, line);
		}
		else
		{
			strcat(source.fragmentShader, line);
		}

		memset(line, 0, 100);
	}

	puts(source.vertexShader);
	printf("//////////////////////////////////////////////////////\n\n\n");
	puts(source.fragmentShader);
	free(line);
	return source;
}
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

    if(gladLoadGL())
    	printf("OpenGL works\n");
    
    float positions[6]={
    	-0.5f, -0.5f,
    	 0.0f,  0.5f,
    	 0.5f, -0.5f

    };


    unsigned int buffer;
    glGenBuffers(1,&buffer); 
    glBindBuffer(GL_ARRAY_BUFFER,buffer); //binds buffer variable to the GPU buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW); //passes vertex vector to GPU buffer

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //tells the GPU what the layout of the buffer is
    glEnableVertexAttribArray(0);



    ShaderProgramSource source=ParseShader("basic.shader");

    unsigned int shader = CreateShader(source.vertexShader,source.fragmentShader);
    glUseProgram(shader);
    //puts(source.vertexShader);

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