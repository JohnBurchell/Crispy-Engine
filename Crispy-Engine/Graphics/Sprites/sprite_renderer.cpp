#include "sprite_renderer.h"

#include <glm\gtc\matrix_transform.hpp>

Sprite_Renderer::Sprite_Renderer(Shader& shader) : m_VAO{}, m_shader{}
{
	m_shader = shader;
	init_data();
}

Sprite_Renderer::~Sprite_Renderer()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void Sprite_Renderer::init_data()
{
	// Configure VAO/VBO
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};


	Vertex_Buffer_Object VBO{ vertices, sizeof(vertices), 4 };
	VAO.add_buffer(&VBO, 0);
}

void Sprite_Renderer::draw_sprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat rotation, glm::vec3 colour)
{
	m_shader.use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	m_shader.set_matrix4("model", model);
	m_shader.set_vector3f("sprite_colour", colour);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	VAO.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	VAO.unbind();
}