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

class Mesh
{
private:
	IndexBuffer ib;
	VertexArray vao;
	Material mat;
public:
	std::array<Texture, 32> textures;
	Mesh(IndexBuffer&& _ib, VertexArray&& _vao, const Material& _mat)
			: ib(std::move(_ib)), vao(std::move(_vao)), mat(_mat)
	{
	}
	virtual ~Mesh() = default;
	Mesh(const Mesh& other) = delete;
	Mesh(Mesh&& other)
			:
			        ib(std::move(other.ib)),
			        vao(std::move(other.vao)),
			        mat(std::move(other.mat))
	{
	}
	Mesh& operator=(const Mesh& other) = delete;
	Mesh& operator=(Mesh&& other)
	{
		this->ib.operator =(std::move(other.ib));
		this->vao.operator =(std::move(other.vao));
		this->mat.operator =(std::move(other.mat));
		return *this;
	}
	void bind(const Program& shader) const
	{
		this->mat.bind(shader);
		this->vao.bind();
		this->ib.bind();
		for (unsigned int i = 0; i < 32; i++)
			this->textures[i].bind(i);
	}
	unsigned count() const
	{
		return this->ib.getCount();
	}
};

Mesh make_Mesh(const std::string&);

} /* namespace glw */

#endif /* GLW_MODEL_MESH_H_ */
