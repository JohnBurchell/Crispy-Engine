#include "particle_generator.h"

Particle_Generator::Particle_Generator(Shader & shader, Texture2D & texture, GLuint amount) : 
	m_shader(shader), m_texture(texture), m_amount(amount)
{
	init();
}

void Particle_Generator::update(GLfloat dt, Game_Object & object, GLuint new_particles, glm::vec2 offset)
{
	//Add new particles
	for (GLuint i = 0; i < new_particles; ++i)
	{
		int unused_particle = first_unused_particle();
		respawn_particle(m_particles[unused_particle], object, offset);
	}

	//Update all particles
	for (GLuint i = 0; i < m_amount; ++i)
	{
		Particle& p = m_particles[i];
		//Reduce lifetime
		p.life -= dt;
		if (p.life > 0.0f)
		{
			//Particle is alive, update it.
			p.position -= (p.velocity * dt);
			p.colour.a -= dt * 2.5f;
		}

	}
}

void Particle_Generator::draw()
{
	//This additve blending will give it a "glow" effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	m_shader.use();
	for (auto& x : m_particles)
	{
		if (x.life > 0.0f)
		{
			m_shader.set_vector2f("offset", x.position);
			m_shader.set_vector4f("colour", x.colour);
			m_texture.bind();
			m_VAO.bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			m_VAO.unbind();
		}
	}

	//Reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Particle_Generator::init()
{
	GLfloat vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	Vertex_Buffer_Object VBO{ vertices , sizeof(vertices), 4 };
	m_VAO.add_buffer(&VBO, 0);

	//Create m_amount particles
	for (GLuint i = 0; i < m_amount; ++i)
	{
		m_particles.push_back(Particle());
	}
}

GLuint last_used_particle = 0;

GLuint Particle_Generator::first_unused_particle()
{
	for (GLuint i = last_used_particle; i < m_amount; ++i)
	{
		if (m_particles[i].life <= 0.0f)
		{
			last_used_particle = i;
			return i;
		}
	}

	//All particles are taken
	last_used_particle = 0;
	return 0;
}

void Particle_Generator::respawn_particle(Particle & particle, Game_Object & object, glm::vec2 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	GLfloat rColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.position = object.m_position + random + offset;
	particle.colour = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.life = 1.0f;
	particle.velocity = object.m_velocity * 0.1f;
}
