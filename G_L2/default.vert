// vertexShaderSource 
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
out vec3 Color;
uniform float scale;
uniform float dx;
uniform float dy;
void main()
{
Color = color;
gl_Position = vec4(scale * position.x + dx, scale * position.y + dy, 0.0, 1.0);
}