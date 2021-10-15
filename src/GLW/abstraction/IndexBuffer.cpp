/*
 * IndexBuffer.cpp
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#include "../abstraction/IndexBuffer.h"
#if 0
namespace glw
{

IndexBuffer::IndexBuffer()
{
	glw::utils::glcall(__LINE__, __FILE__, glGenBuffers, 1, &this->handle);
}

IndexBuffer::IndexBuffer(const unsigned int* data, const size_t count) : count(count)
{
	glw::utils::glcall(__LINE__, __FILE__, glGenBuffers, 1, &this->handle);
	this->setData(data, count);
}

IndexBuffer::~IndexBuffer()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteBuffers, 1, &this->handle);
}

IndexBuffer::IndexBuffer(IndexBuffer &&other)
{
	this->count = other.count;
	this->handle = other.handle;
	other.handle = 0;
}

IndexBuffer& IndexBuffer::operator =(IndexBuffer &&other)
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteBuffers, 1, &this->handle);
	this->count = other.count;
	this->handle = other.handle;
	other.handle = 0;
	return *this;
}

void IndexBuffer::setData(const unsigned int* data, const size_t count)
{
	this->bind();
	glw::utils::glcall(__LINE__, __FILE__, glBufferData, GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
	this->count = count;
}

void IndexBuffer::bind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, this->handle);
}

void IndexBuffer::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
}

} /* namespace glw */
#endif
