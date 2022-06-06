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
#include "Orbit.h"
#include "Camera.h"

void drawIt(Planet &obiekt, double time, GLuint dxID, GLuint dyID, GLuint shaderProgramID) {
	obiekt.update(time, dxID, dyID);
	obiekt.VAO_.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(obiekt.model));
	glDrawElements(GL_TRIANGLES, obiekt.n_vertices, GL_UNSIGNED_INT, 0);
	obiekt.VAO_.Unbind();
}
void drawIt(Planet& obiekt, double time, GLuint dxID, GLuint dyID, Planet& obiektWokolKtoregoKrazy) {
	obiekt.updateCenterByOtherPlanet(time, dxID, dyID, obiektWokolKtoregoKrazy.center_x, obiektWokolKtoregoKrazy.center_y);
	obiekt.VAO_.Bind();
	glDrawElements(GL_TRIANGLES, obiekt.n_vertices, GL_UNSIGNED_INT, 0);
	obiekt.VAO_.Unbind();
}
void drawIt(Orbit& obiekt, double time, GLuint dxID, GLuint dyID) {
	obiekt.update(time, dxID, dyID);
	obiekt.VAO_.Bind();
	glDrawElements(GL_LINES, obiekt.n_vertices, GL_UNSIGNED_INT, 0);
	obiekt.VAO_.Unbind();
}
void drawIt(Orbit& obiekt, double time, GLuint dxID, GLuint dyID, Planet& obiektWokolKtoregoKrazy) {
	obiekt.updateCenterByOtherPlanet(time, dxID, dyID, obiektWokolKtoregoKrazy.center_x, obiektWokolKtoregoKrazy.center_y);
	obiekt.VAO_.Bind();
	glDrawElements(GL_LINES, obiekt.n_vertices, GL_UNSIGNED_INT, 0);
	obiekt.VAO_.Unbind();
}
/*
	TO-DO:

	[X] 3d		- zmiana kó³ na sfery
	[X] kamera	- ruch kamer¹
	[ ] oœwietlenie i cieniowanie
	[ ] tekstury
*/
//CAMERA, RUCH KAMERY
float deltaTime = 0., lastFrame = 0.;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
Camera* currentCamera;
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { // uruchamiane po zmianie rozmiaru okienka
	glViewport(0, 0, width, height);
}
ostream& operator<<(ostream& stream, const glm::vec3& v)
{
	stream << "(" << v.x << "," << v.y << "," << v.z << ")";
	return stream;
}
int width = 800, height = 800;
int main() {
	srand(time(NULL));
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "glhf", NULL, NULL);
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
	glViewport(0, 0, width, height); // viewport
	// Input + Camera
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// Utwórz obiekt Vertex Shader
	Shader shaderProgram("color_uniform.vert", "default.frag");
	//Shader shaderProgram("color_uniform.vert", "lightning.frag");

	GLuint dxID = glGetUniformLocation(shaderProgram.ID, "dx");
	GLuint dyID = glGetUniformLocation(shaderProgram.ID, "dy");
	
	// ========= //
	// kolejnosc argumentow:
	//	 rozmiar_planety								
	//   predkosc_ruchu_planety						
	//   promien_okregu_x, promien_okregu_y			  (dla okregu takie same, dla elips ró¿ne)
	//   color_r, color_g, color_b					  (kolejne wartosci koloru z przed. [0.,1.]
	//   srodek_okregu_ruchu_x, srodek_okregu_ruchu_y (koordynaty srodka, standardowo rowne 0, mozna pominac przy wpisywaniu)

	Planet p1(2, 2, 40, 40, .5, .5, .5);
	Orbit o1(40, 40);

	Planet p2(1, 2.4, 23, 23, .2, .7, .7);
	Orbit o2(23, 23);

	Planet p3(1.2, 2.4, 15, 80, .3, .6, .5);
	Orbit o3(15, 80);
	Planet k1(0.4, 1.2, 25, 15, .9, .2, .2, p3.center_x, p3.center_y);
	Orbit o4(25, 15, p3.center_x, p3.center_y);

	Planet Mercury(0.069849839, 2.306994196, 20.6064265, 17.91523936, 26, 26, 26);
	Orbit mercuryOrbit(Mercury.radius_x, Mercury.radius_y);
	Planet Venus(0.11001818, 1.972026594, 23.88428091, 23.73729699, 230, 230, 230);
	Orbit venusOrbit(Venus.radius_x,Venus.radius_y);
	Planet Earth(0.112942463, 1.819645875, 26.68401649, 26.38816044, 47, 106, 105);
	Orbit earthOrbit(Earth.radius_x, Earth.radius_y);
	Planet Mars(0.082492424, 1.636391694, 31.45597276, 29.4818427, 153, 61, 0);
	Orbit marsOrbit(Mars.radius_x, Mars.radius_y);
	Planet Jupiter(0.378132252, 1.206464071, 46.7423658, 45.24557103, 176, 127, 53);
	Orbit jupiterOrbit(Jupiter.radius_x, Jupiter.radius_y);
	Planet Saturn(0.347182949, 1.038160767, 57.362621, 55.26047248, 176, 143, 54);
	Orbit saturnOrbit(Saturn.radius_x, Saturn.radius_y);
	Planet Ur_Anus(0.226092901, 0.869226987, 72.11247852, 70.05098327, 85, 128, 170);
	Orbit uranusOrbit(Ur_Anus.radius_x, Ur_Anus.radius_y);
	Planet Neptune(0.222548871, 0.774596669, 82.85278982, 82.24130783, 54, 104, 150);
	Orbit neptuneOrbit(Neptune.radius_x, Neptune.radius_y);

	Planet Sun(1, 179830496, 1, 0, 239, 142, 56);

	Planet Ganymede(0.072594766, 0.5, 5.114045609, 5.114045609, 179, 177, 176, Jupiter.center_x, Jupiter.center_y);
	Orbit ganymedeOrbit(5.114045609, 5.114045609, Jupiter.center_x, Jupiter.center_y);
	Planet Titan(0.0717635, 1, 5.313292846, 5.313292846, 224, 194, 133, Saturn.center_x, Saturn.center_y);
	Orbit titanOrbit(5.313292846, 5.313292846, Saturn.center_x, Saturn.center_y);
	Planet Callisto(0.06942622, 1, 6.171005793, 6.171005793, 160, 189, 183, Jupiter.center_x, Jupiter.center_y);
	Orbit callistoOrbit(6.171005793, 6.171005793, Jupiter.center_x, Jupiter.center_y);
	Planet Io(0.06035727, 1, 3.74948141, 3.74948141, 204, 153, 0, Jupiter.center_x, Jupiter.center_y);
	Orbit ioOrbit(3.74948141, 3.74948141, Jupiter.center_x, Jupiter.center_y);
	Planet Moon(0.058949131, 1, 3.701436014, 3.567086838, 254, 252, 215, Earth.center_x, Earth.center_y);
	Orbit moonOrbit(3.701436014, 3.567086838, Earth.center_x, Earth.center_y);

	// ========= // camera
	Camera camera(width, height, glm::vec3(-2.2f, 2.2f, 1.0f), glm::vec3(0.6f, -0.6f, -0.5f));
	currentCamera = &camera;
	// ========= // ustawienia + kolor t³a
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
		// input + ruch kamery
		camera.Inputs(window); //obs³uga wejœcia do kamery
		camera.updateMatrix(camera.fov, 0.5f, 50.0f);

		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");

		//time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// rysowanie //
		// ========= //
		// ORBITY
		drawIt(Mercury, time, dxID, dyID, shaderProgram.ID);
		drawIt(Earth, time, dxID, dyID, shaderProgram.ID);
		drawIt(Sun, time, dxID, dyID, shaderProgram.ID);
		/*
		drawIt(mercuryOrbit, time, dxID, dyID);
		drawIt(venusOrbit, time, dxID, dyID);
		drawIt(earthOrbit, time, dxID, dyID);
		drawIt(marsOrbit, time, dxID, dyID);
		drawIt(jupiterOrbit, time, dxID, dyID);
		drawIt(saturnOrbit, time, dxID, dyID);
		drawIt(uranusOrbit, time, dxID, dyID);
		drawIt(neptuneOrbit, time, dxID, dyID);
		
		// PLANETY
		drawIt(Mercury, time, dxID, dyID);
		drawIt(Venus, time, dxID, dyID);
		drawIt(Earth, time, dxID, dyID);
		drawIt(Mars, time, dxID, dyID);
		drawIt(Jupiter, time, dxID, dyID);
		drawIt(Saturn, time, dxID, dyID);
		drawIt(Ur_Anus, time, dxID, dyID);
		drawIt(Neptune, time, dxID, dyID);
		
		drawIt(Sun, time, dxID, dyID);

		// KSIÊ¯YCE
		drawIt(Ganymede, time, dxID, dyID, Jupiter);
		drawIt(ganymedeOrbit, time, dxID, dyID, Jupiter);
		drawIt(Titan, time, dxID, dyID, Saturn);
		drawIt(titanOrbit, time, dxID, dyID, Saturn);
		drawIt(Callisto, time, dxID, dyID, Jupiter);
		drawIt(callistoOrbit, time, dxID, dyID, Jupiter);
		drawIt(Io, time, dxID, dyID, Jupiter);
		drawIt(ioOrbit, time, dxID, dyID, Jupiter);
		drawIt(Moon, time, dxID, dyID, Earth);
		drawIt(moonOrbit, time, dxID, dyID, Earth);
		*/
		// ========= //
		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window); //Delete window before ending the program
	glfwTerminate(); //Terminate GLFW before ending the program 
	return 0;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	currentCamera->fov -= (float)yoffset;
	if (currentCamera->fov < 1.0f)
		currentCamera->fov = 1.0f;
	if (currentCamera->fov > 90.0f)
		currentCamera->fov = 90.0f;
}