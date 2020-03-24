/*
 * OrthoCamera.cpp
 *
 *  Created on: Feb 17, 2020
 *      Author: timotey
 */

#include "OrthoCamera.h"

namespace glw
{

glm::fmat4 glw::OrthoCamera::getCameraMat() const
{
    float scalex = std::max(this->aspectRatio, 1.0f), scaley = std::max(1/this->aspectRatio, 1.0f);
	auto debug = glm::ortho(scalex*this->scale.z, -scalex*this->scale.z, -scaley*this->scale.z, scaley*this->scale.z);
	return debug;
}

} /* namespace glw */
