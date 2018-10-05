#version 400 core

out vec4 frag_color;

in vec2 colors;
uniform sampler2D sampler;

void main()
{
    frag_color = texture(sampler, colors);
}
