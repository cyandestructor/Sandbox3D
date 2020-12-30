// Shader to show a simple texture

#type vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoords;
layout(location = 3) in vec3 a_tangent;
layout(location = 4) in vec3 a_bitangent;

out vec2 texCoords;
out vec3 toLightVector;
out vec3 lightDirection;

uniform mat4 u_viewProjection;
uniform mat4 u_transformation;

uniform vec3 u_lightPosition;

void main()
{
	vec4 worldPosition = u_transformation * a_position;
	gl_Position = u_viewProjection * worldPosition;
	texCoords = a_texCoords;

	// TBN matrix
	vec3 T = normalize((u_transformation * vec4(a_tangent, 0.0f)).xyz);
	vec3 B = normalize((u_transformation * vec4(a_bitangent, 0.0f)).xyz);
	vec3 N = normalize((u_transformation * vec4(a_normal, 0.0f)).xyz);
	mat3 TBN = transpose(mat3(T, B, N)); // To convert from world space to tangent space

	// Convert to tangent space
	toLightVector = TBN * normalize(u_lightPosition - worldPosition.xyz);
	lightDirection = -toLightVector;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 o_color;
	
in vec2 texCoords;
in vec3 toLightVector;
in vec3 lightDirection;

uniform float u_repeatFactor;

uniform float u_ambientReduction;
uniform float u_diffuseReduction;

uniform vec4 u_lightColor;

uniform sampler2D u_blendMap;
uniform sampler2D u_diffuseTex; // main color
uniform sampler2D u_normalTex;
uniform sampler2D u_diffuseTexR; // red channel
uniform sampler2D u_normalTexR;
uniform sampler2D u_diffuseTexG; // green channel
uniform sampler2D u_normalTexG;
uniform sampler2D u_diffuseTexB; // blue channel
uniform sampler2D u_normalTexB;

vec4 CalculateColorBlend(sampler2D blend, sampler2D bg, sampler2D red, sampler2D green, sampler2D blue, vec2 texCoords, float repeat);

vec3 AmbientLight(vec3 lightColor, float reductionFactor);
vec3 DiffuseLight(vec3 toLightVector, vec3 normal, vec3 lightColor, float reductionFactor);
vec3 SpecularLight(vec3 lightDirection, vec3 normal, vec3 toCameraVector, vec3 lightColor, float reflectivity, float shineDamper);

void main()
{
	vec4 normalColor = CalculateColorBlend(u_blendMap, u_normalTex, u_normalTexR, u_normalTexG, u_normalTexB, texCoords, u_repeatFactor);
	
	vec3 texNormal = normalColor.rgb;
	texNormal = normalize(texNormal * 2.0f - 1.0f);
	
	vec4 texColor = CalculateColorBlend(u_blendMap, u_diffuseTex, u_diffuseTexR, u_diffuseTexG, u_diffuseTexB, texCoords, u_repeatFactor);
	
	vec4 ambientLight = vec4(AmbientLight(u_lightColor.xyz, u_ambientReduction), 1.0f);
	vec4 diffuseLight = vec4(DiffuseLight(toLightVector, texNormal, u_lightColor.xyz, u_diffuseReduction), 1.0f);

	o_color = texColor * (ambientLight + diffuseLight);
}

vec4 CalculateColorBlend(sampler2D blend, sampler2D bg, sampler2D red, sampler2D green, sampler2D blue, vec2 texCoords, float repeat)
{
	vec2 tiledTexCoords = texCoords * repeat;
	
	vec4 blendColor = texture(blend, texCoords);

	float bgAmount = 1 - (blendColor.r + blendColor.g + blendColor.b);

	vec4 bgColor = texture(bg, tiledTexCoords) * bgAmount;
	vec4 rColor = texture(red, tiledTexCoords) * blendColor.r;
	vec4 gColor = texture(green, tiledTexCoords) * blendColor.g;
	vec4 bColor = texture(blue, tiledTexCoords) * blendColor.b;

	vec4 totalColor = bgColor + rColor + gColor + bColor;

	return totalColor;
}

vec3 AmbientLight(vec3 lightColor, float reductionFactor)
{
	vec3 ambientLight = lightColor * reductionFactor;
	return ambientLight;
}

vec3 DiffuseLight(vec3 toLightVector, vec3 normal, vec3 lightColor, float reductionFactor)
{
	float dotProduct = dot(normal, toLightVector);
	float brightness = max(dotProduct, 0.01f);
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