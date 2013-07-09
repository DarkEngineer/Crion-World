#version 420

in vec2 texCoordOut;

uniform sampler2D gShadowMap;

out vec4 fragColor;

void main()
{
	float depth = texture(gShadowMap, texCoordOut).x;
	depth = 1.0 - (1.0 - depth) * 25.0;
	fragColor = vec4(depth);
}