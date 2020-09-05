#type vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 color;
uniform mat4 u_viewProjection;
uniform mat4 u_transformation;
uniform vec4 u_color;

void main()
{
	gl_Position = u_viewProjection * u_transformation * position;
	color = u_color;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;
	
in vec4 color;

void main()
{
	o_color = color;
}