#ifndef OBJECT_H_
#define OBJECT_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Textures/texture.h"
#include "../Sprites/sprite_renderer.h"

class Game_Object
{
public:
	//Object state
	glm::vec2 m_position, m_size, m_velocity;
	glm::vec3 m_colour;
	GLfloat m_rotation;
	GLboolean m_is_solid;
	GLboolean m_destroyed;
	//Render state
	Texture2D m_sprite;
	//Constructors
	Game_Object();
	Game_Object(glm::vec2 pos, glm::vec2 size, Texture2D& sprite, glm::vec3 colour = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	//Draw sprite
	virtual void draw(Sprite_Renderer& renderer);
};

#endif //OBJECT_H_
