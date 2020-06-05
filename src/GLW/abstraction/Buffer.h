/*
 * Buffer.h
 *
 *  Created on: May 12, 2020
 *      Author: timotey
 */

#ifndef GLW_ABSTRACTION_BUFFER_H_
#define GLW_ABSTRACTION_BUFFER_H_

#include "../dependencies.h"
#include "../utils/utils.hpp"

namespace glw
{

enum class buffer_type : GLenum
{
	vertex = GL_ARRAY_BUFFER,
	index = GL_ELEMENT_ARRAY_BUFFER,
	uniform = GL_UNIFORM_BUFFER
};

template <buffer_type>
GLenum binding_conversion;
template <>
GLenum binding_conversion<buffer_type::index> = GL_INDEX_ARRAY_BUFFER_BINDING;
template <>
GLenum binding_conversion<buffer_type::vertex> = GL_ARRAY_BUFFER_BINDING;
template <>
GLenum binding_conversion<buffer_type::uniform> = GL_UNIFORM_BUFFER_BINDING;

template <buffer_type T>
class Buffer
{
public:
	enum class mode : GLenum
	{
		stream_draw = GL_STREAM_DRAW,
		stream_read = GL_STREAM_READ,
		stream_copy = GL_STREAM_COPY,
		static_draw = GL_STATIC_DRAW,
		static_read = GL_STATIC_READ,
		static_copy = GL_STATIC_COPY,
		dynamic_draw = GL_DYNAMIC_DRAW,
		dynamic_read = GL_DYNAMIC_READ,
		dynamic_copy = GL_DYNAMIC_COPY,
	};
	Buffer(mode _m) :
			m(_m)
	{
		glw::utils::glcall(__LINE__, __FILE__, glGenBuffers, 1,
		        &reinterpret_cast<unsigned&>(this->handle));
	}
	Buffer(const void* data, const size_t size)
	{
		glw::utils::glcall(__LINE__, __FILE__, glGenBuffers, 1,
		        &reinterpret_cast<unsigned&>(this->handle));
		this->setData(data, size);
	}
	Buffer(Buffer&& other)
	{
		this->handle = other.handle;
		this->m = other.m;
		other.handle = 0;
	}
	Buffer& operator=(Buffer&& other)
	{
		glw::utils::glcall(__LINE__, __FILE__, glDeleteBuffers, 1,
		        &reinterpret_cast<unsigned&>(this->handle));
		this->handle = other.handle;
		other.handle = 0;
		this->m = other.m;
		return *this;
	}
	~Buffer()
	{
		glw::utils::glcall(__LINE__, __FILE__, glDeleteBuffers, 1,
		        &reinterpret_cast<unsigned&>(this->handle));
	}

	void setData(const void* data, const size_t size)
	{
		Buffer::Buffer_guard g;
		this->bind();
		glw::utils::lglcall(__LINE__, __FILE__, [&]()
		{	glBufferData( GLenum(T), size, data,
					GLenum(this->m));});
	}
	void bind() const
	{
		glw::utils::lglcall(__LINE__, __FILE__, [&]()
		{	glBindBuffer(GLenum(T), this->handle);});
	}
private:
	class Buffer_guard
	{
	public:
		int h;
		Buffer_guard() :
				h(0)
		{
			glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv,
			        binding_conversion<T>, &this->h);
		}
		~Buffer_guard()
		{
			glw::utils::lglcall(__LINE__, __FILE__, [&]()
			{	glBindBuffer(GLenum(T), this->h);});
		}
	};
	int handle;
	mode m;
};

extern template class Buffer<buffer_type::uniform> ;
extern template class Buffer<buffer_type::vertex> ;
extern template class Buffer<buffer_type::index> ;

using UniformBuffer = Buffer<buffer_type::uniform>;
using VertexBuffer = Buffer<buffer_type::vertex>;
using IndexBuffer = Buffer<buffer_type::index>;

}
// namespace glw

#endif /* GLW_ABSTRACTION_BUFFER_H_ */
