#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	
	type = texType;
	int weightImg, heightImg, numColCh;

	stbi_set_flip_vertically_on_load(true);

	//³adownie obrazka
	unsigned char* bytes = stbi_load(image, &weightImg, &heightImg, &numColCh, 0);

	//generowanie text
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); //filtry
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT); //powtarzanie text, jesli za ma³a - 1 oœ
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT); //                                - 2 oœ
	if (bytes) {
		glTexImage2D(texType, 0, GL_RGBA, weightImg, heightImg, 0, format, pixelType, bytes);
		glGenerateMipmap(texType);
	}
	else {
		cerr << "TEXTURE \"" << image << "\" --> FAILED TO LOAD\n";
	}
	stbi_image_free(bytes);

	glBindTexture(texType, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {

	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();

	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}