/*
 * GBuffer.cpp
 *
 *  Created on: May 2, 2020
 *      Author: timotey
 */

#include "../abstraction/GBuffer.h"

namespace glw
{

GBuffer::GBuffer(glm::vec2 size) :
		alb(size), // @suppress("Ambiguous problem")
		pos(size, {GL_RGBA32F, GL_FLOAT, Texture_settings::format::rgba}),
		norm(size,
		        {GL_RGBA8, GL_UNSIGNED_BYTE, Texture_settings::format::rgba}),
		depth(size, {GL_DEPTH24_STENCIL8, GL_UNSIGNED_INT_24_8,
		        Texture_settings::format::ds})
{
	this->f.attach(Framebuffer::draw, Framebuffer::depth_stencil, this->depth);
	this->f.attach(Framebuffer::draw, 0, this->alb);
	this->f.attach(Framebuffer::draw, 1, this->pos);
	this->f.attach(Framebuffer::draw, 2, this->norm);
}

}
/* namespace glw */
