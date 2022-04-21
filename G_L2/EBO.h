#pragma once
#include <glad/glad.h>

class EBO {
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);
	EBO() {};

	void Bind();
	void Unbind();
	void Delete();
};
