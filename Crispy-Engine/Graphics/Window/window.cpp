#include "window.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <string>

Window::Window()
{
	//Initialise glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Set window size, title
	window = glfwCreateWindow(800, 600, "Engine Tests", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//Check to make sure the window is not null. If it is, terminate.
	if (window == nullptr)
	{
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
	}

	//Initialise GLEW
	//glewExperimental allows us to use modern techniques. Not setting it to true might lead to complications
	glewExperimental = GL_TRUE;
	glewInit();
	//Bug with glewInit() causes OpenGL to throw a 1280, catch it here.
	glGetError();

	//Tell OpenGL the size of the window, or in this case the viewport, that we wish to render to
	glViewport(0, 0, 800, 600);

	//enable face culling and alpha blending
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::clear() const 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::flip()
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "OpenGL Error: " << error << std::endl;
		std::cerr << glewGetErrorString(error) << std::endl;
	}

	glfwSwapBuffers(window);
}

Window::Window(int width, int height, const std::string& title)
{
	//Initialise glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Set window size, title
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//Check to make sure the window is not null. If it is, terminate.
	if (window == NULL)
	{
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
	}

	//Initialise GLEW
	//glewExperimental allows us to use modern techniques. Not setting it to true might lead to complications
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialise glew" << std::endl;

	}

	//Tell OpenGL the size of the window, or in this case the viewport, that we wish to render to
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwTerminate();
}