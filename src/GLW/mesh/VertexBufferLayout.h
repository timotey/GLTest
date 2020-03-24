/*
 * VertexBufferLayout.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_MESH_VERTEXBUFFERLAYOUT_H_
#define GLW_MESH_VERTEXBUFFERLAYOUT_H_

#include "../dependencies.h"
#include "../utils/gltype.hpp"

namespace glw
{

class VertexBufferLayout
{
public:
	struct element
	{
		GLenum type;
		size_t size;
		size_t count;
	};
	VertexBufferLayout() = default;
	virtual ~VertexBufferLayout() = default;
	VertexBufferLayout(const VertexBufferLayout &other) : stride(other.stride), elements(other.elements){}
	VertexBufferLayout(VertexBufferLayout &&other) : stride(other.stride), elements(other.elements){}
	VertexBufferLayout& operator=(const VertexBufferLayout &other)
	{
		this->stride = other.stride;
		this->elements = other.elements;
		return *this;
	}
	VertexBufferLayout& operator=(VertexBufferLayout &&other)
	{
		this->stride = other.stride;
		this->elements = other.elements;
		return *this;
	}
	inline const std::vector<element> getLayout() const
	{
		return this->elements;
	}

	inline size_t getStride() const
	{
		return this->stride;
	}

	template<typename T>
	inline void push(size_t count)
	{
		elements.push_back({glw::utils::glGetEnum<T>(), sizeof(T)*count, count});
		stride += sizeof(T)*count;
	}
protected:
	size_t stride = 0;
	std::vector<element> elements;
};

} /* namespace glw */

#endif /* GLW_MESH_VERTEXBUFFERLAYOUT_H_ */
