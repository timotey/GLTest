/*
 * Texture.cpp
 *
 *  Created on: Feb 22, 2020
 *      Author: timotey
 */

#include "../mesh/Texture.h"

namespace glw
{

Texture::Texture(size_t width, size_t height)
		: size(width, height)
{
	glw::utils::glcall(__LINE__, __FILE__, glGenTextures, 1, &this->handle);
	glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GL_TEXTURE_2D,
	        this->handle);

	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	this->unbind();
}

Texture::Texture(glm::uvec2 _size)
		: size(_size)
{
	glw::utils::glcall(__LINE__, __FILE__, glGenTextures, 1, &this->handle);
	glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GL_TEXTURE_2D,
	        this->handle);

	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GL_TEXTURE_2D,
	GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	this->unbind();
}

Texture::~Texture()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteTextures, 1, &this->handle);
}

Texture::Texture(Texture &&other)
{
	this->BPP = other.BPP;
	this->size = other.size;
	this->handle = other.handle;
	other.handle = 0;
}

Texture& Texture::operator =(Texture &&other)
{
	this->BPP = other.BPP;
	this->size = other.size;
	this->handle = other.handle;
	other.handle = 0;
	return *this;
}

Texture make_Texture(const std::string &file)
{
	Texture tex;
	tex.bind(0);
	stbi_set_flip_vertically_on_load(true);
	unsigned char *input = stbi_load(file.c_str(),
	        &reinterpret_cast<int&>(tex.size.x),
	        &reinterpret_cast<int&>(tex.size.y), &tex.BPP, 4);

	glw::utils::glcall(__LINE__, __FILE__, glTexImage2D, GL_TEXTURE_2D, 0,
	GL_RGBA, tex.size.x, tex.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, input);

	stbi_image_free(input);
	return tex;
}

void Texture::bind(unsigned int slot) const
{
	if (!this->handle)
		return;
	if (slot > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)
		std::cout << std::dec << "no texture slot" << slot << std::endl;
	int value;
	glw::utils::glcall(__LINE__, __FILE__, glActiveTexture, GL_TEXTURE0 + slot);
	glw::utils::glcall(__LINE__, __FILE__, glGetIntegeri_v,
	GL_TEXTURE_BINDING_2D, slot, &value);
	if (this->handle != value)
		glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GL_TEXTURE_2D,
		        this->handle);
}

void Texture::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GL_TEXTURE_2D, 0);
}

} /* namespace glw */
