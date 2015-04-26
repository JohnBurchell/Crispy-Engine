#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h> // Include all the OpenGL headers
#include <GLFW/glfw3.h> // Include the glew headers

#pragma once
class Shader
{
public:
	//ID of the program
	GLuint Program;
	Shader(const GLchar* vertex_source_path, const GLchar* fragment_shader_source_path);
	void use();
};

#endif //SHADER_H_
