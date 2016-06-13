#version 410 core

layout(location = 1) in vec3 vertexColor;
in vec3 myColor;

out vec4 color;

void main()
{
	color = vec4(myColor, 1.0f);
}