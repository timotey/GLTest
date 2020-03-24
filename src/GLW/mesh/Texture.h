/*
 * Texture.h
 *
 *  Created on: Feb 22, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_TEXTURE_H_
#define GLW_MODEL_TEXTURE_H_

#include "../dependencies.h"
#include "../vendor/stb_image.h"
#include "../utils/utils.hpp"
#include "Material.h"

namespace glw
{

class Texture
{
protected:
	unsigned int handle = 0;
	glm::uvec2 size;
	int BPP = 0;
public:
	Texture(size_t width, size_t height);
	Texture(glm::uvec2 _size = glm::uvec2());
	virtual ~Texture();
	Texture(const Texture &other) = delete;
	Texture(Texture &&other);
	Texture& operator=(const Texture &other) = delete;
	Texture& operator=(Texture &&other);
	friend Texture make_Texture(const std::string &file);
	void bind(unsigned int slot) const;
	void unbind() const;
};
Texture make_Texture(const std::string &file);

} /* namespace glw */

#endif /* GLW_MODEL_TEXTURE_H_ */
