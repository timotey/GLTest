/*
 * Camera.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: timotey
 */

#include "Camera.h"

namespace glw
{

glm::mat4 glw::Camera::getViewMat() const
{
	glm::mat4 ret(1);
	ret *= glm::mat4_cast(-this->rotation);
	ret = glm::translate(ret, -this->translation);
	ret = glm::scale(ret, this->scale);
	return ret;
}

} /* namespace glw */
