#version 330

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D gTexture;

void main()
{
	fragColor = texture(gTexture, texCoord);
}

