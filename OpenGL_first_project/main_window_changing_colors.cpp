#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


int main() {

	// Initialize GLFW
	glfwInit();
	// We are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using CORE profile ( only modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	// width = 400 , height = 225;
	// GLFWwindow* window = glfwCreateWindow(400,225,"OpenGL", NULL, NULL);
	// GLFWwindow 800 by 800 pixels, named "OpenGl"
	 GLFWwindow* window = glfwCreateWindow(800, 800,"OpenGL", NULL, NULL);

	// Check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 800, 800);

	
	// Orange color:
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	// Blue color:
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// variables needed to change colour smoothly
	float previous_time = float(glfwGetTime());
	float angle = 0.0f;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// All of the GLFW events
		if (glfwGetTime())
		{
			float time = float(glfwGetTime());
			if (time - previous_time >= 0.1f) {

				angle += 0.1f;
				previous_time = time;
			}
		}
		glClearColor(float(sin(angle)), float(cos(angle)), float(tan(angle)), 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window); // this function flickers colors
	

		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
