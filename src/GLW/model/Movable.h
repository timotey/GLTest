/*
 * Movable.h
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_MOVABLE_H_
#define GLW_MODEL_MOVABLE_H_

#include "../dependencies.h"

namespace glw
{

class Movable
{
protected:
	glm::vec3 translation = glm::vec3();
	glm::quat rotation = glm::quat();
	glm::vec3 scale = glm::vec3(1, 1, 1);
public:
	Movable(glm::vec3 position = glm::vec3(), glm::quat rotation = glm::quat(),
	        glm::vec3 scale = glm::vec3(1, 1, 1));
	virtual ~Movable() = default;
	Movable(const Movable &other) = default;
	Movable(Movable &&other) = default;
	Movable& operator=(const Movable &other) = default;
	Movable& operator=(Movable &&other) = default;
	virtual glm::fmat4 getTransformMat() const;

	const glm::fvec3& getTranslation() const;
	void setTranslation(const glm::vec3 &position);
	const glm::fquat& getRotation() const;
	void setRotation(const glm::quat &rotation);
	const glm::fvec3& getScale() const;
	void setScale(const glm::vec3 &scale);
	void translate(const glm::vec3 &position);
	void rotate(const glm::quat &rotation);
};

} /* namespace glw */

#endif /* GLW_MODEL_MOVABLE_H_ */
