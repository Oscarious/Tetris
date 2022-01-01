#version 330 core

out vec4 frag_color;

in vec3 color;
in vec2 tex_coords;

uniform sampler2D texture1;

void main() {
    //frag_color = mix(texture(texture1, tex_coord), texture(texture2, tex_coord), 0.2);
    frag_color = vec4(color, 1.0) * texture(texture1, tex_coords);
    // frag_color = texture(texture1, tex_coords);
}