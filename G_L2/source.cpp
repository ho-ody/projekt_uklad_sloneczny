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

void drawIt(Planet &p, double time, GLuint dxID, GLuint dyID) {
	p.VAO_.Bind();
	glDrawElements(GL_TRIANGLES, p.n_vertices, GL_UNSIGNED_INT, 0);
	p.VAO_.Unbind();
	p.update(time, dxID, dyID);
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
		cerr << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 800, 800); // viewport:  from x = 0, y = 0, to x = 800, y = 800

	// Utwórz obiekt Vertex Shader
	Shader shaderProgram("default.vert", "default.frag");

	GLuint dxID = glGetUniformLocation(shaderProgram.ID, "dx");
	GLuint dyID = glGetUniformLocation(shaderProgram.ID, "dy");
	
	// ========= //
	// 
	Planet p1(2, 0.5, 15, .5, .5, .5);
	Planet p2(1, 1.2, 23, .2, .7, .7);
	// ========= //

	float bg_r = 0., bg_g = 0., bg_b = 0.25;
	double time = 0.;
	//double sizeOfPictureScaller = 0.1;
	//glUniform1f(uniID, sizeOfPictureScaller);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //kontury
	glfwSwapInterval(1); //ograniczenie fps to synchronizacji vsync
	while (!glfwWindowShouldClose(window))
	{
		time += 0.01; //czas - u¿ywane w kolorze t³a, ruchu planet
		// logika koloru t³a
		bg_r = bg_g = cos(time/4.) / 26. ;
		bg_b = sin(time/4.) / 14. + .25;
		glClearColor(bg_r, bg_g, bg_b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// shader
		shaderProgram.Activate();
		// rysowanie trójk¹tów
		// ========= //
		drawIt(p1, time, dxID, dyID);
		drawIt(p2, time, dxID, dyID);
		// ========= //
		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window); //Delete window before ending the program
	glfwTerminate(); //Terminate GLFW before ending the program 
	return 0;
}