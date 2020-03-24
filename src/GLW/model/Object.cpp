/*
 * Object.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#include "Object.h"

namespace glw
{

glw::Object::Object(glm::vec3 position, glm::quat rotation)
		: Movable(position, rotation)
{

}

} /* namespace glw */

