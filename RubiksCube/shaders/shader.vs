#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec4 myColor;

uniform vec3 sideNotToRender;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 camera;

void main()
{
	myColor = vec4(color, 1.0f);
	if (abs(sideNotToRender.x - 0) > 0.01f && abs(sideNotToRender.x - position.x) < 0.00001f) myColor = vec4(color, 0.0f);
	if (abs(sideNotToRender.y - 0) > 0.01f && abs(sideNotToRender.y - position.y) < 0.00001f) myColor = vec4(color, 0.0f);
	if (abs(sideNotToRender.z - 0) > 0.01f && abs(sideNotToRender.z - position.z) < 0.00001f) myColor = vec4(color, 0.0f);
    gl_Position = projection * camera * model * vec4(position.x, position.y, position.z, 1.0);
}