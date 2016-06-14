#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 myColor;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 camera;

void main()
{
	myColor = color;
    gl_Position = projection * camera * model * vec4(position.x, position.y, position.z, 1.0);
}