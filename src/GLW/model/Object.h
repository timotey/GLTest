/*
 * Object.h
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_OBJECT_H_
#define GLW_MODEL_OBJECT_H_

#include "Model.h"
#include "Movable.h"

namespace glw
{

class Object : virtual public Movable
{
public:
	Object(glm::vec3 position = glm::vec3(), glm::quat rotation = glm::quat());
	virtual ~Object() = default;
	Object(const Object &other) = default;
	Object(Object &&other) = default;
	Object& operator=(const Object &other) = default;
	Object& operator=(Object &&other) = default;
};

} /* namespace glw */

#endif /* GLW_MODEL_OBJECT_H_ */
