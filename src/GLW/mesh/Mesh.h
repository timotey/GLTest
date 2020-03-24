/*
 * Mesh.h
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_MESH_H_
#define GLW_MODEL_MESH_H_

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Material.h"
#include "Texture.h"

namespace glw
{

class Mesh: virtual public IndexBuffer, VertexArray, Material
{
private:
public:
	std::array<Texture, 32> textures;
	Mesh(IndexBuffer &&ib, VertexArray &&vao, const Material &mat)
			:
			        IndexBuffer(std::move(static_cast<IndexBuffer&>(ib))),
			        VertexArray(std::move(static_cast<VertexArray&>(vao))),
			        Material(mat)
	{
	}
	virtual ~Mesh() = default;
	Mesh(const Mesh &other) = delete;
	Mesh(Mesh &&other)
			:
			        IndexBuffer(std::move(static_cast<IndexBuffer&>(other))),
			        VertexArray(std::move(static_cast<VertexArray&>(other))),
			        Material(std::move(static_cast<Material&>(other)))
	{
	}
	Mesh& operator=(const Mesh &other) = delete;
	Mesh& operator=(Mesh &&other)
	{
		this->IndexBuffer::operator =(
		        std::move(static_cast<IndexBuffer&>(other)));
		this->VertexArray::operator =(
		        std::move(static_cast<VertexArray&>(other)));
		this->Material::operator =(std::move(static_cast<Material&>(other)));
		return *this;
	}
	virtual void bind(const Program &shader) const override
	{
		this->Material::bind(shader);
		this->VertexArray::bind();
		this->IndexBuffer::bind();
		for (unsigned int i = 0; i < 32; i++)
			this->textures[i].bind(i);
	}
};

Mesh make_Mesh(const std::string&);

} /* namespace glw */

#endif /* GLW_MODEL_MESH_H_ */
