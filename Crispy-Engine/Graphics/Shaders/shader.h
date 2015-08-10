#ifndef SHADER_H_
#define SHADER_H_

#define GLEW_STATIC
#include <GL/glew.h> // Include all the OpenGL headers
#include <GLFW/glfw3.h> // Include the glew headers

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <sstream>

class Shader
{
public:
	//ID of the program
	GLuint m_ID;
	//Vertex First and Fragment second
	Shader();

	void compile(const GLchar* vertex_source_path, const GLchar* fragment_shader_source_path, const GLchar* geometry_source_path = nullptr);

	//Utility functions
	void set_float(const GLchar* name, GLfloat value, GLboolean use_shader = false);
	void set_integer(const GLchar* name, GLint value, GLboolean use_shader = false);
	void set_vector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean use_shader = false);
	void set_vector2f(const GLchar* name, glm::vec2& value, GLboolean use_shader = false);
	void set_vector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean use_shader = false);
	void set_vector3f(const GLchar* name, glm::vec3& value, GLboolean use_shader = false);
	void set_vector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean use_shader = false);
	void set_vector4f(const GLchar* name, glm::vec4& value, GLboolean use_shader = false);
	void set_matrix4(const GLchar* name, glm::mat4& matrix, GLboolean use_shader = false);

	void check_compile_errors(GLuint object, std::string type);

	Shader& use();
};

#endif //SHADER_H_
