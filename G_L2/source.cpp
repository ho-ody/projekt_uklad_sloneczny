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

void drawIt(Planet &obiekt, double time, GLuint dxID, GLuint dyID) {
	obiekt.update(time, dxID, dyID);
	obiekt.VAO_.Bind();
	glDrawElements(GL_TRIANGLES, obiekt.n_vertices, GL_UNSIGNED_INT, 0);
	obiekt.VAO_.Unbind();
}
void drawIt(Planet& obiekt, double time, GLuint dxID, GLuint dyID, Planet& obiektWokolKtoregoKrazy) {
	obiekt.updateCenterByOtherPlanet(time, dxID, dyID, obiektWokolKtoregoKrazy);
	obiekt.VAO_.Bind();
	glDrawElements(GL_TRIANGLES, obiekt.n_vertices, GL_UNSIGNED_INT, 0);
	obiekt.VAO_.Unbind();
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
	// kolejnosc argumentow:
	//	 rozmiar_planety								
	//   predkosc_ruchu_planety						
	//   promien_okregu_x, promien_okregu_y			  (dla okregu takie same, dla elips ró¿ne)
	//   color_r, color_g, color_b					  (kolejne wartosci koloru z przed. [0.,1.]
	//   srodek_okregu_ruchu_x, srodek_okregu_ruchu_y (koordynaty srodka, standardowo rowne 0, mozna pominac przy wpisywaniu)
	Planet p1(2, 2, 15, 15, .5, .5, .5);
	Planet p2(1, 2.4, 23, 23, .2, .7, .7);
	Planet p3(1.2, 2.4, 15, 80, .3, .6, .5);
	Planet k1(0.4, 1.2, 20, 20, .9, .2, .2, p3.center_x, p3.center_y);
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
		drawIt(p3, time, dxID, dyID);
		drawIt(k1, time, dxID, dyID, p3);
		// ========= //
		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window); //Delete window before ending the program
	glfwTerminate(); //Terminate GLFW before ending the program 
	return 0;
}