#version 330 core

layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_tex_coords;

out vec3 color;
out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * vec4(in_pos, 0.0f, 1.0f);
	color = in_color;
	tex_coords = in_tex_coords;
}