#version 420

const int MAX_POINT_LIGHTS = 2;

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 fragColor;

struct BaseLight
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};
struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

struct Attentuation
{
	float constant;
	float linear;
	float exp;
};

struct PointLight
{
	BaseLight base;
	vec3 position;
	Attentuation attentuation;
};

uniform int gNumPointLights;
uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLights[MAX_POINT_LIGHTS];
uniform sampler2D gSampler;
uniform vec3 gEyeWorldPos;
uniform float gMatSpecularIntensity;
uniform float gSpecularPower;

vec4 calcLightInterval(BaseLight light, vec3 lightDirection, vec3 normal)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;

	float diffuseFactor = dot(normal, -lightDirection);
	
	vec4 diffuseColor = vec4(0, 0, 0, 0);
	vec4 specularColor = vec4(0, 0, 0, 0);

	if (diffuseFactor > 0)
	{
		diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

		vec3 vertexToEye = normalize(gEyeWorldPos - worldPos0);
		vec3 lightReflect = normalize(reflect(gDirectionalLight.direction, normal));
		float specularFactor = dot(vertexToEye, lightReflect);
		specularFactor = pow(specularFactor, gSpecularPower);
		if(specularFactor > 0)
		{
			specularColor = vec4(light.color, 1.0f) * gMatSpecularIntensity * specularFactor;
		}	
	}

	return (ambientColor + diffuseColor + specularColor);
}

vec4 calcDirectionalLight(vec3 normal)
{
	return calcLightInterval(gDirectionalLight.base, gDirectionalLight.direction, normal);
}

vec4 calcPointLight(int index, vec3 normal)
{
	vec3 lightDirection = worldPos0 - gPointLights[index].position;
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection);

	vec4 color = calcLightInterval(gPointLights[index].base, lightDirection, normal);
	float attentuation = gPointLights[index].attentuation.constant + gPointLights[index].attentuation.linear * distance + gPointLights[index].attentuation.exp * distance * distance;

	return color / attentuation;
}

void main()
{
	vec3 normal = normalize(normal0);
	vec4 totalLight = calcDirectionalLight(normal);

	for(int i = 0; i < gNumPointLights; i++)
	{
		totalLight += calcPointLight(i, normal);
	}
	

	fragColor = texture2D(gSampler, texCoord0.xy) * totalLight;
}