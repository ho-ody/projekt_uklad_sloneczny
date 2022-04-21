#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"in vec2 position;\n"
"in vec3 color;\n"
"out vec3 Color;\n"
"void main()\n"
"{\n"
" Color = color;\n"
" gl_Position = vec4(position, 0.0, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 Color;\n"
"out vec4 outColor;\n"
"void main()\n"
"{\n"
" outColor = vec4(Color, 1.0);\n"
"}\n\0";

int zad4(int size, GLfloat*& vertices, GLuint*& indices) {
	int n_verticles_to_draw = 3 * size * size;
	vertices = new GLfloat[(size + 1) * (size + 1) * 5];
	indices = new GLuint[n_verticles_to_draw];

	GLfloat x, y, z = 0.;
	int iterator = 0;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++, iterator += 5) {
			x = (GLfloat)j * 2. / size - 1.;
			y = (GLfloat)i * 2. / size - 1.;
			vertices[iterator + 0] = x; //pos  x
			vertices[iterator + 1] = y; //pos  y
			vertices[iterator + 2] = 0.f; //rgb  r
			vertices[iterator + 3] = 1.f; //rgb  g
			vertices[iterator + 4] = 0.f; //rgb  b
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

void colorUpdate(float r, float g, float b, int size, GLfloat*& vertices) {
	int iterator = 0;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++, iterator += 5) {
			vertices[iterator + 2] = r; //rgb  r
			vertices[iterator + 3] = g; //rgb  g
			vertices[iterator + 4] = b; //rgb  b
		}
	}
}
void colorUpdateV2(float r, float g, float b, int size, GLfloat*& vertices) {
	int iterator = 0;
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++, iterator += 5) {
			if (i % 2 == 0) {
				vertices[iterator + 2] = g; //rgb  r
				vertices[iterator + 3] = b; //rgb  g
				vertices[iterator + 4] = r; //rgb  b
			}
			else {
				vertices[iterator + 2] = b; //rgb  r
				vertices[iterator + 3] = r; //rgb  g
				vertices[iterator + 4] = g; //rgb  b
			}
		}
	}
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
	int size = 7;
	GLfloat* vertices = NULL;
	GLuint* indices = NULL;
	int n_verticles_to_draw = 6;
	n_verticles_to_draw = zad4(size, vertices, indices);
	//
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (size + 1) * (size + 1) * 5, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size * size * 3, indices, GL_STATIC_DRAW);
	// Skonfiguruj format buffora, typ danych i d³ugoœæ
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	// Uruchom buffor
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float a = 0.383, b = 0.336, c = 0.449;
	glfwSwapInterval(1); //ograniczenie fps to synchronizacji vsync
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //kontury
	int counter = 0;
	float xx = 0;
	while (!glfwWindowShouldClose(window))
	{
		// Ustaw typ VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// za³aduj przygotowane wierzcho³ki
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (size + 1) * (size + 1) * 5, vertices, GL_STATIC_DRAW);
		// Ustaw kolor t³a (RGBA, z przedzia³u <0, 1>)
		xx += 0.02;
		a = sin(xx) / 2 + 0.5;
		b = sin(-xx) / 2 + 0.5;
		c = sin(xx + 1.57) / 2 + 0.5;
		glClearColor(a, b, c, 1.0f);
		// color update
		colorUpdate(b, c, a, size, vertices);
		//colorUpdateV2(a, b, c, size, vertices);
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
	delete[] vertices;
	delete[] indices;

	return 0;
}