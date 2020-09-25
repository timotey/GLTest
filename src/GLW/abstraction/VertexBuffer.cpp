/*
 * VertexBuffer.cpp
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#include "../abstraction/VertexBuffer.h"
#ifdef DONT_DEFINE_THIS_
namespace glw
{

VertexBuffer::VertexBuffer(GLenum _mode)
		: mode(_mode)
{
	glw::utils::glcall(__LINE__, __FILE__, glGenBuffers, 1, &this->handle);
}

VertexBuffer::VertexBuffer(const void* data, const size_t size, GLenum mode)
		: mode(mode)
{
	glw::utils::glcall(__LINE__, __FILE__, glGenBuffers, 1, &this->handle);
	this->setData(data, size);
}

VertexBuffer::~VertexBuffer()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteBuffers, 1, &this->handle);
}

void VertexBuffer::setData(const void* data, const size_t size)
{
	this->bind();
	glw::utils::glcall(__LINE__, __FILE__, glBufferData, GL_ARRAY_BUFFER, size,
	        data, this->mode);
}

void VertexBuffer::bind() const
{
	unsigned binding = 0;
	glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv,
	GL_ARRAY_BUFFER_BINDING, reinterpret_cast<int*>(&binding)); //check if thing is already bound

	if (binding != this->handle)
		glw::utils::glcall(__LINE__, __FILE__, glBindBuffer, GL_ARRAY_BUFFER,
		        this->handle);
}

void VertexBuffer::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindBuffer, GL_ARRAY_BUFFER, 0);
}
VertexBuffer::VertexBuffer(VertexBuffer&& other)
{
	this->mode = other.mode;
	this->handle = other.handle;
	other.handle = 0;
}

VertexBuffer& VertexBuffer::operator =(VertexBuffer&& other)
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteBuffers, 1, &this->handle);
	this->mode = other.mode;
	this->handle = other.handle;
	other.handle = 0;
	return *this;
}

} /* namespace glw */
#endif
