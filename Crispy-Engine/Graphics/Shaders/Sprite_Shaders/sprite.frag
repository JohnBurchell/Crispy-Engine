#version 330 core
in vec2 tex_coords;
in vec3 frag_pos;
out vec4 colour;

uniform sampler2D image;
uniform vec3 sprite_colour;
uniform vec3 light_position;

void main()
{
	float intensity = 100.0 / length(vec3(frag_pos.xy, 1.0f) - light_position);
	colour = vec4(sprite_colour, 1.0) * (texture(image, tex_coords) * intensity);
}
