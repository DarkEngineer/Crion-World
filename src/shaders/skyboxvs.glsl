#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 texCoord0;
uniform mat4 gWVP;

void main()
{
	vec4 matrix_pos = gWVP * vec4(position, 1.0);
	gl_Position = matrix_pos.xyww;
	vec3 normal0 = normal;
	texCoord0 = texCoord;
}