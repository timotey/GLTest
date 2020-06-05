/*
 * GBuffer.h
 *
 *  Created on: May 2, 2020
 *      Author: timotey
 */

#ifndef GLW_ABSTRACTION_GBUFFER_H_
#define GLW_ABSTRACTION_GBUFFER_H_
#include "../abstraction/Framebuffer.h"

namespace glw
{

class GBuffer
{
	Framebuffer f;
	Texture2 alb;
	Texture2 pos;
	Texture2 norm;
	Texture2 depth;
public:
	GBuffer(glm::vec2 size);
	virtual ~GBuffer() = default;
	GBuffer(const GBuffer& other) = delete;
	GBuffer(GBuffer&& other) = default;
	GBuffer& operator=(const GBuffer& other) = delete;
	GBuffer& operator=(GBuffer&& other) = default;
	void bind(Framebuffer::target target)
	{
		if (target != Framebuffer::read)
			this->f.bind(target);
		if (target != Framebuffer::draw)
		{
			this->alb.bind(0);
			this->pos.bind(1);
			this->norm.bind(2);
		}
	}
	void unbind()
	{
		this->f.unbind();
	}

};

} /* namespace glw */

#endif /* GLW_ABSTRACTION_GBUFFER_H_ */
