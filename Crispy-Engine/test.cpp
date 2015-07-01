//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "Graphics\window.h"
#include "Graphics\Core\vertexbuffer.h"
#include "Graphics\Core\vertexbufferarray.h"

#include <iostream>

GLuint shaderProgram;
GLuint shaderProgram_yellow;

GLuint fragmentShader;
GLuint vertexShader;
GLuint frag_shader_yellow;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 colour; \n"
	"out vec3 our_colour;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position, 1.0);\n"
	"our_colour = colour;\n"
	"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
	"in vec3 our_colour;\n"
	"out vec4 colour;\n"
	"void main()\n"
	"{\n"
	"colour = vec4(our_colour, 1.0f);\n"
	"}\n\0";

void tut_two_shaders()
{

	//Create a shader object in the same way a VBO is created.
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Attach the code and compile the shader.
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	//Check for errors during compilation.
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Compile Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	//Check for errors during compilation.
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Attach the shaders to the program.
	shaderProgram = glCreateProgram();
	shaderProgram_yellow = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check that linking worked correctly
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_ERROR\n" << infoLog << std::endl;
	}
	//Delete the shaders as they are no longer needed anymore. Frees up memory perhaps?
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//Callback for handling key presses.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//When the user presses the escape key, set WindowShouldClose to true, thus closing the application.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main()
{
	Window window;

	glfwSetKeyCallback(window.window, key_callback);

	//Tutorial Two
	tut_two_shaders();

	GLfloat vertices[] =
	{
		//Positions - x,y,z  - Colours r,g,b
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //Top
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  //Bottom Left
	};

	GLuint VAOs[1];
	GLuint EBO;

	Vertex_Buffer VBO(vertices, sizeof(vertices), 3);

	glGenVertexArrays(1, VAOs);
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO.get_index());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//Simple loop
	while (!window.window_is_open())
	{
		glfwPollEvents();

		window.clear();

		GLint vertex_colour_location = glGetUniformLocation(shaderProgram, "our_colour");

		glUseProgram(shaderProgram);

		//Drawning
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//Polygon mode aka wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(0);



		window.flip();
	}

	//Cleanup
	return 0;
}
