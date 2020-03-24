/*
 * PerspectiveCamera.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: timotey
 */

#include "PerspectiveCamera.h"

namespace glw
{

glm::fmat4 glw::PerspectiveCamera::getCameraMat() const
{
	return glm::perspective(this->fov*2, this->aspectRatio, this->near, this->far);
}

glw::Camera* glw::PerspectiveCamera::self_clone() const
{
	return new PerspectiveCamera(*this);
}

} /* namespace glw */

