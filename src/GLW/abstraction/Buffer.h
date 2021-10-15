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

///
///@brief enum which describes OpenGL buffer type
///
enum class buffer_type : GLenum
{
	vertex = GL_ARRAY_BUFFER,
	index = GL_ELEMENT_ARRAY_BUFFER,
	uniform = GL_UNIFORM_BUFFER
};

template<class... Ts>
class buffer_struct_type;

template<class T, class... Ts>
class buffer_struct_type<T, Ts...>
{
	T value;

};

///
///@brief adapter from OpenGL macro definition to templated constant
///
///@tparam buffer_type 
///
///@return buffer binding constant corresponding to the buffer type
///
template <buffer_type>
constexpr GLenum binding_conversion;
template <>
constexpr GLenum binding_conversion<buffer_type::index> = GL_INDEX_ARRAY_BUFFER_BINDING;
template <>
constexpr GLenum binding_conversion<buffer_type::vertex> = GL_ARRAY_BUFFER_BINDING;
template <>
constexpr GLenum binding_conversion<buffer_type::uniform> = GL_UNIFORM_BUFFER_BINDING;

///
///@brief abstraction for OpenGL Buffer Object
///
///@details a class which represents and does resource management for OpenGL Buffer Object
///
///@tparam type specifies which type of buffer needs to be created
///
template <buffer_type type>
class Buffer
{
public:
	///
	///@brief adapter for OpenGL buffer usage hints
	///
	///@details enum which provides type-safe wrapper for default OpenGL macro definitions for buffer usage hints
	///
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

    Buffer(const void* data, const size_t size, mode _m = mode::dynamic_draw):
        m(_m), _size(size)
    {
        glw::utils::glcall(__LINE__, __FILE__, glGenBuffers, 1,
                &reinterpret_cast<unsigned&>(this->handle));
        this->setData(data, size);
    }

    Buffer(Buffer&& other)
    {
        this->handle = other.handle;
        this->_size = other._size;
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
        this->_size = other._size;
        return *this;
    }

    Buffer()
    {
        glw::utils::glcall(__LINE__, __FILE__, glDeleteBuffers, 1,
                &reinterpret_cast<unsigned&>(this->handle));
    }
    size_t getSize() const {
        return _size;
    }
    void setData(const void* data, const size_t size)
    {
        Buffer::Buffer_guard g;
        this->bind();
        glw::utils::lglcall(__LINE__, __FILE__, [&]()
        {	glBufferData( GLenum(type), size, data,
                    GLenum(this->m));});
        _size = size;
    }

    void bind() const
    {
        glw::utils::lglcall(__LINE__, __FILE__, [&]()
        {	glBindBuffer(GLenum(type), this->handle);});
    }
    void unbind() const
    {
        glw::utils::lglcall(__LINE__, __FILE__, [&]()
        {	glBindBuffer(GLenum(type), 0);});
    }
private:
	///
	///@brief a helper class to prevent unexpected OpenGL state changes related to buffer bindings
	///
	///@details this class remembers current bound buffer on construction and restores it on destuction
	///
	class Buffer_guard
	{
	public:
		int h;
		Buffer_guard() :
				h(0)
		{
			glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv,
			        binding_conversion<type>, &this->h);
		}
		~Buffer_guard()
		{
			glw::utils::lglcall(__LINE__, __FILE__, [&]()
			{	glBindBuffer(GLenum(type), this->h);});
		}
	};
	int handle;
	mode m;
    size_t _size = 0;
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
