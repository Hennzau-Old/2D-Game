#version 400 core

layout(location = 0) in vec2 v_position;
layout(location = 1) in vec2 v_colors;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 colors;

void main()
{
    colors = v_colors;

    gl_Position = projection * view * model * vec4(v_position, 0.0, 1.0);
}
