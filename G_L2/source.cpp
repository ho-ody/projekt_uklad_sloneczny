#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderClass.h"
#include "Planet.h"


int zad1(int size, GLfloat*& vertices, GLuint*& indices) {
	int n_verticles_to_draw = 2 * 3;
	vertices = new GLfloat[4 * 5];
	indices = new GLuint[n_verticles_to_draw];

	GLfloat Tvertices[] = {
		-0.5f,-0.5f,1.0f,0.0f,0.0f,
		+0.5f,-0.5f,0.0f,1.0f,0.0f,
		-0.5f,+0.5f,0.0f,0.0f,1.0f,
		+0.5f,+0.5f,1.0f,0.0f,0.0f,
	};
	GLuint Tindices[] = {
		0,1,2,
		1,2,3
	};
	for (int i = 0; i < 20; i++)
		vertices[i] = Tvertices[i];
	for (int i = 0; i < 6; i++)
		indices[i] = Tindices[i];
	return n_verticles_to_draw; //returns number of verticles to draw
}
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
void generuj_koordynaty_wierzcholkow(double r, int ilosc_wierzcholkow, double kat_alfa, int numer_wierzcholka, double* x, double* y)
{
	double old_x = *x, old_y = *y;
	double a = tan(numer_wierzcholka * kat_alfa);
	*y = sqrt(r * r / (1 + a * a));
	*x = abs(a) * *y;

	//std::cout << "nw * ka = " << numer_wierzcholka * kat_alfa << std::endl;
	//std::cout << "x = " << *x << std::endl;
	//std::cout << "y = " << *y << std::endl;

	if (numer_wierzcholka * kat_alfa < 1.5707)              // - +
	{
		*x *= -1;
	}
	else if (numer_wierzcholka * kat_alfa < 1.5709)         // - 0
	{
		*x *= -1;
		*y = 0.;
	}
	else if (numer_wierzcholka * kat_alfa < 3.1415)         // - -
	{
		*x *= -1;
		*y *= -1;
	}
	else if (numer_wierzcholka * kat_alfa < 3.1417)         // 0 -
	{
		*y *= -1;
		*x = 0.;
	}
	else if (numer_wierzcholka * kat_alfa < 4.7123)         // + -
	{
		*y *= -1;
	}
	else if (numer_wierzcholka * kat_alfa < 4.7125)         // + 0
	{
		*y = 0.;
	}
	else if (numer_wierzcholka * kat_alfa < 6.2831)         // + +
	{
	}
	else if (numer_wierzcholka * kat_alfa < 6.2833)         // 0 +
	{
		*x = 0.;
	}
	else
		std::cout << "\n\nerror2\n\n";                      //wykroczono poza zakres 2pi

	//std::cout << "x' = " << *x << std::endl;
	//std::cout << "y' = " << *y << std::endl << std::endl;
}
void generate(double r, int ilosc_wierzcholkow, double* kat_alfa, double* x, double* y, GLfloat*& wierzcholki, GLuint*& indices)
{
	*kat_alfa = 2 * M_PI / ilosc_wierzcholkow;
	int numer_wierzcholka = 0;
	*x = 0, * y = r;

	int temp_color = 0;

	float color_r = 0., color_g = 0., color_b = 0.;
	for (int i = 0; i < ilosc_wierzcholkow; i++)
	{
		int temp_color = rand() % 3;
		if ((i + temp_color) % 3 == 0)
		{
			color_r = 1.;
			color_g = 0.;
			color_b = 0.;
		}
		if ((i + temp_color) % 3 == 1)
		{
			color_r = 0.;
			color_g = 0.;
			color_b = 1.;
		}
		if ((i + temp_color) % 3 == 2)
		{
			color_r = 0.;
			color_g = 1.;
			color_b = 0.;
		}
		temp_color--;
		if (i != 0)
		{
			generuj_koordynaty_wierzcholkow(r, ilosc_wierzcholkow, *kat_alfa, numer_wierzcholka, x, y);
		}
		wierzcholki[0 + 5 * i] = *x;
		wierzcholki[1 + 5 * i] = *y;
		wierzcholki[2 + 5 * i] = color_r;
		wierzcholki[3 + 5 * i] = color_g;
		wierzcholki[4 + 5 * i] = color_b;
		numer_wierzcholka++;
	}
	/*
	wierzcholki[6] = 1.0f;
	wierzcholki[7] = 1.0f;

	wierzcholki[14] = 1.0f;
	wierzcholki[15] = 0.0f;

	wierzcholki[22] = 0.0f;
	wierzcholki[23] = 0.0f;

	wierzcholki[30] = 0.0f;
	wierzcholki[31] = 1.0f;
	*/

	for (int i = 0, j = 0, k = 0; i < 3 * (ilosc_wierzcholkow - 2); i++)
	{
		if (i % 3 == 0) // pierwsza koordynata (zawsze równa 0)
		{
			indices[i] = 0;
			if (i % 6 == 3)
				j += 2;
			if (i % 6 == 0)
				k += 2;
		}
		if (i % 3 == 1)
			indices[i] = 1 + j;
		if (i % 3 == 2)
			indices[i] = k;
	}
}

int circle(int size, GLfloat*& vertices, GLuint*& indices) {

	int ilosc_wierzcholkow = 10;
	vertices = new  GLfloat[8 * ilosc_wierzcholkow];
	indices = new GLuint[3 * (ilosc_wierzcholkow - 2)];

	double r = 1.5;
	double kat_alfa = 2 * M_PI / ilosc_wierzcholkow;
	double x = 0., y = r;

	generate(r, ilosc_wierzcholkow, &kat_alfa, &x, &y, vertices, indices);

	int n_verticles_to_draw = ilosc_wierzcholkow * 3;

	return n_verticles_to_draw; //returns number of verticles to draw
}

void drawIt(int n_verticles_to_draw, int mode = 0) {
	if (mode == 0) { //wszystko wypelnione
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, n_verticles_to_draw, GL_UNSIGNED_INT, 0);
	}
	else if (mode == 1) { //polowa wypelniona, polowa linie
		for (int i = 0; i < n_verticles_to_draw; i += 6) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * sizeof(float)));
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)((i + 3) * sizeof(float)));
		}
	}
}
void drawIt(Planet &p) {
	p.VAO_.Bind();
	glDrawElements(GL_TRIANGLES, p.n_vertices, GL_UNSIGNED_INT, 0);
	p.VAO_.Unbind();
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

GLfloat* vertices = NULL;
GLuint* indices = NULL;
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
		cerr << "Failed to create GLFW window" << endl;
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
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	//
	int size = 6;
	int n_verticles_to_draw = 4;
	n_verticles_to_draw = circle(size, vertices, indices);


	VBO VBO1(vertices, sizeof(GLfloat) * (size + 1) * (size + 1) * 5);
	EBO EBO1(indices, sizeof(GLuint) * n_verticles_to_draw);


	

	VAO1.LinkVBO(VBO1, 0, 1);
	VAO1.Unbind();

	float a = 0.383, b = 0.336, c = 0.449;
	glfwSwapInterval(1); //ograniczenie fps to synchronizacji vsync
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //kontury
	int counter = 0;
	float xx = 0;
	VBO1.Bind(); //dynamiczna zmiana koloru


	VAO VAO2;
	VBO VBO2(vertices, sizeof(GLfloat) * (size + 1) * (size + 1) * 5);
	EBO EBO2(indices, sizeof(GLuint) * n_verticles_to_draw);



	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint dxID = glGetUniformLocation(shaderProgram.ID, "dx");
	GLuint dyID = glGetUniformLocation(shaderProgram.ID, "dy");

	double x = 0, y = 0, dx = 0, dy = 0;
	
	Planet p1(0.5, .5, .5, .5);

	while (!glfwWindowShouldClose(window))
	{
		VBO1.dynamicUpdate(vertices, sizeof(GLfloat) * (size + 1) * (size + 1) * 5);
		// Ustaw kolor t³a (RGBA, z przedzia³u <0, 1>)
		xx += 0.02;
		a = sin(xx) / 2 + 0.5;
		b = sin(-xx) / 2 + 0.5;
		c = sin(xx + 1.57) / 2 + 0.5;


		double mult = 0.5; //speed
		double scaller = 10.; //radius

		dx = x;
		dy = y;
		x = 1 / mult * scaller * 1.2 * sin(mult * xx);
		y = 1 / mult * scaller * cos(mult * xx);
		dx -= x;
		dy -= y;

		//glUniform1f(dxID, dx);
		//glUniform1f(dyID, dy);

		float size = 0.1;

		/*
		for (int i = 0; i < (size+1)*(size+1); i++)
		{
			vertices[5*i] += dx;
			vertices[5*i+1] += dy;
		}
		*/


		glClearColor(a, b, c, 1.0f);
		// color update
		colorUpdate(b, c, a, size, vertices);
		//colorUpdateV2(a, b, c, size, vertices);
		// Wyczyœæ buffor I nadaj mu kolor
		glClear(GL_COLOR_BUFFER_BIT);
		// Wybierz, który shader bêdzie u¿ywany
		shaderProgram.Activate();




		glUniform1f(uniID, size);

		VAO1.Bind();
		// Narysuj trójk¹ty
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		drawIt(n_verticles_to_draw,0);
		drawIt(p1);

		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	delete[] vertices;
	delete[] indices;

	return 0;
}