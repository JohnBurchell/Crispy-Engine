#ifndef SPRITE_SHADER_H_
#define SPRITE_SHADER_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/common.hpp>

#include "../Shaders/shader.h"
#include "../Core/index_buffer_array.h"
#include "../Core/vertex_buffer_array.h"
#include "../Core/vertex_buffer_object.h"
#include "../Textures/texture.h"

class Sprite_Renderer
{
public:
	Sprite_Renderer(Shader& shader);
	~Sprite_Renderer();

	void draw_sprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));
private:

	Shader m_shader;
	GLuint m_VAO;
	Vertex_Buffer_Array VAO;
	void init_data();

};

#endif //SPRITE_SHADER_H_
