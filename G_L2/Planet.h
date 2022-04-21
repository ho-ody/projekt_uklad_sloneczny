#pragma once
#include <glad/glad.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Planet {
public:
	const int n_wierzcholkow = 30;
	GLfloat* vertices;
	int n_vertices;
	GLuint* indices;
	int n_indices;

	VAO VAO_;
	VBO VBO_;
	EBO EBO_;

	double size;
	double color[3] = { 0. };
	double center_x, center_y;
	double speed; //liniowa prêdkoœæ - styczna do okregu
	double radius; //odlegosc od srodka

	// 
	Planet(double rozmiar_planety, double predkosc_ruchu_planety, double promien_okregu_x, double color_r, double color_g, double color_b, double srodek_okregu_ruchu_x = 0., double srodek_okregu_ruchu_y = 0.);
	~Planet();
	
	void update(double time, GLuint dxID, GLuint dyID);
};	