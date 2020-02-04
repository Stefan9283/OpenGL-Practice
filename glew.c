#include </usr/include/GLFW/glfw3.h>
#include <stdio.h>

/*
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
*/

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("%d\n", key);
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{


if (!glfwInit())
{
   printf("failed\n");
    // Initialization failed
}
//else printf("successful\n");

//double time = glfwGetTime();
GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
glfwMakeContextCurrent(window);
glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glfwSwapBuffers(window);
		glfwSwapInterval(100);

		glfwPollEvents();

		//scanf("%d",&c);
		if (!window)
		{
			   printf("failed\n");

		    // Window or OpenGL context creation failed
		}
		//else printf("successful\n");
	}
glfwDestroyWindow(window);

glfwTerminate();

}