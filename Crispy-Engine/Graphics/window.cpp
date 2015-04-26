#include "window.h"

Window::Window()
{
	//Initialise glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Set window size, title
	window = glfwCreateWindow(800, 600, "Learning some OpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//TODO -- print to stderr if these fail.

	//Check to make sure the window is not null. If it is, terminate.
	if (window == nullptr)
	{
		glfwTerminate();
	}

	//Initialise GLEW
	//glewExperimental allows us to use modern techniques. Not setting it to true might lead to complications
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{

	}

	//Tell OpenGL the size of the window, or in this case the viewport, that we wish to render to
	glViewport(0, 0, 800, 600);
}

Window::~Window()
{
	glfwTerminate();
}