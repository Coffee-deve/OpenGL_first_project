#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f, 0.0f, 0.2f, 1.0f);\n" //  This sets the figure color
"}\n\0";

int main() {

	// Initialize GLFW
	glfwInit();
	// We are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using CORE profile ( only modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

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

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program = (Vertex + Fragment) and get its reference
	GLuint shaderProgram = glCreateProgram();

	//Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/ Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertices coordinates
	GLfloat vertices[] =  // wierzcholki z kolorem, pozycja, texture
	{
		-0.5f, -0.5f,   // left corner
		-0.5f, 0.5f,  // top left corner
		0.5f, 0.5f, // top right corner
		0.5f, -0.5f // right corner
		

	};

	// Reference integer for vertex object buffer
	// Buffer for storing Vertex Data
	GLuint VAOs[1], VBOs[1]; // VBO is an array of references

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, VAOs);
	glGenBuffers(1, VBOs); // buffer object

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	// store vertices in the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure the Vertex Attribute so that OPENGL knows how to read the VBO
	// where to find vbos and how to interpret them
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OPENGL knows to use it
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// All of the GLFW events
		glClearColor(0.5f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGl which Shader Program we want to use
		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);// bind VAO so OpenGL knows how to use it
		// Draw outline of a Square
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glfwSwapBuffers(window); // this function flickers colors

		glfwPollEvents();
	}
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
