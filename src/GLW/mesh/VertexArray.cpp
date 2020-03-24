/*
 * VertexArray.cpp
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#include "../mesh/VertexArray.h"

namespace glw
{

VertexArray::VertexArray()
{
	glw::utils::glcall(__LINE__, __FILE__, glGenVertexArrays, 1, &this->handle);
	this->bind();
}
VertexArray::VertexArray(VertexBuffer &&vb, const VertexBufferLayout &layout)
		: layout(layout)
{
	glw::utils::glcall(__LINE__, __FILE__, glGenVertexArrays, 1, &this->handle);
	this->bind();
	this->makeArray(std::move(vb), layout);
}

VertexArray::~VertexArray()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteVertexArrays, 1,
	        &this->handle);
}

void VertexArray::makeArray(VertexBuffer &&vb, const VertexBufferLayout &layout)
{
	this->vb = std::move(vb);
	this->bind();
	this->vb.bind();
	std::vector<VertexBufferLayout::element> types = layout.getLayout();
	size_t stride = layout.getStride();
	size_t offset = 0;
	for (size_t i = 0; i < types.size(); i++)
	{
		auto element = types[i];
		glw::utils::glcall(__LINE__, __FILE__, glVertexAttribPointer, i,
		        element.count, element.type, GL_FALSE, stride,
		        reinterpret_cast<void*>(offset));
		glw::utils::glcall(__LINE__, __FILE__, glEnableVertexAttribArray, i);
		offset += element.size;
	}
}

void VertexArray::bind() const
{
	unsigned binding = 0;
	glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv, GL_CURRENT_PROGRAM,
	        reinterpret_cast<int*>(&binding)); //check if thing is already bound

	if (binding != this->handle)
		glw::utils::glcall(__LINE__, __FILE__, glBindVertexArray, this->handle);
}

void VertexArray::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindVertexArray, 0);
}

VertexArray::VertexArray(VertexArray &&other)
		: vb(std::move(other.vb)), layout(std::move(other.layout))
{
	this->handle = other.handle;
	other.handle = 0;
}

VertexArray& VertexArray::operator =(VertexArray &&other)
{
	this->layout = std::move(other.layout);
	this->vb = std::move(other.vb);
	this->handle = other.handle;
	other.handle = 0;
	return *this;
}

} /* namespace glw */
