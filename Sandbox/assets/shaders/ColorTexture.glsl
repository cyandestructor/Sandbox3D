// 2 in 1 Shader for texture and flat color

#type vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoords;

out vec4 v_color;
out vec2 v_texCoords;

uniform mat4 u_viewProjection;
//uniform mat4 u_transformation;

void main()
{
	gl_Position = u_viewProjection * a_position;
	v_color = a_color;
	v_texCoords = a_texCoords;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 out_color;
	
in vec4 v_color;
in vec2 v_texCoords;

uniform sampler2D u_texture;
//uniform vec4 u_color;
uniform float u_tileFactor;

void main()
{
	//out_color = texture(u_texture, v_texCoords * u_tileFactor) * u_color;
	out_color = v_color;
}