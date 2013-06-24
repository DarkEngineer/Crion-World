#version 420

in vec2 texCoord0;

out vec4 fragColor;

struct DirectionalLight
{
	vec3 color;
	float ambientIntensity;
};

uniform DirectionalLight gDirectionalLight;
uniform sampler2D gSampler;

void main()
{
	fragColor = texture2D(gSampler, texCoord0.xy) * vec4(gDirectionalLight.color, 1.0f) * gDirectionalLight.ambientIntensity;
}