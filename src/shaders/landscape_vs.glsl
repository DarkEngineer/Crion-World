#version 330

in vec3 position0;
in vec2 texCoord0;

out vec2 texCoord;
uniform mat4 gWVP;

void main()
{
	vec4 mat_pos = gWVP * vec4(position0, 1.0);
	gl_Position = mat_pos;
	texCoord = texCoord0;
}