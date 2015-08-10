#include "object.h"

Game_Object::Game_Object() :
	m_position{ 0.0f, 0.0f }, m_size{ 1.0f, 1.0f }, m_velocity{ 0.0f }, m_colour{ 1.0f },
	m_rotation{ 0.0f }, m_sprite{}, m_is_solid{ false }, m_destroyed{ false }
{

}

Game_Object::Game_Object(glm::vec2 pos, glm::vec2 size, Texture2D& sprite, glm::vec3 colour, glm::vec2 velocity) :
	m_position{ pos }, m_size{ size }, m_velocity{ velocity }, m_colour{ colour },
	m_rotation{ 0.0f }, m_sprite{ sprite }, m_is_solid{ false }, m_destroyed{ false }
{

}

void Game_Object::draw(Sprite_Renderer& renderer)
{
	renderer.draw_sprite(m_sprite, m_position, m_size, m_rotation, m_colour);
}
	