
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

uniform samplerCube u_texture;

void main()
{
	o_color = texture(u_texture, texCoords);
	//o_color = vec4(1.0,1.0,1.0,1.0);
}