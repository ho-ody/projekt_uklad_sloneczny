#pragma once
#include "ShaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	//pozycja
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
	//punkt na ktory sierowana jest kamera
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	//kierunek do góry
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	//wysokosc i szerokosc okna
	int width, height;

	Camera(int width, int height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));
	//aktualizacja i ekspot macierzy kamery do vertex shadera
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	//obs³uga wejœcia kamery
};