#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <map>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>

#include "../Textures/texture.h"
#include "../Shaders/shader.h"

class Resource_Manager
{

public:
	//Resource Storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;

	//Load and generate a shader program from a file loading vertex, fragment and if given, geometry shader.
	static Shader load_shader(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file, std::string name);
	//Retrieve a stored shader
	static Shader get_shader(const std::string& name);
	//Loads (and generates) a texture from a file
	static Texture2D load_texture(const GLchar* file, GLboolean alpha, std::string name);
	//Retrieve a stored texture
	static Texture2D get_texture(std::string name);
	//Properly de-allocate all loaded resources
	static void clear();

private:
	//Private constructore - do not want to allow any instances of a resource manager
	Resource_Manager() {}
	//Loads and generates a shader from a file
	static Shader load_shader_from_file(const GLchar* vertex_shader, const GLchar* fragment_shader, const GLchar* geometry_shader = nullptr);
	//Loads a single texture from a file
	static Texture2D load_texture_from_file(const GLchar* file, GLboolean alpha);

};

#endif //RESOURCE_MANAGER_H_
