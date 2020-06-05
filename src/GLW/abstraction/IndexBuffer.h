/*
 * IndexBuffer.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_ABSTRACTION_INDEXBUFFER_H_
#define GLW_ABSTRACTION_INDEXBUFFER_H_

#include "../utils/utils.hpp"

namespace glw
{

class IndexBuffer
{
private:
	unsigned int handle = 0;
	size_t count = 0;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, const size_t count);
	virtual ~IndexBuffer();
	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer(IndexBuffer&& other);
	IndexBuffer& operator=(const IndexBuffer& other) = delete;
	IndexBuffer& operator=(IndexBuffer&& other);
	void setData(const unsigned int* data, const size_t count);
	virtual void bind() const;
	void unbind() const;
	inline size_t getCount() const
	{
		return this->count;
	}
};

} /* namespace glw */

#endif /* GLW_ABSTRACTION_INDEXBUFFER_H_ */
