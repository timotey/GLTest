/*
 * Framebuffer.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: timotey
 */

#include "Framebuffer.h"

namespace glw
{

Framebuffer::Framebuffer()
{
	glw::utils::glcall(__LINE__, __FILE__, glGenFramebuffers, 1, &this->h);
}

Framebuffer::Framebuffer(Framebuffer&& other)
{
	this->h = other.h;
	other.h = 0;
}

Framebuffer::~Framebuffer()
{
	if (this->handle())
		glw::utils::glcall(__LINE__, __FILE__, glDeleteFramebuffers, 1,
		        &this->h);
	this->h = 0;
}

void Framebuffer::bind(target t) const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindFramebuffer, t, this->h);
	glw::utils::glcall(__LINE__, __FILE__, glDrawBuffers, attachments.size(),
	        attachments.data());

	size_t error;
	if ( (error = glw::utils::glcall(__LINE__, __FILE__,
	glCheckFramebufferStatus,
	GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		glw::utils::glcall(__LINE__, __FILE__, glBindFramebuffer,
		GL_FRAMEBUFFER, 0);
		std::cerr << "Framebuffer " << this->handle() << " is not complete: "
		        << std::hex << error << std::dec << "\n";
	}
}

void Framebuffer::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindFramebuffer,
	GL_FRAMEBUFFER, 0);
}

void Framebuffer::attach(target t, attachment a, Texture2 const& target)
{
	glw::utils::glcall(__LINE__, __FILE__, glBindFramebuffer,
	GL_FRAMEBUFFER, this->h);
	glw::utils::glcall(__LINE__, __FILE__, glFramebufferTexture, t, a,
	        int(target.handle()), 0);
}

void Framebuffer::attach(target t, size_t a, Texture2 const& target)
{
	glw::utils::glcall(__LINE__, __FILE__, glBindFramebuffer,
	GL_FRAMEBUFFER, this->h);
	int att = int(a) + GL_COLOR_ATTACHMENT0;
	this->attachments.push_back(att);
	glw::utils::glcall(__LINE__, __FILE__, glFramebufferTexture, t, att,
	        int(target.handle()), 0);
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other)
{
	this->h = other.h;
	other.h = 0;
	return *this;
}

} /* namespace glw */
