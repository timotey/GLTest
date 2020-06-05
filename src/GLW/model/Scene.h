/*
 * Scene.h
 *
 *  Created on: Feb 24, 2020
 *      Author: timotey
 */

#ifndef GLW_SCENE_SCENE_H_
#define GLW_SCENE_SCENE_H_

#include "../dependencies.h"
#include "../model/Model.h"
#include "../Program.h"

namespace glw
{

//class Renderer;

class Scene
{
private:
	friend class Renderer;
	std::map<const std::string, std::unique_ptr<glw::basic_Model>> models;

	std::map<const std::string, std::vector<glw::Object*>> obj;
	glw::Cubemap cubemap;
protected:
public:
	Scene(glw::Cubemap&& _cubemap) :
			cubemap(std::move(_cubemap))
	{
	}
	virtual ~Scene() = default;
	Scene(const Scene& other) = default;
	Scene(Scene&& other) = default;
	Scene& operator=(const Scene& other) = default;
	Scene& operator=(Scene&& other) = default;
	void push(const std::string& label, Object* val);
	void push(const std::string& label,
	        std::unique_ptr<glw::basic_Model>&& val);
	void pop(const std::string& label);
	void draw(const Camera& c);
};

} /* namespace glw */

#endif /* GLW_SCENE_SCENE_H_ */
