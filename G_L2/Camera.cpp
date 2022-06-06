#include "Camera.h"

Camera::Camera(int width_, int height_, glm::vec3 position_) {
	width = width_;
	height = height_;
	Position = position_;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	//inicjalizacja macierzy view i projection - macierze jednostkowe
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	//usytu�owanie kamery, patrzenie w danym kierunku
	view = glm::lookAt(Position, Position + Orientation, Up); //mod: dodano  .. + position .. -> �atwiejsza obs�uga ruchu

	//macierz projekcji - rzutowanie perspektywiczne
	// 1) k�t pod jakim wida� g�rn� i doln� p�aszczyn� obcinaj�c� bry�y widzenia
	// 2) proporcje obszaru wizualizacji
	// 3) po�o�enie przedniej p�aszczyny obcinaj�cej
	// 4) po�o�enie tylniej p�aszczyny obcinaj�cej
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

	//eksport macierzy kamery do vertex shadera
	// 1) location - lokalizacja zmiennej uniform w programie shader�w
	// 2) count - ilo�� macierzy do przekazania
	// 3) transpose - konieczno�� transpozycji macierzy ( 0 v 1 )
	// 4) value - wska�nik do wektora zawieraj�cego przekszyta�con� macierz
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}