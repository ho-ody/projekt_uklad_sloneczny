#pragma once
#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <cerrno>
using namespace std;

string getFileContents(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();

private:
	void compileErrors(unsigned int shader, const char* type, string vert);
};