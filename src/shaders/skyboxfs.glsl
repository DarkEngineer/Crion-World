#version 330

in vec2 texCoord0;

out vec4 fragColor;

uniform sampler2D gCubemapTexture;

void main()
{
	fragColor = texture(gCubemapTexture, texCoord0.xy);   
}