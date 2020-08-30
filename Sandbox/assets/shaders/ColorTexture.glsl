// 2 in 1 Shader for texture and flat color

#type vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoords;
layout(location = 3) in float a_texIndex;
layout(location = 4) in float a_tileFactor;

out vec4 v_color;
out vec2 v_texCoords;
out float v_texIndex;
out float v_tileFactor;

uniform mat4 u_viewProjection;
//uniform mat4 u_transformation;

void main()
{
	gl_Position = u_viewProjection * a_position;
	v_color = a_color;
	v_texCoords = a_texCoords;
	v_texIndex = a_texIndex;
	v_tileFactor = a_tileFactor;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 out_color;
	
in vec4 v_color;
in vec2 v_texCoords;
in float v_texIndex;
in float v_tileFactor;

uniform sampler2D u_textures[32];

void main()
{
	out_color = texture(u_textures[int(v_texIndex)], v_texCoords * v_tileFactor) * v_color;
	//out_color = v_color;
}