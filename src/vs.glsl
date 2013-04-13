#version 330

in vec3 color;
in vec4 position;

out vec3 Color;

uniform mat4 MVP;

void main()
{
	Color = color;
    gl_Position = MVP * position;
}