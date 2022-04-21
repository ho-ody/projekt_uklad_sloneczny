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
	n_vertices = 5 * n_wierzcholkow;
	vertices = new GLfloat[n_vertices];
	n_indices = 2 * n_wierzcholkow;
	indices = new GLuint[n_indices];

	double kat = 2 * M_PI / n_wierzcholkow;
	int i_wierzcholka = 0;
	double x, y;
	//vertices
	for (int i = 0; i < n_wierzcholkow; i++) {
		orbit_generuj_koordynaty_wierzcholkow(size_x, size_y, kat, i_wierzcholka, &x, &y);
		vertices[0 + 5 * i] = x;
		vertices[1 + 5 * i] = y;
		vertices[2 + 5 * i] = color[0];
		vertices[3 + 5 * i] = color[1];
		vertices[4 + 5 * i] = color[2];
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
	VAO_.LinkVBO(VBO_, 0, 1);
	VAO_.Unbind();
}

void Orbit::update(double time, GLuint dxID, GLuint dyID) {
	double dx = center_x;
	double dy = center_y;

	center_x = 1. / speed * radius_x * sin(speed * time);
	center_y = 1. / speed * radius_y * cos(speed * time);

	dx -= center_x;
	dy -= center_y;

	glUniform1f(dxID, dx);
	glUniform1f(dyID, dy);
}
void Orbit::updateCenterByOtherPlanet(double time, GLuint dxID, GLuint dyID, double centerToFollow_x, double centerToFollow_y) {
	double dx = center_x;
	double dy = center_y;

	center_x = 1. / speed * radius_x * sin(speed * time);
	center_y = 1. / speed * radius_y * cos(speed * time);
	center_x += centerToFollow_x;
	center_y += centerToFollow_y;
	dx -= center_x;
	dy -= center_y;

	glUniform1f(dxID, dx);
	glUniform1f(dyID, dy);
}

Orbit::~Orbit() {
	delete[] vertices, indices;
	VAO_.Delete();
	VBO_.Delete();
	EBO_.Delete();
}
