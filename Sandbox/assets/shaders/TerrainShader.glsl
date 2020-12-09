// Shader to show a simple texture

#type vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoords;

out vec2 texCoords;

uniform mat4 u_viewProjection;
uniform mat4 u_transformation;

void main()
{
	gl_Position = u_viewProjection * u_transformation * a_position;
	texCoords = a_texCoords;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 o_color;
	
in vec2 texCoords;

uniform float u_repeatFactor;

uniform sampler2D u_diffuseTex;

void main()
{
	o_color = texture(u_diffuseTex, texCoords * u_repeatFactor);
}