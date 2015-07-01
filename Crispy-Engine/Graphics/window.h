#ifndef WINDOW_H_
#define WINDOW_H_

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window();
	Window(int width, int height, const std::string& title);
	~Window();

	void flip();
	void clear();

	//glfwWindowShouldClose returns an integer, hence the equality check to avoid implicit conversion.
	inline bool window_is_open() const { return glfwWindowShouldClose(window) == 1; };

	GLFWwindow* window;

private:

	//Disable Copy and assignment operators
	//Disable move as well?
	Window(Window& lhs);

	//void set_title(std::string title);
};

#endif //WINDOW_H_