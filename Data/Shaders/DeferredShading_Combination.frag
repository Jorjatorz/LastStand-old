#version 430 core

layout (location = 0) out vec4 outColor; //layout(location = 0))


uniform sampler2D colorTex;
uniform sampler2D normalsTex;

in vec2 uv;

void main()
{
	vec3 n = texture(normalsTex, uv).xyz;
	vec3 l = vec3(1.0, 1.0, 0.5);
	float a = clamp(dot(n, l), 0.0, 1.0);
	outColor = texture(colorTex, uv) * a;
}