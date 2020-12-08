// Shader to show a simple texture

#type vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoords;

out vec2 texCoords;
out vec3 toLightVector;
out vec3 surfaceNormal;
out vec3 toCameraVector;
out vec3 lightDirection;

uniform mat4 u_viewProjection;
uniform mat4 u_transformation;

uniform vec3 u_cameraPosition;
uniform vec3 u_lightPosition;

void main()
{
	vec4 worldPosition = u_transformation * a_position;
	gl_Position = u_viewProjection * worldPosition;
	
	texCoords = a_texCoords;
	surfaceNormal = normalize((u_transformation * vec4(a_normal, 0.0f)).xyz);
	
	toLightVector = normalize(u_lightPosition - worldPosition.xyz);
	lightDirection = -toLightVector;

	toCameraVector = normalize(u_cameraPosition - worldPosition.xyz);
}

#type pixel
#version 330 core
	
layout(location = 0) out vec4 o_color;

in vec2 texCoords;
in vec3 toLightVector;
in vec3 surfaceNormal;
in vec3 toCameraVector;
in vec3 lightDirection;

uniform vec4 u_lightColor;
uniform vec4 u_color;

uniform float u_ambientReduction;
uniform float u_diffuseReduction;
uniform float u_reflectivity;
uniform float u_shineDamper;

uniform sampler2D u_diffuseTex;

vec3 AmbientLight(vec3 lightColor, float reductionFactor);
vec3 DiffuseLight(vec3 toLightVector, vec3 normal, vec3 lightColor, float reductionFactor);
vec3 SpecularLight(vec3 lightDirection, vec3 normal, vec3 toCameraVector, vec3 lightColor, float reflectivity, float shineDamper);

void main()
{
	vec4 diffuseColor = texture(u_diffuseTex, texCoords) * u_color;
	vec4 ambientLight = vec4(AmbientLight(u_lightColor.xyz, 0.1f), u_ambientReduction);
	vec4 diffuseLight = vec4(DiffuseLight(toLightVector, surfaceNormal, u_lightColor.xyz, u_diffuseReduction), 1.0f);
	vec4 specularLight = vec4(SpecularLight(lightDirection, surfaceNormal, toCameraVector, u_lightColor.xyz, u_reflectivity, u_shineDamper), 1.0f);

	o_color =  diffuseColor * (ambientLight + diffuseLight + specularLight);
}

vec3 AmbientLight(vec3 lightColor, float reductionFactor)
{
	vec3 ambientLight = lightColor * reductionFactor;
	return ambientLight;
}

vec3 DiffuseLight(vec3 toLightVector, vec3 normal, vec3 lightColor, float reductionFactor)
{
	float dotProduct = dot(normal, toLightVector);
	float brightness = max(dotProduct, 0.001f);
	vec3 diffuseLight = lightColor * brightness;

	return diffuseLight;
}

vec3 SpecularLight(vec3 lightDirection, vec3 normal, vec3 toCameraVector, vec3 lightColor, float reflectivity, float shineDamper)
{
	vec3 reflectedLightDirection = reflect(lightDirection, normal);
	
	float specularFactor = dot(reflectedLightDirection, toCameraVector);
	specularFactor = max(specularFactor, 0.001f);

	float dampedFactor = pow(specularFactor, shineDamper);

	vec3 specularLight = lightColor * dampedFactor * reflectivity;

	return specularLight;
}