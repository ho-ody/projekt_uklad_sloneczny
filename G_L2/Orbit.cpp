#include "Orbit.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <stdlib.h>
#include <iostream>


void orbit_generuj_koordynaty_wierzcholkow(double rx, double ry, double kat, int i_wierzcholka, double* x, double* y)
{
	double a = tan(i_wierzcholka * kat);
	*y = sqrt(ry * ry / (1 + a * a));
	*x = abs(a) * *y * rx / ry;
	//korekta w zale¿noœci od æwiartki uk³adu wspó³rzêdnych
	if (i_wierzcholka * kat < M_PI / 2.)              // - +
	{
		*x *= -1;
	}
	else if (i_wierzcholka * kat < M_PI)         // - -
	{
		*x *= -1;
		*y *= -1;
	}
	else if (i_wierzcholka * kat < 3. * M_PI / 2.)         // + -
	{
		*y *= -1;
	}
}
Orbit::Orbit(double rx, double ry, double center_x_in, double center_y_in) {
	//std zmienne
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	size_x = 0.1 * rx;
	size_y = 0.1 * ry;
	center_x = center_x_in;
	center_y = center_y_in;
	radius_x = 0;
	radius_y = 0;
	speed = 1.;
	//
	n_vertices = 11 * n_wierzcholkow;
	vertices = new GLfloat[n_vertices];
	n_indices = 2 * n_wierzcholkow;
	indices = new GLuint[n_indices];

	double kat = 2 * M_PI / n_wierzcholkow;
	int i_wierzcholka = 0;
	double x, y;
	//vertices
	for (int i = 0; i < n_wierzcholkow; i++) {
		orbit_generuj_koordynaty_wierzcholkow(size_x, size_y, kat, i_wierzcholka, &x, &y);
		vertices[0 + 11 * i] = x;
		vertices[1 + 11 * i] = 0.;
		vertices[2 + 11 * i] = y;
		i_wierzcholka++;
	}
	//indices
	for (int i = 0, j = 0; i < n_wierzcholkow; i++)
	{
		indices[j] = i;
		indices[j + 1] = i + 1;
		j += 2;
	}
	indices[n_wierzcholkow * 2 - 1] = 0; //fix ostatniego wierzcholka
	//VAO,VBO,EBO
	VAO_.Bind();
	VBO_ = VBO(vertices, sizeof(GLfloat) * n_vertices);
	EBO_ = EBO(indices, sizeof(GLuint) * n_indices);
	VAO_.LinkAttrib(VBO_, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);		//linkowanie konkretnych rzeczy z default.vert
	VAO_.LinkAttrib(VBO_, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO_.LinkAttrib(VBO_, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO_.LinkAttrib(VBO_, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO_.Unbind();
	VBO_.Unbind();
	EBO_.Unbind();

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
}

void Orbit::update(double time) {
	float multi = 10;
	position.x = radius_x * sin(speed * time) / multi;
	position.y = 0.;
	position.z = radius_y * cos(speed * time) / multi;

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
}
void Orbit::updateCenterByOtherPlanet(double time, double centerToFollow_x, double centerToFollow_y) {
	float multi = 10;
	position.x = radius_x * sin(speed * time) / multi;
	position.y = 0.;
	position.z = radius_y * cos(speed * time) / multi;

	position.x += centerToFollow_x;
	position.z += centerToFollow_y;

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

}

Orbit::~Orbit() {
	delete[] vertices, indices;
	VAO_.Delete();
	VBO_.Delete();
	EBO_.Delete();
}