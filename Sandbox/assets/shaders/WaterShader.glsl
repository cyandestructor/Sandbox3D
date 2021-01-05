#type vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoords;

out vec2 texCoords;
out vec3 toCameraVector;
out vec3 toLightVector;
out vec3 lightDirection;
out vec4 clipSpace;

uniform mat4 u_viewProjection;
uniform mat4 u_transformation;

uniform vec3 u_cameraPosition;
uniform vec3 u_lightPosition;

uniform float u_tilingFactor;

void main()
{
	vec4 worldPosition = u_transformation * a_position;
	clipSpace = u_viewProjection * worldPosition;
	gl_Position = clipSpace;

	toCameraVector = normalize(u_cameraPosition - worldPosition.xyz);
	toLightVector = normalize(u_lightPosition - worldPosition.xyz);
	lightDirection = -toLightVector;

	texCoords = a_texCoords * u_tilingFactor;
}

#type fragment
#version 330 core

in vec2 texCoords;
in vec3 toCameraVector;
in vec3 toLightVector;
in vec3 lightDirection;
in vec4 clipSpace;

layout(location = 0) out vec4 o_color;

uniform float u_distortionFactor;
uniform float u_motionFactor;

uniform float u_reflectivity;
uniform float u_shineDamper;

uniform vec4 u_lightColor;
uniform vec4 u_color;

//uniform sampler2D u_reflection;
uniform sampler2D u_refraction;

uniform sampler2D u_distortion;
uniform sampler2D u_normal;

vec3 SpecularLight(vec3 lightDirection, vec3 normal, vec3 toCameraVector, vec3 lightColor, float reflectivity, float shineDamper);

void main()
{
	vec2 projectiveTexCoords = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;
	vec2 refractionTexCoords = projectiveTexCoords;
	vec2 reflectionTexCoords = vec2(projectiveTexCoords.x, -projectiveTexCoords.y);

	vec4 distortionMap = texture(u_distortion, vec2(texCoords.x + u_motionFactor, texCoords.y));
	vec2 distortedTexCoords = distortionMap.rg * 0.1f;
	distortedTexCoords = texCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + u_motionFactor);
	distortionMap = texture(u_distortion, distortedTexCoords);
	vec2 distortion = (distortionMap.rg * 2.0f - 1.0f) * u_distortionFactor;

	vec4 normalMap = texture(u_normal, distortedTexCoords);
	vec3 normal = normalize(vec3(normalMap.r * 2.0f - 1.0f, normalMap.b, normalMap.g * 2.0f - 1.0f));

	vec3 specular = SpecularLight(lightDirection, normal, toCameraVector, u_lightColor.rgb, u_reflectivity, u_shineDamper);

	refractionTexCoords += distortion;
	reflectionTexCoords += distortion;

	// Clamp the reflection and refraction coordinates so that they do not cause texture bugs on edges
	refractionTexCoords = clamp(refractionTexCoords, 0.001, 0.999);
	reflectionTexCoords.x = clamp(reflectionTexCoords.x, 0.0001, 0.9990);
	reflectionTexCoords.y = clamp(reflectionTexCoords.y, -0.9999, -0.0001);

	//vec4 reflection = texture(u_reflection, reflectionTexCoords);
	vec4 refraction = texture(u_refraction, refractionTexCoords);

	o_color = mix(refraction, u_color, 0.2f) + vec4(specular, 0.0f);
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