#pragma once
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <glm\common.hpp>

class Particle
{
public:
	Particle() : m_position(0.0f), m_velocity(0.0f), m_colour(0.0f), m_life(0.0f) {};
	Particle(float position, float velocity, float colour, float life) : m_position(position), m_velocity(velocity), m_colour(colour), m_life(life) {};

private:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_colour;
	float m_life;
};

#endif //PARTICLE_H_