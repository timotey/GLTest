/*
 * Renderer.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_RENDERER_H_
#define GLW_RENDERER_H_

#include "Scene.h"
#include "../dependencies.h"
#include "../mesh/Mesh.h"
#include "../camera/Camera.h"
#include "../model/Object.h"
#include "../shader/Program.h"

namespace glw
{

//class Renderer
//{
//private:
//	std::map<std::string, std::shared_ptr<glw::Mesh>>	models;
//	std::multimap<std::string, std::shared_ptr<glw::Object>>	obj;
//	std::shared_ptr<glw::Program>	shader;
//	std::unique_ptr<Camera>	camera;
//public:
//	void render();
//	explicit Renderer(const Camera &cam, std::shared_ptr<Program> &prog);
//	virtual ~Renderer() = default;
//	Renderer(const Renderer &other) = delete;
//	Renderer(Renderer &&other) = default;
//	Renderer& operator=(const Renderer &other) = delete;
//	Renderer& operator=(Renderer &&other) = default;
//	void push(std::string, std::shared_ptr<Object>);
//	void push(std::string, std::shared_ptr<glw::Mesh>);
//	void pop(std::string);
//	Camera &cam()
//	{
//		return *this->camera.get();
//	}
//};

class Renderer
{
private:
	std::weak_ptr<Scene> scene;
	std::unique_ptr<Camera> camera;
public:
	explicit Renderer(const Camera &cam, const std::weak_ptr<Scene> &sc);
	explicit Renderer(const Camera &cam, const std::shared_ptr<Scene> &sc);
	virtual ~Renderer() = default;
	Renderer(const Renderer &other);
	Renderer(Renderer &&other) = default;
	Renderer& operator=(const Renderer &other);
	Renderer& operator=(Renderer &&other) = default;
	virtual void render();

	Camera& cam()
	{
		return *this->camera.get();
	}
};

} /* namespace glw */

#endif /* GLW_RENDERER_H_ */
