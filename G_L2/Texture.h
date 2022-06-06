#pragma once
#include <glad/glad.h>
#include "ShaderClass.h"
#include "stb/stb_image.h"

class Texture {

public:
	GLuint ID;
	GLenum type;

	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	Texture();

	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	void Bind();
	void Unbind();
	void Delete();
};