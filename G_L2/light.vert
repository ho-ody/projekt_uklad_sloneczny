#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexture;
layout (location = 3) in vec3 inNormal;

out vec2 myTexture;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * model * vec4(aPos, 1.0f);

	myTexture = inTexture;
}