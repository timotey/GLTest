/*
 * VertexBufferLayout.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_ABSTRACTION_VERTEXBUFFERLAYOUT_H_
#define GLW_ABSTRACTION_VERTEXBUFFERLAYOUT_H_

#include "../dependencies.h"
#include "../utils/gltype.hpp"

namespace glw
{

class VertexBufferLayout
{
public:
	std::map<size_t, size_t> strides;
	struct element
	{
		GLenum type;
		size_t size;
		size_t count;
		size_t divisor;
		size_t bufferID;
		size_t offset;
	};
	VertexBufferLayout() = default;
	virtual ~VertexBufferLayout() = default;
	VertexBufferLayout(VertexBufferLayout const& other) :
			strides(other.strides),
			elements(other.elements)
	{
	}
	VertexBufferLayout(VertexBufferLayout&& other) :
			strides(other.strides),
			elements(other.elements)
	{
	}
	VertexBufferLayout& operator=(VertexBufferLayout const& other)
	{
		this->strides = other.strides;
		this->elements = other.elements;
		return *this;
	}
	VertexBufferLayout& operator=(VertexBufferLayout&& other)
	{
		this->strides = other.strides;
		this->elements = other.elements;
		return *this;
	}
	inline std::vector<element> const getLayout() const
	{
		return this->elements;
	}

	inline std::map<size_t, size_t> const& getStrides() const
	{
		return this->strides;
	}

	inline size_t getAttribCount() const
	{
		return this->elements.size();
	}

	inline bool isDirty() const
	{
		return this->dirty;
	}

	inline void unDirty() const
	{
		this->dirty = false;
	}

	template <typename T>
	inline void push(size_t count, size_t buffID = 0, size_t divisor = 0)
	{
		this->dirty = true;
		elements.push_back({glw::utils::glEnum<T>, sizeof(T) * count, count, // @suppress("Invalid arguments")
		        divisor, buffID, this->strides[buffID]});
		this->strides[buffID] += sizeof(T) * count;
	}

protected:
	mutable bool dirty = true;
	std::vector<element> elements;
};

} /* namespace glw */

#endif /* GLW_ABSTRACTION_VERTEXBUFFERLAYOUT_H_ */
