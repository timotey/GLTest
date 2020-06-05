/*
 * Renderer.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: timotey
 */

#include "Renderer.h"
#include "programcollection.h"

namespace glw
{

Renderer::Renderer(glm::uvec2 _res) :
		res(_res),
		f(_res)
{
}

void Renderer::draw(GLFWwindow* w, Scene& s, const Camera& c)
{
	int ress[4];
	glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv, GL_VIEWPORT, ress);
	this->f.bind(glw::Framebuffer::draw);
	glViewport(0, 0, this->res.x, this->res.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glDisable(GL_BLEND);

	for (auto& [key, model] : s.models)
	{

		std::vector<glw::Object*>& ob = s.obj.at(key);

		model->drawBatched(this->f, s, c,
		        const_cast<const glw::Object**>(ob.data()), ob.size());
//		for (auto& v : ob)
//			model->draw(f, s, c, *v);
	}

	this->f.unbind();
	glViewport(ress[0], ress[1], ress[2], ress[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glDepthMask(GL_FALSE);
	glw::shader::Cubemap().bind();
	glw::shader::Cubemap().setUniform<1, int>("u_c", glm::ivec1(1));
	s.cubemap.bind(1);
	glw::shader::Cubemap().setUniformMatrix<4, 4, float>("u_V",
	        glm::mat4(glm::mat3(c.getViewMat())));
	glw::shader::Cubemap().setUniformMatrix<4, 4, float>("u_P",
	        c.getCameraMat());
	glw::cube().bind();
	s.cubemap.bind(4);
	glw::utils::glcall(__LINE__, __FILE__, glDrawElements, GL_TRIANGLES,
	        glw::cube().getCount(), GL_UNSIGNED_INT, nullptr);
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);

	this->f.bind(Framebuffer::read);
	glw::shader::Post_process().bind();
	glw::quad().bind();
	glw::shader::Post_process().setUniform<1, int>("u_norm", glm::ivec1(2));
	glw::shader::Post_process().setUniform<1, int>("u_pos", glm::ivec1(1));
	glw::shader::Post_process().setUniform<1, int>("u_alb", glm::ivec1(0));
	glw::shader::Post_process().setUniform<1, int>("u_c", glm::ivec1(4));
	glw::shader::Post_process().setUniformMatrix<4, 4, float>("u_V",
	        glm::mat4(glm::mat3(c.getViewMat())));
	glw::utils::glcall(__LINE__, __FILE__, glDrawArrays, GL_TRIANGLE_STRIP, 0,
	        4);

	glw::quad().unbind();
}

} /* namespace glw */
