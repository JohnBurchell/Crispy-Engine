#ifndef WINDOW_H_
#define WINDOW_H_

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();

	inline bool window_is_open() const { return glfwWindowShouldClose(window); };

	GLFWwindow* window;

private:

	//Disable Copy and assignment operators
	//Disable move as well?
	Window(Window& lhs);

	//void set_title(std::string title);
};

#endif //WINDOW_H_