#include "Planet.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

//
int sectorCount = 36;		//36 //12
int stackCount = 18;		//18 //6

void gen_sphere(float radius, GLfloat* vertices = NULL, GLuint* indices = NULL) {
	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;

	int v_counter = 0;
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi
			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices[0 + v_counter * 11] = x;
			vertices[1 + v_counter * 11] = y;
			vertices[2 + v_counter * 11] = z;
			// colors
			vertices[3 + v_counter * 11] = 0.8;
			vertices[4 + v_counter * 11] = 0.8;
			vertices[5 + v_counter * 11] = 0.8;
			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			vertices[8 + v_counter * 11] = nx;
			vertices[9 + v_counter * 11] = ny;
			vertices[10 + v_counter * 11] = nz;
			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			vertices[6 + v_counter * 11] = s;
			vertices[7 + v_counter * 11] = t;
			v_counter++;
		}
	}
	int k1, k2;
	float indice[6];

	int indices_counter = 0;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			indice[0] = indice[1] = indice[2] = indice[3] = indice[4] = indice[5] = 0;
			if (i != 0)
			{
				indice[0] = k1;
				indice[1] = k2;
				indice[2] = k1 + 1;
			}
			if (i != (stackCount - 1))
			{
				indice[3] = k1 + 1;
				indice[4] = k2;
				indice[5] = k2 + 1;
			}
			if (indice[0]) { //not 0
				indices[0 + indices_counter] = indice[0];
				indices[1 + indices_counter] = indice[1];
				indices[2 + indices_counter] = indice[2];
				indices_counter += 3;
			}
			if (indice[3]) { //not 0
				indices[0 + indices_counter] = indice[3];
				indices[1 + indices_counter] = indice[4];
				indices[2 + indices_counter] = indice[5];
				indices_counter += 3;
			}
		}
	}
}
Planet::Planet(const char* texture_name, double size_in, double speed_in, double radius_x_in, double radius_y_in, double color_r, double color_g, double color_b, double center_x_in, double center_y_in) {
	//textury
	texture = Texture(texture_name, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	//std zmienne
	color[0] = color_r / 255;
	color[1] = color_g / 255;
	color[2] = color_b / 255;
	size =  2 * size_in;
	radius_x = radius_x_in;
	radius_y = radius_y_in;
	speed = speed_in;
	//
	n_vertices = 11 * (stackCount + 1) * (sectorCount + 1);
	n_indices = 6 * (stackCount - 1) * sectorCount;
	vertices = new GLfloat[n_vertices];
	indices = new GLuint[n_indices];
	gen_sphere(size/10., vertices, indices);
			
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
	//oribt
	// kolejnosc argumentow:
	//	 rozmiar_planety								
	//   predkosc_ruchu_planety						
	//   promien_okregu_x, promien_okregu_y			  (dla okregu takie same, dla elips ró¿ne)
	//   color_r, color_g, color_b					  (kolejne wartosci koloru z przed. [0.,1.]
	//   srodek_okregu_ruchu_x, srodek_okregu_ruchu_y (koordynaty srodka, standardowo rowne 0, mozna pominac przy wpisywaniu)
}
extern glm::vec3 TESTpos;
void Planet::update(double time) {
	float multi = 10;
	position.x = radius_x * sin(speed * time) / multi;
	position.y = 0.;
	position.z = radius_y * cos(speed * time) / multi;

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
}

void Planet::updateCenterByOtherPlanet(double time, double centerToFollow_x, double centerToFollow_z) {
	float multi = 10;
	position.x = radius_x * sin(speed * time) / multi;
	position.y = 0.;
	position.z = radius_y * cos(speed * time) / multi;

	position.x += centerToFollow_x;
	position.z += centerToFollow_z;

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
}

Planet::~Planet(){
	texture.Delete();
	delete[] vertices, indices;
	VAO_.Delete();
	VBO_.Delete();
	EBO_.Delete();
}