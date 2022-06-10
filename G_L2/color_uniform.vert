// vertexShaderSource 
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexture;
layout (location = 3) in vec3 inNormal;

out vec3 Color;
out vec2 myTexture;
out vec3 Normal;
out vec3 currPosition;

uniform mat4 camMatrix;
uniform mat4 model;
void main()
{
	currPosition = vec3(model * vec4(position, 1.0f));
	gl_Position = camMatrix * vec4(currPosition, 1.0);

	myTexture = inTexture;
	Color = inColor;
	Normal = inNormal;
}