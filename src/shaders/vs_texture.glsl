#version 420

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 normal;

uniform mat4 gWorld;
uniform mat4 gWVP;
uniform mat4 gLightMatrix;
uniform mat3 gNormalMatrix;

out vec4 lightSpacePos;
out vec2 texCoord0;
out vec3 normal0;
out vec3 worldPos0;

void main()
{	
	gl_Position = gWVP * vec4(position, 1.0);
	lightSpacePos = gLightMatrix * vec4(position, 1.0);
	texCoord0 = TexCoord;
	mat4 normalMatrix = inverse(gWorld);
	normal0 = vec3(gNormalMatrix * normal);
	worldPos0 = vec3(gWorld * vec4(position, 1.0));

}