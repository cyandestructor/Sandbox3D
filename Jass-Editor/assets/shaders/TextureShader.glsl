// Shader to show a simple texture

#type vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 o_texCoords;

uniform mat4 u_viewProjection;
uniform mat4 u_transformation;

void main()
{
	gl_Position = u_viewProjection * u_transformation * position;
	o_texCoords = texCoords;
}

#type pixel
#version 330 core
			
layout(location = 0) out vec4 o_color;
	
in vec2 o_texCoords;

uniform sampler2D u_texture;

void main()
{
	o_color = texture(u_texture, o_texCoords);
}