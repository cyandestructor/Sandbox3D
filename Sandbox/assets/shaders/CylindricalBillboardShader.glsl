#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;

out float gl_ClipDistance[1];

out vec2 texCoords;
out vec3 normal;

uniform mat4 u_viewProjection;
uniform vec3 u_cameraRightWS;
uniform vec3 u_cameraUpWS;
uniform vec3 u_billboardPosition;
uniform vec3 u_billboardScale;

uniform vec4 u_clipPlane;

void main()
{
	vec3 worldPosition =
    u_billboardPosition
    + u_cameraRightWS * a_position.x * u_billboardScale.x
    + vec3(0.0f, 1.0f, 0.0f) * a_position.y * u_billboardScale.y;

	gl_Position = u_viewProjection * vec4(worldPosition, 1.0f);
	gl_ClipDistance[0] = dot(vec4(worldPosition, 1.0f), u_clipPlane);

	texCoords = a_texCoords;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 o_color;
	
in vec2 texCoords;

uniform float u_ambientReduction;
uniform vec4 u_lightColor;

uniform sampler2D u_diffuseTex;

vec3 AmbientLight(vec3 lightColor, float reductionFactor);

void main()
{
	vec4 ambientLight = vec4(AmbientLight(u_lightColor.xyz, u_ambientReduction), 1.0f);
	
	vec4 color = texture(u_diffuseTex, texCoords) * ambientLight;
	// temporal. change with an alpha texture
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