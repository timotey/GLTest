/*
 * PerspectiveCamera.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: timotey
 */

#include "PerspectiveCamera.h"

namespace glw
{

void glw::PerspectiveCamera::setCameraMat()
{
	this->camMat = glm::perspective(this->fov * 2, this->aspectRatio,
	        this->near, this->far);
}

glw::Camera* glw::PerspectiveCamera::self_clone() const
{
	return new PerspectiveCamera(*this);
}

} /* namespace glw */

