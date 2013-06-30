#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 normal;

out vec2 texCoord0;
out vec3 normal0;
out vec3 worldPos0;
uniform mat4 gWorld;
uniform mat4 gWVP;

void main()
{	
	gl_Position = gWVP * vec4(position, 1.0);
	texCoord0 = TexCoord;
	normal0 = (gWorld * vec4(normal, 0.0)).xyz;
	worldPos0 = (gWorld * vec4(position, 1.0)).xyz;
}