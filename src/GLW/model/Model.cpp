/*
 * Model.cpp
 *
 *  Created on: May 9, 2020
 *      Author: timotey
 */

#include "Model.h"
#include "../programcollection.h"

namespace glw
{

Model::Model(VertexArray&& _vao, Texture2&& _tex) :
		tex(std::move(_tex)),
		vao(std::move(_vao))
{
	this->vao.vb.push_back(VertexBuffer(VertexBuffer::mode::dynamic_draw));
	this->vao.layout.push<float>(4, 1, 1);
	this->vao.layout.push<float>(4, 1, 1);
	this->vao.layout.push<float>(4, 1, 1);
	this->vao.layout.push<float>(4, 1, 1);
}

void Model::draw(GBuffer& f, const Scene&, const Camera& c, const Object& o)
{
	this->tex.bind(1);
	glw::shader::Basic().bind();
	auto transform = MatrixData(o.getTransformMat(), c.getViewMat());
	this->vao.vb[1].setData(&transform, sizeof(MatrixData));
	this->vao.bind();
	glw::shader::Basic().setUniformMatrix<4, 4, float>("P", c.getCameraMat());
	f.bind(glw::Framebuffer::draw);
	glw::utils::glcall(__LINE__, __FILE__, glDrawElements, GL_TRIANGLES,
	        this->vao.getCount(), GL_UNSIGNED_INT, nullptr);
}
//glw::Model::Model(Mesh &&va) : mesh(std::move(va))
//{
//}

void Model::drawBatched(GBuffer& f, const Scene& s, const Camera& c,
        const Object** const o, size_t size)
{
	this->data.reserve(std::max(size, this->data.capacity()));
	for (size_t i = 0; i < size; i++)
	{
		this->data.push_back({o[i]->getTransformMat(), c.getViewMat()});
	}
	this->vao.vb[1].setData(this->data.data(),
	        this->data.size() * sizeof(MatrixData));
	this->vao.bind();
	glw::shader::Basic().bind();
	this->tex.bind(1);
	glw::shader::Basic().setUniformMatrix<4, 4, float>("P", c.getCameraMat());
	glw::shader::Basic().setUniform<1, int>("u_Tex0", glm::ivec1{1});
	f.bind(glw::Framebuffer::draw);
	glw::utils::glcall(__LINE__, __FILE__, glDrawElementsInstanced,
	GL_TRIANGLES, this->vao.getCount(), GL_UNSIGNED_INT, nullptr, size);
	this->vao.vb[1].setData(nullptr, this->data.size() * sizeof(MatrixData));
	this->data.clear();
}

} /* namespace glw */
