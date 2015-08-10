#include "shader.h"

Shader::Shader()
{

}

void Shader::compile(const GLchar* vertex_source_path, const GLchar* fragment_shader_source_path, const GLchar* geometry_source_path)
{
	GLuint s_vertex, s_fragment, g_shader;

	//Vertex Shader
	s_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(s_vertex, 1, &vertex_source_path, nullptr);
	glCompileShader(s_vertex);
	check_compile_errors(s_vertex, "VERTEX");

	//Fragment Shader
	s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(s_fragment, 1, &fragment_shader_source_path, nullptr);
	glCompileShader(s_fragment);
	check_compile_errors(s_fragment, "FRAGMENT");

	//If there is a geometry source, compile also
	if (geometry_source_path != nullptr)
	{
		g_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(g_shader, 1, &geometry_source_path, nullptr);
		glCompileShader(g_shader);
		check_compile_errors(g_shader, "GEOMETRY");
	}

	//Shader Program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, s_vertex);
	glAttachShader(m_ID, s_fragment);
	
	//Likewise, if the geometry exists attach the shader
	if (geometry_source_path != nullptr)
	{
		glAttachShader(m_ID, g_shader);
	}
	
	glLinkProgram(m_ID);
	check_compile_errors(m_ID, "PROGRAM");
	//Delete the shaders as they're linked into our program and are now no longer required.
	glDeleteShader(s_vertex);
	glDeleteShader(s_fragment);

	if (geometry_source_path != nullptr)
	{
		glDeleteShader(g_shader);
	}

}

void Shader::set_float(const GLchar* name, GLfloat value, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform1f(glGetUniformLocation(m_ID, name), value);
}
void Shader::set_integer(const GLchar* name, GLint value, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform1i(glGetUniformLocation(m_ID, name), value);
}

void Shader::set_vector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform2f(glGetUniformLocation(m_ID, name), x, y);
}

void Shader::set_vector2f(const GLchar* name, glm::vec2& value, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
}

void Shader::set_vector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform3f(glGetUniformLocation(m_ID, name), x, y, z);
}

void Shader::set_vector3f(const GLchar* name, glm::vec3& value, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
}

void Shader::set_vector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform4f(glGetUniformLocation(m_ID, name), x, y, z, w);
}

void Shader::set_vector4f(const GLchar* name, glm::vec4& value, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
}

void Shader::set_matrix4(const GLchar* name, glm::mat4& matrix, GLboolean use_shader)
{
	if (use_shader)
		use();
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::check_compile_errors(GLuint object, std::string type)
{
	GLint success;
	GLchar info_log[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, nullptr, info_log);
			std::cout << "| ERROR::SHADER: Compile-Time error: Type: " << type << "\n"
				<< info_log << "\n -- -------------------------------------------- -- "
				<< std::endl;

			system("pause");

		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(object, 1024, nullptr, info_log);
			std::cout << "| ERROR::SHADER: Link-Time error: Type: " << type << "\n"
				<< info_log << "\n -- -------------------------------------------- -- "
				<< std::endl;

			system("pause");

		}
	}
}

Shader& Shader::use()
{
	//I recall something about this in ECPP - Look it up.
	glUseProgram(m_ID);
	return *this;
}


