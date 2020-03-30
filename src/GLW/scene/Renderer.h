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

class Renderer
{
private:
	std::weak_ptr<Scene> scene;
	std::unique_ptr<Camera> camera;
public:
	explicit Renderer(const Camera& cam, const std::weak_ptr<Scene>& sc);
	explicit Renderer(const Camera& cam, const std::shared_ptr<Scene>& sc);
	virtual ~Renderer() = default;
	Renderer(const Renderer& other);
	Renderer(Renderer&& other) = default;
	Renderer& operator=(const Renderer& other);
	Renderer& operator=(Renderer&& other) = default;
	virtual void render();

	Camera& cam()
	{
		return *this->camera.get();
	}
};

} /* namespace glw */

#endif /* GLW_RENDERER_H_ */
