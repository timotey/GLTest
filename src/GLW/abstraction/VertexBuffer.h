/*
 * VertexBuffer.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_ABSTRACTION_VERTEXBUFFER_H_
#define GLW_ABSTRACTION_VERTEXBUFFER_H_

#include "../utils/utils.hpp"

namespace glw
{

class VertexBuffer
{
private:
	unsigned int handle = 0;
	unsigned int mode;
public:
	VertexBuffer(GLenum = GL_DYNAMIC_DRAW);
	VertexBuffer(const void* data, const size_t size, GLenum = GL_STATIC_DRAW);
	virtual ~VertexBuffer();
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer(VertexBuffer&& other);
	VertexBuffer& operator=(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(VertexBuffer&& other);
	void setData(const void* data, const size_t size);
	void bind() const;
	void unbind() const;
};

} /* namespace glw */

#endif /* GLW_ABSTRACTION_VERTEXBUFFER_H_ */
