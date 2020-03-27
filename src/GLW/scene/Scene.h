/*
 * Scene.h
 *
 *  Created on: Feb 24, 2020
 *      Author: timotey
 */

#ifndef GLW_SCENE_SCENE_H_
#define GLW_SCENE_SCENE_H_

#include "../dependencies.h"
#include "../mesh/Mesh.h"
#include "../model/Object.h"
#include "../shader/Program.h"

namespace glw
{

//class Renderer;

class Scene
{
private:
	friend class Renderer;
	struct Targets
	{
		std::shared_ptr<glw::Program> prog;
		std::shared_ptr<glw::Mesh> mesh;
		std::vector<std::shared_ptr<glw::Object>> obj;
		Targets(std::shared_ptr<glw::Program> _prog,
		        std::shared_ptr<glw::Mesh> _mesh,
		        std::vector<std::shared_ptr<glw::Object>> _obj)
				: prog(_prog), mesh(_mesh), obj(_obj)
		{
		}
	};

	std::map<const std::string, std::weak_ptr<glw::Mesh>> models;
	std::map<const std::string, std::weak_ptr<glw::Program>> shader;
	std::multimap<const std::string, std::weak_ptr<glw::Object>> obj;
protected:
	std::vector<Targets> genTargets() const;
public:
	Scene() = default;
	virtual ~Scene() = default;
	Scene(const Scene& other) = default;
	Scene(Scene&& other) = default;
	Scene& operator=(const Scene& other) = default;
	Scene& operator=(Scene&& other) = default;
	void push(const std::string& label, const std::shared_ptr<Object> val);
	void push(const std::string& label, const std::shared_ptr<glw::Mesh> val);
	void push(const std::string& label,
	        const std::shared_ptr<glw::Program> val);
	void push(const std::string& label, const std::weak_ptr<Object> val);
	void push(const std::string& label, const std::weak_ptr<glw::Mesh> val);
	void push(const std::string& label, const std::weak_ptr<glw::Program> val);
	void pop(const std::string& label);
};

} /* namespace glw */

#endif /* GLW_SCENE_SCENE_H_ */
