#pragma once
#include <glad/glad.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Planet {
public:
	const int n_wierzcholkow = 20;
	GLfloat* vertices;
	int n_vertices;
	GLuint* indices;
	int n_indices;

	VAO VAO_;
	VBO VBO_;
	EBO EBO_;

	double r;
	double color[3] = { 0. };
	double center_x, center_y;


	Planet(double r, double color_r, double color_g, double color_b);
	~Planet();
	
	void update(double time, GLuint dxID, GLuint dyID, double m = 0.5, double = 10.);
};	