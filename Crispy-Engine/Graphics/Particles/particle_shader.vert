#version 330 core
layout (location = 0) in vec4 vertex; //<vec2 pos, vec2 tex>

out vec2 tex_coords;
out vec4 particle_colour;

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 colour;

void main()
{
	float scale = 10.0f;
	tex_coords = vertex.zw;
	particle_colour = colour;
	gl_Position = projection * vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}