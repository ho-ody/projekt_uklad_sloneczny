#include "Planet.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <stdlib.h>
#include <iostream>


void generuj_koordynaty_wierzcholkow(double r, double kat, int i_wierzcholka, double* x, double* y)
{
	double a = tan(i_wierzcholka * kat);
	*y = sqrt(r * r / (1 + a * a));
	*x = abs(a) * *y;
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
	else if (i_wierzcholka * kat < 3. * M_PI / 2.)       // + -
	{
		*y *= -1;
	}
}
/*
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

	double r = 1.0;
	double kat_alfa = 2 * M_PI / ilosc_wierzcholkow;
	double x = 0., y = r;

	generate(r, ilosc_wierzcholkow, &kat_alfa, &x, &y, vertices, indices);

	int n_verticles_to_draw = ilosc_wierzcholkow * 3;

	return n_verticles_to_draw; //returns number of verticles to draw
}
*/


Planet::Planet(double size_in, double speed_in, double radius_x_in, double radius_y_in, double color_r, double color_g, double color_b, double center_x_in, double center_y_in) {
	//std zmienne
	color[0] = color_r;
	color[1] = color_g;
	color[2] = color_b;
	size = size_in;
	center_x = center_x_in;
	center_y = center_y_in;
	radius_x = radius_x_in;
	radius_y = radius_y_in;
	speed = speed_in;
	//
	n_vertices = 5 * n_wierzcholkow;
	vertices = new GLfloat[n_vertices];
	n_indices = 3 * n_wierzcholkow;
	indices = new GLuint[n_indices];

	double kat = 2 * M_PI / n_wierzcholkow;
	int i_wierzcholka = 0;
	double x, y;
	//vertices
	for (int i = 0; i < n_wierzcholkow; i++) {
		generuj_koordynaty_wierzcholkow(size, kat, i_wierzcholka, &x, &y);
		vertices[0 + 5 * i] = x;
		vertices[1 + 5 * i] = y;
		vertices[2 + 5 * i] = color[0];
		vertices[3 + 5 * i] = color[1];
		vertices[4 + 5 * i] = color[2];
		i_wierzcholka++;
	}
	//indices
	for (int i = 0, j = 0, k = 0; i < 3 * (n_wierzcholkow - 2); i++)
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
	//VAO,VBO,EBO
	VAO_.Bind();
	VBO_ = VBO(vertices, sizeof(GLfloat) * n_vertices);
	EBO_ = EBO(indices, sizeof(GLuint) * n_indices);
	VAO_.LinkVBO(VBO_, 0, 1);
	VAO_.Unbind();
	//oribt
	// kolejnosc argumentow:
	//	 rozmiar_planety								
	//   predkosc_ruchu_planety						
	//   promien_okregu_x, promien_okregu_y			  (dla okregu takie same, dla elips ró¿ne)
	//   color_r, color_g, color_b					  (kolejne wartosci koloru z przed. [0.,1.]
	//   srodek_okregu_ruchu_x, srodek_okregu_ruchu_y (koordynaty srodka, standardowo rowne 0, mozna pominac przy wpisywaniu)
}

void Planet::update(double time, GLuint dxID, GLuint dyID) {
	double dx = center_x;
	double dy = center_y;

	center_x = 1. / speed * radius_x * sin(speed * time);
	center_y = 1. / speed * radius_y * cos(speed * time);
	dx -= center_x;
	dy -= center_y;

	glUniform1f(dxID, dx);
	glUniform1f(dyID, dy);
}

void Planet::updateCenterByOtherPlanet(double time, GLuint dxID, GLuint dyID, double centerToFollow_x, double centerToFollow_y) {
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


Planet::~Planet(){
	delete[] vertices, indices;
	VAO_.Delete();
	VBO_.Delete();
	EBO_.Delete();
}
