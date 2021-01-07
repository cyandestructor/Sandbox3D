
#type vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec3 texCoords;

uniform mat4 u_viewProjection;

void main()
{
	texCoords = position.xyz;
	gl_Position = u_viewProjection * position;
	gl_Position = gl_Position.xyww;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 o_color;
	
in vec3 texCoords;

uniform float u_blendLevel;

uniform samplerCube u_texture;
uniform samplerCube u_texture2;

void main()
{
	vec4 color1 = texture(u_texture, texCoords);
	vec4 color2 = texture(u_texture2, texCoords);

	vec4 totalColor = mix(color1, color2, u_blendLevel);

	o_color = totalColor;
	//o_color = vec4(1.0,1.0,1.0,1.0);
}