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
	//usytu³owanie kamery, patrzenie w danym kierunku
	view = glm::lookAt(Position, Position + Orientation, Up); //mod: dodano  .. + position .. -> ³atwiejsza obs³uga ruchu

	//macierz projekcji - rzutowanie perspektywiczne
	// 1) k¹t pod jakim widaæ górn¹ i doln¹ p³aszczynê obcinaj¹c¹ bry³y widzenia
	// 2) proporcje obszaru wizualizacji
	// 3) po³o¿enie przedniej p³aszczyny obcinaj¹cej
	// 4) po³o¿enie tylniej p³aszczyny obcinaj¹cej
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

	//eksport macierzy kamery do vertex shadera
	// 1) location - lokalizacja zmiennej uniform w programie shaderów
	// 2) count - iloœæ macierzy do przekazania
	// 3) transpose - koniecznoœæ transpozycji macierzy ( 0 v 1 )
	// 4) value - wskaŸnik do wektora zawieraj¹cego przekszyta³con¹ macierz
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}