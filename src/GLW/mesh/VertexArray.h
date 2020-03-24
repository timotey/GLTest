/*
 * VertexArray.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_MESH_VERTEXARRAY_H_
#define GLW_MESH_VERTEXARRAY_H_

#include "../mesh/VertexBuffer.h"
#include "../mesh/VertexBufferLayout.h"

namespace glw
{

class VertexArray
{
private:
	unsigned int handle = 0;
	VertexBuffer vb;
	VertexBufferLayout layout;
//	void makeArray(const VertexBuffer &, const VertexBufferLayout &);
public:
	VertexArray();
	VertexArray(VertexBuffer&&, const VertexBufferLayout&);
	virtual ~VertexArray();
	VertexArray(const VertexArray &other) = delete;
	VertexArray(VertexArray &&other);
	VertexArray& operator=(const VertexArray &other) = delete;
	VertexArray& operator=(VertexArray &&other);
	void makeArray(VertexBuffer&&, const VertexBufferLayout&);
	void bind() const;
	void unbind() const;
};

} /* namespace glw */

#endif /* GLW_MESH_VERTEXARRAY_H_ */
