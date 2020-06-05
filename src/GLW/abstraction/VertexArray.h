/*
 * VertexArray.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_ABSTRACTION_VERTEXARRAY_H_
#define GLW_ABSTRACTION_VERTEXARRAY_H_

#include "../abstraction/IndexBuffer.h"
#include "../abstraction/VertexBuffer.h"
#include "../abstraction/VertexBufferLayout.h"

namespace glw
{

class VertexArray
{
private:
	unsigned int handle = 0;
public:
	IndexBuffer ib;
	std::vector<VertexBuffer> vb;
	VertexBufferLayout layout;
	VertexArray(IndexBuffer&&, VertexBuffer&&, const VertexBufferLayout&);
	virtual ~VertexArray();
	VertexArray(const VertexArray& other) = delete;
	VertexArray(VertexArray&& other);
	VertexArray& operator=(const VertexArray& other) = delete;
	VertexArray& operator=(VertexArray&& other);
	void bind() const;
	void unbind() const;
	inline auto getCount() const
	{
		return this->ib.getCount();
	}
};

glw::VertexArray make_vao(const std::string& filename);
VertexArray& quad();
VertexArray& cube();

} /* namespace glw */

#endif /* GLW_ABSTRACTION_VERTEXARRAY_H_ */
