#include "ShaderClass.h"
#include <vector>

string getFileContents(const char* filename) {
	ifstream in(filename, ios::binary);
	if (in) {
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());

		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());

		in.close();
		return contents;
	}
	throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	string vertexCode = getFileContents(vertexFile);
	string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Po³¹cz istniej¹cy obiekt z napisan¹ wczeœniej implementacj¹ shadera
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Skompiluj gotowy kod
	glCompileShader(vertexShader);
	// errors
	compileErrors(vertexShader, "VERTEX  ", vertexCode);
	// Powtórz operacjê dla fragment shadera
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	// errors
	compileErrors(fragmentShader, "FRAGMENT", fragmentCode);
	// Utwórz program
	ID = glCreateProgram();
	// Pod³¹cz shadery pod program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	compileErrors(ID, "PROGRAM ", vertexCode + "\n" + fragmentCode);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	cerr << endl;
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type, string shaderCode) {

	char infoLog[1024];
	GLint hasCompiled = GL_FALSE;


	//glGetProgramInfoLog(shader, 1024, NULL, infoLog);
	//glGetShaderInfoLog(shader, 1024, NULL, infoLog);
	//glGetShaderInfoLog(shader, 1024, NULL, infoLog);

	if (type != "PROGRAM ") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		cerr << type << " SHADER --> STATUS KOMPILACJI: ";
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		cerr << type << " SHADER --> STATUS LINKOWANIA: ";
	}

	if (hasCompiled == GL_TRUE) {
		cerr << "OK\n";
	}
	else {
		cerr << "BAD\n";
		cerr << shaderCode << endl;
		cerr << infoLog << endl;
	}
}