/*
 * OrthoCamera.cpp
 *
 *  Created on: Feb 17, 2020
 *      Author: timotey
 */

#include "OrthoCamera.h"

namespace glw
{

void glw::OrthoCamera::setCameraMat()
{
	float scalex = std::max(this->aspectRatio, 1.0f), scaley = std::max(
	        1 / this->aspectRatio, 1.0f);
	this->camMat = glm::ortho(scalex * this->scale.z, -scalex * this->scale.z,
	        -scaley * this->scale.z, scaley * this->scale.z);
}

} /* namespace glw */
