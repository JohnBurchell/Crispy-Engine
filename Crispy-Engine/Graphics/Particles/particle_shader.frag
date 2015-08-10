#version 330 core
in vec2 tex_coords;
in vec4 particle_colour;
out vec4 colour;

uniform sampler2D sprite;

void main()
{
	colour = (texture(sprite, tex_coords) * particle_colour);
}