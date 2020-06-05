/*
 * Mesh.h
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#define GLW_MODEL_MESH_H_
#ifndef GLW_MODEL_MESH_H_
#define GLW_MODEL_MESH_H_

#include "../abstraction/IndexBuffer.h"
#include "../abstraction/VertexArray.h"
#include "../abstraction/Material.h"
#include "../abstraction/Texture.h"

namespace glw
{

class Mesh
{
private:
	IndexBuffer ib;
	VertexArray vao;
	Material mat;
public:
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
	}
	unsigned count() const
	{
		return this->ib.getCount();
	}
};

Mesh make_Mesh(const std::string&);

} /* namespace glw */

#endif /* GLW_MODEL_MESH_H_ */
