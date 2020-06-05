/*
 * Scene.cpp
 *
 *  Created on: Feb 24, 2020
 *      Author: timotey
 */

#include "Scene.h"

namespace glw
{

void Scene::push(const std::string& label, Object* val)
{
	this->obj[label].push_back(val);
}

void Scene::push(const std::string& label,
        std::unique_ptr<glw::basic_Model>&& val)
{
	this->models.insert(
	        std::pair<const std::string, std::unique_ptr<glw::basic_Model>>{
	                label, std::move(val)});
}

void Scene::pop(const std::string& label)
{
	this->models.erase(label);
	this->obj.erase(label);
}

} /* namespace glw */
