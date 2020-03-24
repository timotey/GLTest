/*
 * Camera.cpp
 *
 *  Created on: Feb 16, 2020
 *      Author: timotey
 */

#include "Camera.h"

namespace glw
{

glm::fmat4 Camera::getTransformMat() const
{
	glm::mat4 ret(1);
	ret *= glm::mat4_cast(-this->rotation);
	ret = glm::translate(ret, -this->translation);
//	ret = glm::scale(ret, this->scale);
	return ret;
}

} /* namespace glw */
