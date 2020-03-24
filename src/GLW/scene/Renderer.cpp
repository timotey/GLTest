/*
 * Renderer.cpp
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#include "../scene/Renderer.h"

namespace glw
{

//void Renderer::render()
//{
//	std::vector<std::string> names;
//	names.reserve(this->models.size());
//	for (auto &val : this->models)
//		names.push_back(val.first);	//copy indices to a vector
//
//	std::remove_if(names.begin(), names.end(), [this](std::string &s)
//	{	return 0==obj.count(s);});	//filter for models with no objects
//
//	this->shader->setUniform<3, float>("u_LightPos", glm::vec3(0, 3, 3));
//	this->shader->setUniform<3, float>("u_CameraPos",
//	        this->cam().getTranslation());
//
//	for (auto &val : names)
//	{
//		std::vector<std::tuple<glm::fmat4, glm::fmat4>> transforms;
//		transforms.resize(this->obj.count(val));
//		std::transform(this->obj.lower_bound(val), this->obj.upper_bound(val),
//		        transforms.begin(),
//		        [this](
//		                auto &o)
//		                {
//			                return std::make_tuple(this->cam().getCameraMat() * this->cam().getTransformMat() * o.second->getTransformMat(), o.second->getTransformMat());
//		                });	//find all object transforms
//
//		auto &model = *this->models.at(val).get();
//		model.bind(*this->shader.get());
//		this->shader->setUniform<1, int>("u_Tex0", glm::ivec1(0));
//		for (auto &transf : transforms)
//		{
//			this->shader->setUniformMatrix<4, 4>("MVP", std::get<0>(transf));
//			this->shader->setUniformMatrix<4, 4>("M", std::get<1>(transf));
//			glw::utils::glcall(__LINE__, __FILE__, glDrawElements, GL_TRIANGLES,
//			        model.getCount(), GL_UNSIGNED_INT, nullptr);
//		}
//	}
//}
//
//Renderer::Renderer(const Camera &cam, std::shared_ptr<Program> &prog)
//{
//	this->shader = prog;
//	this->camera = std::unique_ptr<Camera>(cam.self_clone());
//}
//
//void Renderer::push(std::string key, std::shared_ptr<Object> object)
//{
//	this->obj.insert(std::make_pair(key, object));
//}
//
//void Renderer::push(std::string key, std::shared_ptr<glw::Mesh> model)
//{
//	this->models.insert(std::make_pair(key, model));
//}
//
//void Renderer::pop(std::string key)
//{
//	this->obj.erase(key);
//	this->models.erase(key);
//}

glw::Renderer::Renderer(const Camera &cam, const std::weak_ptr<Scene> &sc)
{
	this->camera = std::unique_ptr<Camera>(cam.self_clone());
	this->scene = sc;
}

glw::Renderer::Renderer(const Camera &cam, const std::shared_ptr<Scene> &sc)
{
	this->camera = std::unique_ptr<Camera>(cam.self_clone());
	this->scene = sc;
}

glw::Renderer::Renderer(const Renderer &other)
{
	this->camera = std::unique_ptr<Camera>(other.camera->self_clone());
	this->scene = other.scene;
}

Renderer& glw::Renderer::operator =(const Renderer &other)
{
	this->camera = std::unique_ptr<Camera>(other.camera->self_clone());
	this->scene = other.scene;
	return *this;
}

void glw::Renderer::render()
{
	if (this->scene.expired())
		return;
	Scene &scene = *this->scene.lock().get();
	auto vp = this->camera->getCameraMat() * this->camera->getTransformMat();
	for (auto target : scene.genTargets())
	{
		target.prog->bind();
		target.prog->setUniform<3, float>("u_LightPos", glm::vec3(0, 3, 3));
		target.prog->setUniform<3, float>("u_CameraPos",
		        this->cam().getTranslation());
		target.mesh->bind(*target.prog.get());
		for (auto &object : target.obj)
		{
			target.prog->setUniformMatrix<4, 4>("MVP",
			        vp * object->getTransformMat());
			target.prog->setUniformMatrix<4, 4>("M", object->getTransformMat());
			glw::utils::glcall(__LINE__, __FILE__, glDrawElements, GL_TRIANGLES,
			        target.mesh->getCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

} /* namespace glw */

