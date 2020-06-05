/*
 * basic_Model.h
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_BASIC_MODEL_H_
#define GLW_MODEL_BASIC_MODEL_H_

#include "../abstraction/GBuffer.h"
#include "../abstraction/VertexArray.h"
#include "Movable.h"
#include "Camera.h"
#include "../abstraction/Texture.h"

namespace glw
{

class Scene;

class Object: virtual public Movable
{
public:
	Object(glm::vec3 position = glm::vec3(), glm::quat rotation = glm::quat());
	virtual ~Object() = default;
	Object(const Object& other) = default;
	Object(Object&& other) = default;
	Object& operator=(const Object& other) = default;
	Object& operator=(Object&& other) = default;
};

class Camera;

class basic_Model
{
private:
public:
	virtual ~basic_Model() = default;
	basic_Model(const basic_Model& other) = delete;
	basic_Model(basic_Model&& other) = default;
	basic_Model() = default;
	basic_Model& operator=(const basic_Model& other) = delete;
	basic_Model& operator=(basic_Model&& other) = default;
	virtual void draw(GBuffer&, const Scene&, const Camera&, const Object&) = 0;
	virtual void drawBatched(GBuffer&, const Scene&, const Camera&,
	        const Object** const, size_t size) = 0; //TODO: make work with c++ ranges
//	virtual void drawShadow(GBuffer&, const Scene&, const Camera&,
//	        const Object&) = 0;
//	virtual void drawShadowBatched(GBuffer&, const Scene&, const Camera&,
//	        const Object** const, size_t size) = 0; //TODO: make work with c++ ranges
};

//basic_Model make_Model(const std::string& filename, glw::Program&& s,
//        glw::Texture&& t);
//basic_Model make_Model(const std::string& filename,
//        std::shared_ptr<Program> shader, glw::Texture&& t);

} /* namespace glw */

#endif /* GLW_MODEL_BASIC_MODEL_H_ */
