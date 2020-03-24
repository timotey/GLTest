/*
 * Scene.cpp
 *
 *  Created on: Feb 24, 2020
 *      Author: timotey
 */

#include "../scene/Scene.h"

namespace glw
{

std::vector<Scene::Targets> Scene::genTargets() const
{
	std::vector<std::string> names;
	std::vector<Scene::Targets> result;
	std::transform(this->models.begin(), this->models.end(),
	        std::back_inserter(names),
	        [](
	                const std::pair<const std::string, std::weak_ptr<Mesh>> &in) -> std::string
	                {	return in.first;});

	std::remove_if(names.begin(), names.end(),
	        [this](
	                const std::string &in) -> bool
	                {	return !this->obj.count(in) ||
		                !this->shader.count(in) ||
		                this->models.at(in).expired() ||
		                this->shader.at(in).expired() ||
		                this->obj.upper_bound(in) == std::find_if_not(this->obj.lower_bound(in), this->obj.upper_bound(in),
				                [](std::pair<const std::string, const std::weak_ptr<Object>> in)
				                {	return in.second.expired();});});

	std::transform(names.begin(), names.end(), std::back_inserter(result),
	        [this](
	                const std::string &in)
	                {	std::vector<std::shared_ptr<Object>> temp;
		                std::transform(this->obj.lower_bound(in), this->obj.upper_bound(in), std::back_inserter(temp),
				                [](const std::pair<const std::string, std::weak_ptr<Object>> &in)
				                {	return in.second.lock();});

		                return Scene::Targets(shader.at(in).lock(), models.at(in).lock(), temp);});
	return result;
}

void Scene::push(const std::string &label, const std::shared_ptr<Object> val)
{
	this->obj.insert(std::pair<const std::string, std::weak_ptr<Object>>
	{ label, std::weak_ptr<Object>(val) });
}

void Scene::push(const std::string &label, const std::shared_ptr<glw::Mesh> val)
{
	this->models.insert(std::pair<const std::string, std::weak_ptr<Mesh>>
	{ label, std::weak_ptr<Mesh>(val) });
}

void Scene::push(const std::string &label,
        const std::shared_ptr<glw::Program> val)
{
	this->shader.insert(std::pair<const std::string, std::weak_ptr<Program>>
	{ label, std::weak_ptr<Program>(val) });
}

void Scene::push(const std::string &label, const std::weak_ptr<Object> val)
{
	this->obj.insert(
	{ label, val });
}

void Scene::push(const std::string &label, const std::weak_ptr<glw::Mesh> val)
{
	this->models.insert(
	{ label, val });
}

void Scene::push(const std::string &label,
        const std::weak_ptr<glw::Program> val)
{
	this->shader.insert(std::pair<const std::string, std::weak_ptr<Program>>
	{ label, val });
}

void Scene::pop(const std::string &label)
{
	this->shader.erase(label);
	this->models.erase(label);
	this->obj.erase(label);
}

} /* namespace glw */
