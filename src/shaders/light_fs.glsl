#version 420

const int MAX_POINT_LIGHTS = 2;
const int MAX_SPOT_LIGHTS = 2;

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

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float cutoff;
};

uniform int gNumSpotLights;
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS];
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
	float specularFactor;
	if (diffuseFactor > 0)
	{
		diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

		vec3 vertexToEye = normalize(gEyeWorldPos - worldPos0);
		vec3 lightReflect = normalize(reflect(lightDirection, normal));
		specularFactor = dot(vertexToEye, lightReflect);
		specularFactor = pow(specularFactor, gSpecularPower);
	}
	if(specularFactor > 0)
	{
			specularColor = vec4(light.color, 1.0f) * gMatSpecularIntensity * specularFactor;
	}	

	return (ambientColor + diffuseColor + specularColor);
}

vec4 calcDirectionalLight(vec3 normal)
{
	return calcLightInterval(gDirectionalLight.base, gDirectionalLight.direction, normal);
}

vec4 calcPointLight(PointLight light, vec3 normal)
{
	vec3 lightDirection = worldPos0 - light.position;
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection);

	vec4 color = calcLightInterval(light.base, lightDirection, normal);
	float attentuation = light.attentuation.constant +
						 light.attentuation.linear * distance + 
						 light.attentuation.exp * distance * distance;

	return color / attentuation;
}

vec4 calcSpotLights(SpotLight light, vec3 normal)
{
	vec3 lightToPixel = normalize(worldPos0 - light.base.position);
	float spotFactor = dot(lightToPixel, light.direction);

	if(spotFactor < light.cutoff)
	{
		vec4 color = calcPointLight(light.base, normal);

		return color * (1.0 - (1.0 - spotFactor) * 1.0 / (1.0 - light.cutoff));
	}
	else
		return vec4(0, 0, 0, 0);
}



void main()
{
	vec3 normal = normalize(normal0);
	vec4 totalLight = calcDirectionalLight(normal);

	for(int i = 0; i < gNumPointLights; i++)
	{
		totalLight += calcPointLight(gPointLights[i], normal);
	}

	for(int i = 0; i < gNumSpotLights; i++)
	{
		totalLight += calcSpotLights(gSpotLights[i], normal);
	}
	

	fragColor = texture2D(gSampler, texCoord0.xy) * totalLight;
}