#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 tex_coords>

out vec2 tex_coords;
out vec3 frag_pos;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	tex_coords = vertex.zw;
	frag_pos = vec3(model * vec4(vertex.xy, 0.0f, 1.0f));
	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}