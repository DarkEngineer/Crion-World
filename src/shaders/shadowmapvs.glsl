#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 gWVP;

out vec2 texCoordOut;

void main()
{
	gl_Position = gWVP * vec4(position, 1.0);
	texCoordOut = texCoord;
}