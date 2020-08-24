// 2 in 1 Shader for texture and flat color

#type vertex
#version 330 core

layout(location = 0) in vec4 in_position;
layout(location = 1) in vec2 in_texCoords;

out vec2 v_texCoords;

uniform mat4 u_viewProjection;
uniform mat4 u_transformation;

void main()
{
	gl_Position = u_viewProjection * u_transformation * in_position;
	v_texCoords = in_texCoords;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 out_color;
	
in vec2 v_texCoords;

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_tileFactor;

void main()
{
	out_color = texture(u_texture, v_texCoords * u_tileFactor) * u_color;
}