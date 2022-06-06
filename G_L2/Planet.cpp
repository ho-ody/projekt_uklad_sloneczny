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

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
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
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indice[0] = k1;
				indice[1] = k2;
				indice[2] = k1 + 1;
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indice[3] = k1 + 1;
				indice[4] = k2;
				indice[5] = k2 + 1;
			}

			/*
			// store indices for lines
			// vertical lines for all stacks, k1 => k2
			lineIndices.push_back(k1);
			lineIndices.push_back(k2);
			if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
			{
				lineIndices.push_back(k1);
				lineIndices.push_back(k1 + 1);
			}
			*/
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
/*
	sp_nv = 11 * (1 + sectorCount + stackCount * sectorCount);
	sp_nv = 11 * (stackCount + 1) * (sectorCount + 1);
	sp_v = new GLfloat[sp_nv];
	sp_ni = 6 * (stackCount - 1) * sectorCount;
	//sp_ni = 15;
	sp_i = new GLuint[sp_ni];


	VAO VAO_sphere;
	VAO_sphere.Bind();

	gen_sphere();


	VBO VBO_sphere(sp_v, sizeof(GLfloat) * sp_nv);
	EBO EBO_sphere(sp_i, sizeof(GLuint) * sp_ni);
	int i_draw = sp_nv;

*/
/*

	VAO_sphere.Bind();
	VAO_sphere.LinkAttrib(VBO_sphere, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);		//linkowanie konkretnych rzeczy z default.vert
	VAO_sphere.LinkAttrib(VBO_sphere, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO_sphere.LinkAttrib(VBO_sphere, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO_sphere.LinkAttrib(VBO_sphere, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO_sphere.Unbind();
	VBO_sphere.Unbind();
	EBO_sphere.Unbind();


	glm::vec3 spherePos = glm::vec3(0.0f, -5.0f, 0.0f);
	glm::mat4 sphereMod = glm::mat4(1.0f);
	sphereMod = glm::translate(sphereMod, spherePos);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(sphereMod));
*/
Planet::Planet(double size_in, double speed_in, double radius_x_in, double radius_y_in, double color_r, double color_g, double color_b, double center_x_in, double center_y_in) {
	//std zmienne
	color[0] = color_r / 255;
	color[1] = color_g / 255;
	color[2] = color_b / 255;
	size = size_in;
	center_x = center_x_in;
	center_y = center_y_in;
	radius_x = radius_x_in;
	radius_y = radius_y_in;
	speed = speed_in;
	
	//
	n_vertices = 11 * (stackCount + 1) * (sectorCount + 1);
	n_indices = 6 * (stackCount - 1) * sectorCount;
	vertices = new GLfloat[n_vertices];
	indices = new GLuint[n_indices];
	
	gen_sphere(size/10., vertices, indices);
	
	
	
	
	
	
	/*
	n_vertices = 11 * n_wierzcholkow;
	vertices = new GLfloat[n_vertices];
	n_indices = 3 * n_wierzcholkow;
	indices = new GLuint[n_indices];

	double kat = 2 * M_PI / n_wierzcholkow;
	int i_wierzcholka = 0;
	double x, y;
	//vertices
	for (int i = 0; i < n_wierzcholkow; i++) {
		generuj_koordynaty_wierzcholkow(size, kat, i_wierzcholka, &x, &y);
		vertices[0 + 11 * i] = x;
		vertices[1 + 11 * i] = 0.; // y - póki co = 0
		vertices[2 + 11 * i] = y; 

		vertices[3 + 11 * i] = color[0];
		vertices[4 + 11 * i] = color[1];
		vertices[5 + 11 * i] = color[2];

		vertices[6 + 11 * i] = 0.;
		vertices[7 + 11 * i] = 0.;

		vertices[8 + 11 * i] = 0.;
		vertices[9 + 11 * i] = 0.;
		vertices[10 + 11 * i] = 0.;
		/*
		layout (location = 0) in vec3 position;
		layout (location = 1) in vec3 inColor;
		layout (location = 2) in vec2 inTexture;
		layout (location = 3) in vec3 inNormal;
		//!!!
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
	*/
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
void Planet::update(double time, GLuint dxID, GLuint dyID) {
	double dx = center_x;
	double dy = center_y;

	


	center_x = 1. / speed * radius_x * sin(speed * time);
	center_y = 1. / speed * radius_y * cos(speed * time);

	position.x = center_x / 10.;
	position.y = 0.;
	position.z = center_y / 10.;

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

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