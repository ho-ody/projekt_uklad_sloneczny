// vertexShaderSource 
#version 330 core
layout (location = 0) in vec3 position;

out vec3 Color;
uniform mat4 camMatrix;
uniform mat4 model;
uniform vec3 color;
void main()
{
	Color = color;
	gl_Position = camMatrix * model * vec4(position, 1.0);
}