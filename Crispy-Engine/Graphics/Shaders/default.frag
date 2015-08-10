#version 330 core

in vec3 our_colour;
out vec4 colour;

void main()
{
	colour = vec4(our_colour, 1.0f);
}