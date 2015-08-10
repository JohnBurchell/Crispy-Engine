#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL\soil.h>

//Instantiate static variables
std::map<std::string, Texture2D> Resource_Manager::textures;
std::map<std::string, Shader>    Resource_Manager::shaders;

Shader Resource_Manager::load_shader(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file, std::string name)
{
	shaders[name] = load_shader_from_file(v_shader_file, f_shader_file, g_shader_file);
	return shaders[name];
}

Shader Resource_Manager::get_shader(const std::string& name)
{
	return shaders[name];
}

Texture2D Resource_Manager::load_texture(const GLchar* file, GLboolean alpha, std::string name)
{
	textures[name] = load_texture_from_file(file, alpha);
	return textures[name];
}

Texture2D Resource_Manager::get_texture(std::string name)
{
	return textures[name];
}

Shader Resource_Manager::load_shader_from_file(const GLchar* vertex_shader, const GLchar* fragment_shader, const GLchar* geometry_shader)
{
	//1. Retrieve the vertex & fragment sources from their respective filepaths
	std::string vertex_source;
	std::string fragment_source;
	std::string geometry_source;
	try
	{
		//Open Files
		std::ifstream vertex_shader_file(vertex_shader);
		std::ifstream fragment_shader_file(fragment_shader);
		std::stringstream vertex_stream, fragment_stream;

		//Read file's buffer contents into streams
		vertex_stream << vertex_shader_file.rdbuf();
		fragment_stream << fragment_shader_file.rdbuf();

		//Close file handlers
		vertex_shader_file.close();
		fragment_shader_file.close();

		//Convert stream into string
		vertex_source = vertex_stream.str();
		fragment_source = fragment_stream.str();

		//If geometry shader path is present, also load this.
		if (geometry_shader != nullptr)
		{
			std::ifstream geometry_shader_file(geometry_shader);
			std::stringstream geo_stream;
			geo_stream << geometry_shader_file.rdbuf();
			geometry_shader_file.close();
			geometry_source = geo_stream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR:SHADER: Failed to read shader files. " << std::endl;
		std::cout << "Vertex Path: " << vertex_shader << std::endl;
		std::cout << "Fragment Path: " << fragment_shader << std::endl;
		std::cout << "Geometry Path: " << geometry_shader << std::endl;
	}

	const GLchar* vertex_shader_code = vertex_source.c_str();
	const GLchar* fragment_shader_code = fragment_source.c_str();
	const GLchar* geometry_shader_code = geometry_source.c_str();
	
	//Create shader object from this source
	Shader shader;
	shader.compile(vertex_shader_code, fragment_shader_code, geometry_shader != nullptr ? geometry_shader_code : nullptr);
	return shader;
}

Texture2D Resource_Manager::load_texture_from_file(const GLchar* file, GLboolean alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.m_internal_format = GL_RGBA;
		texture.m_image_format = GL_RGBA;
	}

	//Load image
	int width = 0, height = 0;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.m_image_format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	//Now generate texture
	texture.generate(width, height, image);
	//Finally, free the image data
	SOIL_free_image_data(image);

	return texture;
}

void Resource_Manager::clear()
{
	//Delete all shaders
	for (auto& x : shaders)
	{
		glDeleteProgram(x.second.m_ID);
	}
	//Delete all textures
	for (auto& x : textures)
	{
		glDeleteTextures(1, &x.second.m_ID);
	}
}
