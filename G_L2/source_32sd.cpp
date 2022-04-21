#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.835f, 0.835f, 0.835f, 1.0f);\n"
"}\n\0";

int zad1(int size, GLfloat*& vertices, GLuint*& indices) {
	int n_verticles_to_draw = size * 3 * ceil(static_cast<float>(size) / 2.);
	vertices = new GLfloat[(size + 1) * (size + 1) * 3];
	indices = new GLuint[n_verticles_to_draw];

	GLfloat x, y, z = 0.;
	int iterator = 0;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++, iterator += 3) {
			x = (GLfloat)j * 2. / size - 1.;
			y = (GLfloat)i * 2. / size - 1.;
			z = 0.;
			vertices[iterator + 0] = x;
			vertices[iterator + 1] = y;
			vertices[iterator + 2] = z;
		}
	}
	iterator = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j % 2 == 0) {
				indices[iterator + 0] = i * (size + 1) + j;
				indices[iterator + 1] = i * (size + 1) + j + 1;
				indices[iterator + 2] = i * (size + 1) + j + size + 2;
				iterator += 3;
			}
		}
	}
	return n_verticles_to_draw;
}
int zad2(int size, GLfloat*& vertices, GLuint*& indices) {
	int n_verticles_to_draw = 3 * size * size;
	vertices = new GLfloat[(size + 1) * (size + 1) * 3];
	indices = new GLuint[n_verticles_to_draw];

	GLfloat x, y, z = 0.;
	int iterator = 0;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++, iterator += 3) {
			x = (GLfloat) j * 2./size - 1.;
			y = (GLfloat) i * 2./size - 1.;
			z = 0.;
			vertices[iterator + 0] = x;
			vertices[iterator + 1] = y;
			vertices[iterator + 2] = z;
		}
	}
	iterator = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++, iterator += 3) {
			indices[iterator + 0] = i * (size + 1) + j;
			indices[iterator + 1] = i * (size + 1) + j + 1;
			indices[iterator + 2] = i * (size + 1) + j + size + 2;
		}
	}
	/*
	cerr << "\n\nvertic:\n";
	for (int i = 0; i < size * size*3; i++) {
		cerr << vertices[i] << ",";
		if (i % 3 == 2)
			cerr << endl;
	}
	cerr << "\n\nindi:\n";
	for (int i = 0; i < size * size * 3; i++) {
		cerr << indices[i] << ",";
		if (i % 3 == 2)
			cerr << endl;
	}
	*/
	return n_verticles_to_draw; //returns number of verticles to draw
}
int zad3(int size, GLfloat*& vertices, GLuint*& indices) {
	int n_verticles_to_draw = 3 * size * ceil(static_cast<float>(size) / 2.);
	vertices = new GLfloat[(size + 1) * (size + 1) * 3];
	indices = new GLuint[n_verticles_to_draw];

	GLfloat x, y, z = 0.;
	int iterator = 0;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++, iterator += 3) {
			x = (GLfloat)j * 2. / size - 1.;
			y = (GLfloat)i * 2. / size - 1.;
			z = 0.;
			vertices[iterator + 0] = x;
			vertices[iterator + 1] = y;
			vertices[iterator + 2] = z;
		}
	}
	iterator = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((j % 2 == 0 && i % 2 == 1) || (j % 2 == 1 && i % 2 == 0)) {
				indices[iterator + 0] = i * (size + 1) + j;
				indices[iterator + 1] = i * (size + 1) + j + 1;
				indices[iterator + 2] = i * (size + 1) + j + size + 2;
				iterator += 3;
			}
		}
	}
	return iterator; //returns number of verticles to draw
}
int zad4(int size, GLfloat*& vertices, GLuint*& indices) {
	int n_verticles_to_draw = 3 * size * size;
	vertices = new GLfloat[(size + 1) * (size + 1) * 3];
	indices = new GLuint[n_verticles_to_draw];

	GLfloat x, y, z = 0.;
	int iterator = 0;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++, iterator += 3) {
			x = (GLfloat)j * 2. / size - 1.;
			y = (GLfloat)i * 2. / size - 1.;
			z = 0.;
			vertices[iterator + 0] = x;
			vertices[iterator + 1] = y;
			vertices[iterator + 2] = z;
		}
	}
	iterator = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((j % 2 == 0 && i % 2 == 1) || (j % 2 == 1 && i % 2 == 0)) {
				indices[iterator + 0] = i * (size + 1) + j;
				indices[iterator + 1] = i * (size + 1) + j + 1;
				indices[iterator + 2] = i * (size + 1) + j + size + 2;

				indices[iterator + 3] = i * (size + 1) + j;
				indices[iterator + 4] = i * (size + 1) + j + size + 1;
				indices[iterator + 5] = i * (size + 1) + j + size + 2;
				iterator += 6;
			}
		}
	}
	return iterator; //returns number of verticles to draw
}

int main() {
	srand(time(NULL));
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "lab4", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" <<
			std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);


	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Utwórz obiekt Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Po³¹cz istniej¹cy obiekt z napisan¹ wczeœniej implementacj¹ shadera
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Skompiluj gotowy kod
	glCompileShader(vertexShader);
	// Powtórz operacjê dla fragment shadera
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Utwórz program
	GLuint shaderProgram = glCreateProgram();
	// Pod³¹cz shadery pod program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Usuñ niepotrzebne shadery


	//zad.2
	int size = 11;
	GLfloat* vertices = NULL;
	GLuint* indices = NULL;
	int n_verticles_to_draw = 12;
	//n_verticles_to_draw = zad2(size, vertices, indices);
	//n_verticles_to_draw = zad1(size, vertices, indices);
	//n_verticles_to_draw = zad3(size, vertices, indices);
	n_verticles_to_draw = zad4(size, vertices, indices);
	//n_verticles_to_draw--;
	GLuint VAO, VBO, EBO;
	// Utwórz obiekty VBO i VAO, ka¿dy posiada jeden obiekt
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Po³¹cz wierzcho³ki z bufforem wierzcho³ków
	glBindVertexArray(VAO);
	// Ustaw typ VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// za³aduj przygotowane wierzcho³ki
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*(size+1)*(size+1)*3, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size * size * 3, indices, GL_STATIC_DRAW);
	// Skonfiguruj format buffora, typ danych i d³ugoœæ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Uruchom buffor
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	float a = 0.383, b = 0.336, c = 0.449;
	int lewoprawo = 0;
	glfwSwapInterval(1); //ograniczenie fps to synchronizacji vsync
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //kontury
	while (!glfwWindowShouldClose(window))
	{
		// Ustaw kolor t³a (RGBA, z przedzia³u <0, 1>)
		switch (lewoprawo) {
		case 0:
			a += 0.01;
			if (a > 1)
				lewoprawo++;
			break;
		case 1:
			a -= 0.01;
			if (a < 0.5)
				lewoprawo++;
			break;
		case 2:
			b += 0.01;
			if (b > 1)
				lewoprawo++;
			break;
		case 3:
			b -= 0.01;
			if (b < 0.5)
				lewoprawo++;
			break;
		case 4:
			c += 0.01;
			if (c > 1)
				lewoprawo++;
			break;
		case 5:
			c -= 0.01;
			if (c < 0.5)
				lewoprawo = 0;
			break;
		}
		glClearColor(a, b, c, 1.0f);
		// Wyczyœæ buffor I nadaj mu kolor
		glClear(GL_COLOR_BUFFER_BIT);
		// Wybierz, który shader bêdzie u¿ywany
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Narysuj trójk¹t
		glDrawElements(GL_TRIANGLES, n_verticles_to_draw, GL_UNSIGNED_INT, 0);
		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	return 0;
}