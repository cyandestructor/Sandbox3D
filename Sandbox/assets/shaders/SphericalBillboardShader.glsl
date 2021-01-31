#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;

uniform mat4 u_viewProjection;
uniform vec3 u_cameraRightWS;
uniform vec3 u_cameraUpWS;
uniform vec3 u_billboardPosition;
uniform vec3 u_billboardScale;

uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

uniform vec4 u_clipPlane;

out float gl_ClipDistance[1];

out vec2 texCoords;
out vec3 normal;

out vec3 toLightVector;
out vec3 lightDirection;
out vec3 toCameraVector;

void main()
{
	vec3 rightVector = u_cameraRightWS;
	vec3 upVector = u_cameraUpWS;
	
	normal = normalize(cross(rightVector, upVector));
	vec3 tangent = normalize(rightVector);
	vec3 bitangent = upVector;

	mat3 tbn = transpose(mat3(tangent, bitangent, normal)); // To convert from world space to tangent space

	vec3 worldPosition =
    u_billboardPosition
    + rightVector * a_position.x * u_billboardScale.x
    + upVector * a_position.y * u_billboardScale.y;

	gl_Position = u_viewProjection * vec4(worldPosition, 1.0f);
	gl_ClipDistance[0] = dot(vec4(worldPosition, 1.0f), u_clipPlane);

	texCoords = a_texCoords;

	toLightVector = tbn * normalize(u_lightPosition - worldPosition);
	lightDirection = -toLightVector;
	toCameraVector = tbn * normalize(u_cameraPosition - worldPosition);
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 o_color;
	
in vec2 texCoords;

in vec3 toLightVector;
in vec3 lightDirection;
in vec3 toCameraVector;

uniform vec4 u_color;
uniform vec4 u_lightColor;

uniform float u_ambientReduction;
uniform float u_diffuseReduction;
uniform float u_reflectivity;
uniform float u_shineDamper;

uniform sampler2D u_diffuseTex;
uniform sampler2D u_normalTex;

vec3 AmbientLight(vec3 lightColor, float reductionFactor);
vec3 DiffuseLight(vec3 toLightVector, vec3 normal, vec3 lightColor, float reductionFactor);
vec3 SpecularLight(vec3 lightDirection, vec3 normal, vec3 toCameraVector, vec3 lightColor, float reflectivity, float shineDamper);

void main()
{
	vec3 texNormal = texture(u_normalTex, texCoords).rgb;
	texNormal = normalize(texNormal * 2.0f - 1.0f);

	vec4 ambientLight = vec4(AmbientLight(u_lightColor.rgb, u_ambientReduction), 1.0f);
	vec4 diffuseLight = vec4(DiffuseLight(toLightVector, texNormal, u_lightColor.rgb, u_diffuseReduction), 1.0f);
	vec4 specularLight = vec4(SpecularLight(lightDirection, texNormal, toCameraVector, u_lightColor.rgb, u_reflectivity, u_shineDamper), 1.0f);

	vec4 diffuseColor = texture(u_diffuseTex, texCoords) * u_color;

	vec4 color = diffuseColor * (ambientLight + diffuseLight + specularLight);
	
	if(color.a < 0.5f)
	{
		discard;
	}
	else
	{
		o_color = color;
	}
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