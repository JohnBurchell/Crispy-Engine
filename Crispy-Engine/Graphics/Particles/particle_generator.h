#ifndef PARTICLE_GENERATOR_H_
#define PARTICLE_GENERATOR_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/common.hpp>

#include "../Textures/texture.h"
#include "../Shaders/shader.h"
#include "../Objects/object.h"
#include "../Core/vertex_buffer_array.h"
#include "../Core/vertex_buffer_object.h"

#include <vector>


class Particle
{
public:
	glm::vec2 position, velocity;
	glm::vec4 colour;
	GLfloat life;

	Particle() : position{ 0.0f }, velocity{ 0.0f }, colour{ 0.0f } {}
};


class Particle_Generator
{

public:
	Particle_Generator(Shader& shader, Texture2D& texture, GLuint ammount);

	//Update all particles
	void update(GLfloat dt, Game_Object& object, GLuint new_particles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void draw();

private:
	//State
	std::vector<Particle> m_particles;
	GLuint m_amount;
	//Render state
	Shader m_shader;
	Texture2D m_texture;

	Vertex_Buffer_Array m_VAO;

	//Init buffer and vertex attributes
	void init();
	//Return first particle index
	GLuint first_unused_particle();
	//Respawns particle
	void respawn_particle(Particle& particle, Game_Object& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif //PARTICLE_GENERATOR_H_
