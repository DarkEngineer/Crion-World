#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord0;
uniform mat4 gWorld;

void main()
{	
	gl_Position = gWorld * vec4(position, 1.0);
	texCoord0 = TexCoord;
}