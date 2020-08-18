#include <stdio.h>
#include "glfw3.h"

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
	}

	GLFWwindow* window = glfwCreateWindow(400, 400, "My Title", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glfwSwapBuffers(window);
		glfwSwapInterval(100);

		glfwPollEvents();

		if (!window)
			printf("failed\n");
	}

	glfwDestroyWindow(window);

	glfwTerminate();

return 0;
}