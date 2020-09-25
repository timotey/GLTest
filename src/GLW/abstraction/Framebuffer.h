/*
 * Framebuffer.h
 *
 *  Created on: Mar 30, 2020
 *      Author: timotey
 */

#ifndef GLW_ABSTRACTION_FRAMEBUFFER_H_
#define GLW_ABSTRACTION_FRAMEBUFFER_H_

#include "../abstraction/Texture.h"
#include "../utils/utils.hpp"

namespace glw
{

///
///@brief The opengl framebuffer abstraction
///

class Framebuffer
{
private:
	unsigned h;
	std::vector<GLenum> attachments;
public:
	enum target : GLenum
	{
		draw = GL_DRAW_FRAMEBUFFER,
		read = GL_READ_FRAMEBUFFER,
		both = GL_FRAMEBUFFER,
	};
	enum attachment : GLenum
	{
		stencil = GL_STENCIL_ATTACHMENT,
		depth = GL_DEPTH_ATTACHMENT,
		depth_stencil = GL_DEPTH_STENCIL_ATTACHMENT,
	};
	///
	///@brief a function to obtain a handle of underlying opengl FBO
	///
	///@return handle of opengl FBO
	///
	///@retval 0 no resource attached
	///
	unsigned handle() const
	{
		return h;
	}

	///
	///@brief function to bind FBO for reading or drawing
	///
	///@param[in] target specifies the operation (reading, drawing, both)
	///

	void bind(target) const;

	///
	///@brief function to unbind the current FBO and bind the default one (for debugging)
	///
	void unbind() const;

	///
	///@brief function to attach a texture to non-color attachment slot
	///
	///@param[in] target specifies the operation (reading, drawing, both)
	///@param[in]  specifies the operation (reading, drawing, both)
	///
	void attach(target, attachment, Texture2 const&);
	void attach(target, size_t, Texture2 const&);
	Framebuffer();
	virtual ~Framebuffer();
	Framebuffer(Framebuffer const& other) = delete;
	Framebuffer(Framebuffer&& other);
	Framebuffer& operator=(Framebuffer const& other) = delete;
	Framebuffer& operator=(Framebuffer&& other);
};

} /* namespace glw */

#endif /* GLW_ABSTRACTION_FRAMEBUFFER_H_ */
