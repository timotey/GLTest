/*
 * Renderer.h
 *
 *  Created on: Apr 30, 2020
 *      Author: timotey
 */

#ifndef GLW_RENDERER_H_
#define GLW_RENDERER_H_

#include "model/Scene.h"

namespace glw
{

class Renderer
{
	glm::uvec2 res{640, 480};
	GBuffer f;
public:
	Renderer(glm::uvec2 res);
	virtual ~Renderer() = default;
	Renderer(const Renderer& other) = delete;
	Renderer(Renderer&& other) = default;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer& operator=(Renderer&& other) = default;
	virtual void draw(GLFWwindow* w, Scene& s, const Camera& c);

};

} /* namespace glw */

#endif /* GLW_RENDERER_H_ */
