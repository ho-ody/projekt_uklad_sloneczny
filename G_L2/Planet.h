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

	Planet(double size_in, double speed_in, double radius_in, double color_r, double color_g, double color_b, double center_x_in = 0., double center_y_in = 0.);
	~Planet();
	
	void update(double time, GLuint dxID, GLuint dyID);
};	