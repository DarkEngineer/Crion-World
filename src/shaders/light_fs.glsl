#version 420

const int MAX_POINT_LIGHTS = 2;
const int MAX_SPOT_LIGHTS = 2;

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;
in vec4 lightSpacePos;

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
uniform sampler2D gShadowMap;
uniform vec3 gEyeWorldPos;
uniform float gMatSpecularIntensity;
uniform float gSpecularPower;

float calcShadowFactor(vec4 lightSpacePos)
{
	vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
	vec2 UVCoords;
	UVCoords.x = 0.5 * projCoords.x + 0.5;
	UVCoords.y = 0.5 * projCoords.y + 0.5;
	float z = 0.5 * projCoords.z + 0.5;
	float depth = texture(gShadowMap, UVCoords).x;
	if(depth < z + 0.00001)
	{
		return 0.5;
	}
	else 
		return 1.0;
}

vec4 calcLightInterval(BaseLight light, vec3 lightDirection, vec3 normal, float shadowFactor)
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

	return (ambientColor + shadowFactor * (diffuseColor + specularColor));
}

vec4 calcDirectionalLight(vec3 normal)
{
	return calcLightInterval(gDirectionalLight.base, gDirectionalLight.direction, normal, 1.0);
}

vec4 calcPointLight(PointLight light, vec3 normal, vec4 lightSpacePos)
{
	vec3 lightDirection = worldPos0 - light.position;
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection);
	float shadowFactor = calcShadowFactor(lightSpacePos); 
	vec4 color = calcLightInterval(light.base, lightDirection, normal, shadowFactor);
	float attentuation = light.attentuation.constant +
						 light.attentuation.linear * distance + 
						 light.attentuation.exp * distance * distance;

	return color / attentuation;
}

vec4 calcSpotLights(SpotLight light, vec3 normal, vec4 lightSpacePos)
{
	vec3 lightToPixel = normalize(worldPos0 - light.base.position);
	float spotFactor = dot(lightToPixel, light.direction);

	if(spotFactor < light.cutoff)
	{
		vec4 color = calcPointLight(light.base, normal, lightSpacePos);

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
		totalLight += calcPointLight(gPointLights[i], normal, lightSpacePos);
	}

	for(int i = 0; i < gNumSpotLights; i++)
	{
		totalLight += calcSpotLights(gSpotLights[i], normal, lightSpacePos);
	}
	

	fragColor = texture2D(gSampler, texCoord0.xy) * totalLight;
}