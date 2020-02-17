
//#define GL_GLEXT_PROTOTYPES //it ignores all the warnings
#include <GL/glew.h>
#include <GL/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string>
#include <iostream>

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
	char vertexShader[1000];
	char fragmentShader[1000];
}ShaderProgramSource;

static ShaderProgramSource ParseShader(const char* filepath)
{
	ShaderProgramSource source;

	FILE *f=fopen(filepath,"r");
	char line[100];
	int mode=0;
	while(fgets(line,100,f))
	{
		line[strlen(line)-1]='\0';
		if(!strcmp("#shader vertex",line))
    		{
                memset(source.vertexShader, 0, 1000);
    			mode=0;	
    			continue;
    		}
		else 
            if(!strcmp("#shader fragment",line))
    		{
                memset(source.fragmentShader, 0, 1000);
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
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
   
    glfwSwapInterval(1);
   
    if(glewInit()!=GLEW_OK)
    	printf("glew!");
    
    float positions[]={
    	-0.5f, -0.5f,
    	 0.5f, -0.5f,
    	 0.5f,  0.5f,
    	-0.5f,  0.5f

    };

    unsigned int indeces[]={
    	0,1,2,
    	2,3,0
    };
    unsigned int buffer;
    glGenBuffers(1,&buffer); 
    glBindBuffer(GL_ARRAY_BUFFER,buffer); //binds buffer variable to the GPU buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW); //passes vertex vector to GPU buffer

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //tells the GPU what the layout of the buffer is
    glEnableVertexAttribArray(0);

    unsigned int ibo;	// ibo = index buffer object
    glGenBuffers(1,&ibo); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo); //binds buffer variable to the GPU buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(unsigned int),indeces,GL_STATIC_DRAW); //passes vertex vector to GPU buffer



    ShaderProgramSource source=ParseShader("basic.shader");

    unsigned int shader = CreateShader(source.vertexShader,source.fragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader,"u_Color");

    float r=0.0,g=0.0,b=0.4;
    float r_pas=0.05,g_pas=0.05,b_pas=0.05;
	//glUniform4f(location,r,g,b,1);
    glUniform4f(location,r,g,b,1);
    int *nullp=NULL;
    
    std :: string s = "Chestia asta merge doar in C++";
	std :: cout << s << std :: endl ;
 
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
    	 
        glClear(GL_COLOR_BUFFER_BIT);

    	glUniform4f(location,r,g,b,1);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullp);
        



        if(r>=1)r_pas=-0.002f;
        	else if(r<=0)r_pas=0.005f;
        if(g>=1)g_pas=-0.004f;else if(g<=0)g_pas=0.007f;
         
        if(b>=1)b_pas=-0.005f;else if(b<=0)b_pas=0.006f;
        //printf("%.3f %.3f %.3f \n",r,g,b);
        r=r+r_pas;
        g+=g_pas;
        b+=b_pas;
       
        
		delay(0.01);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}