/*
 * Movable.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#include "Movable.h"

namespace glw
{

glw::Movable::Movable(glm::vec3 position, glm::quat rotation, glm::vec3 scale) :translation(position), rotation(rotation), scale(scale)
{

}

glm::mat4 glw::Movable::getTransformMat() const
{
	glm::mat4 ret(1);
	ret = glm::translate(ret, this->translation);
	ret = glm::scale(ret, this->scale);
	ret *= glm::mat4_cast(this->rotation);
	return ret;
}

const glm::fvec3& glw::Movable::getTranslation() const
{
	return translation;
}

void glw::Movable::setTranslation(const glm::vec3 &position)
{
	this->translation = position;
}

const glm::fquat& glw::Movable::getRotation() const
{
	return rotation;
}

void glw::Movable::setRotation(const glm::quat &rotation)
{
	this->rotation = rotation;
}

const glm::fvec3& glw::Movable::getScale() const
{
	return scale;
}

void glw::Movable::setScale(const glm::vec3 &scale)
{
	this->scale = scale;
}

void Movable::translate(const glm::vec3 &position)
{
	this->translation+=position;
}

void Movable::rotate(const glm::quat &rotation)
{
	this->rotation *= rotation;
}

} /* namespace glw */
