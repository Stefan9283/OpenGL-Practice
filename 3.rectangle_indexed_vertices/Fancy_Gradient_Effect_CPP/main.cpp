
//#define GL_GLEXT_PROTOTYPES //it ignores all the warnings
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string>
#include <iostream>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void delay(float seconds)
{
    long pause;
    clock_t now,then;

    pause = seconds*CLOCKS_PER_SEC;
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

typedef struct ShaderProgramSource
{
    char vertexShader[10000];
    char fragmentShader[10000];
}ShaderProgramSource;

 ShaderProgramSource ParseShader(const char* filepath)
{
    ShaderProgramSource source;
    memset(source.vertexShader, 0, 10000);
    memset(source.fragmentShader, 0, 10000);
    FILE *f=fopen(filepath,"r");
    char line[100];
    int mode=0;
    while(fgets(line,100,f))
    {
        line[strlen(line)-1]='\0';
        if(!strcmp("#shader vertex",line))
            {
                mode=0; 
                continue;
            }
        else 
            if(!strcmp("#shader fragment",line))
            {
                mode=1;
                continue;
            }

        if(!mode)
            {
                strcat(source.vertexShader,line);
                strcat(source.vertexShader,"\n");
            }
            else
            {
                strcat(source.fragmentShader,line);
                strcat(source.fragmentShader,"\n");
            }
        memset(line, 0, 100);
    }
        source.vertexShader[strlen(source.vertexShader)]='\0';
        source.fragmentShader[strlen(source.fragmentShader)]='\0';
        
    /*
        puts(source.vertexShader);
        printf("///////\n\n\n\n");
        puts(source.fragmentShader);
    */

    fclose(f);
    return source;
}
 unsigned int CompileShader(unsigned int type,const char* source)
{
        unsigned int id = glCreateShader(type);
        const char* src = source;
        glShaderSource(id,1,&src,NULL);
        glCompileShader(id);

        return id;
}
 unsigned int CreateShader(const char* vertexShader, const char* fragmentShader)
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
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
   
    glfwSwapInterval(1);
   
    if(gladLoadGL())
        printf("Glad!");
    
     float r=0.6,g=0.6,b=0.6;
    float r_pas=0.05,g_pas=0.05,b_pas=0.05;

    float positions[]={
        -0.5f, -0.5f, 0.0f,	r,		0.0f, 	0.0f,
         0.5f, -0.5f, 0.0f,	0.0f,	g, 		0.0f,
         0.5f,  0.5f, 0.0f,	0.0f,	0.0f,	b,
        -0.5f,  0.5f, 0.0f,	0.0f,	0.0f,	b

    };

    unsigned int indeces[]={
        0,1,2,
        2,3,0
    };
    unsigned int buffer;
    glGenBuffers(1,&buffer); 
    glBindBuffer(GL_ARRAY_BUFFER,buffer); //binds buffer variable to the GPU buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW); //passes vertex vector to GPU buffer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0); //tells the GPU what the layout of the buffer is
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int ibo;   // ibo = index buffer object
    glGenBuffers(1,&ibo); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo); //binds buffer variable to the GPU buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indeces),indeces,GL_STATIC_DRAW); //passes vertex vector to GPU buffer

    ShaderProgramSource source=ParseShader("basic.shader");
    unsigned int shader = CreateShader(source.vertexShader,source.fragmentShader);
    glUseProgram(shader);

 
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
         
        glClear(GL_COLOR_BUFFER_BIT);

       // glVertexAttrib4f(location,r,g,b,1);
        
        glDrawElements(GL_TRIANGLES, sizeof(indeces), GL_UNSIGNED_INT, nullptr);
        

 

       /* updating the color in the vertex positions and colors array "positions" */
	    glBindBuffer(GL_ARRAY_BUFFER,buffer); //binds buffer variable to the GPU buffer
		glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW); //passes vertex vector to GPU buffer

       //glMapBuffer(buffer,GL_READ_WRITE);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glfwSetKeyCallback(window, key_callback);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}