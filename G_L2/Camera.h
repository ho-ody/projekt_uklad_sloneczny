#pragma once
#include "ShaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	//pozycja
	glm::vec3 Position;
	//punkt na ktory sierowana jest kamera
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	//kierunek do góry
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	//nowa macierz kamery
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	//wysokosc i szerokosc okna
	int width, height;
	//pierwsza interakcja myszy
	bool firstClick = true;
	//konfiguracja myszy
	float speed = 0.04f;
	float sensitivity = 100.0f;
	float fov = 45.0f;

	Camera(int width, int height, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 orientation = glm::vec3(0.0, 0.0, -1.0));
	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	//obs³uga wejœcia kamery
	void Inputs(GLFWwindow* window);
};