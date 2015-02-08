#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 uv;

uniform mat4 MVP; //ModelViewPerspective matrix

void main()
{
	uv = texCoord;		
	gl_Position =  MVP * vec4(position, 1.0);
}