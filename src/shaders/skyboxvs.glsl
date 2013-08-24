#version 330

in vec3 position;

uniform mat4 gWVP;

out vec3 texCoord0;

void main()
{
	vec4 matrix_pos = gWVP * vec4(position, 1.0);
	gl_Position = matrix_pos.xyzw;
	texCoord0 = position;
}