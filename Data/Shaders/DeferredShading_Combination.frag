#version 430 core

layout (location = 0) out vec4 outColor; //layout(location = 0))


uniform sampler2D colorTex;
in vec2 uv;

void main()
{
	outColor = texture(colorTex, uv);
}