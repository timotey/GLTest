/*
 * Light.h
 *
 *  Created on: May 17, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_LIGHT_H_
#define GLW_MODEL_LIGHT_H_

#include "Camera.h"

namespace glw
{

///
///@brief base class for game lights
///

class Light: public Movable
{
protected:
	glm::mat4 projmat;
public:
	Light();
	virtual ~Light() = default;
	Light(Light const& other) = default;
	Light(Light&& other) = default;
	Light& operator=(Light const& other) = default;
	Light& operator=(Light&& other) = default;
	glm::fmat4 getViewMat() const
	{
		return -this->getTransformMat();
	}
	glm::fmat4 getLightMat() const
	{
		return this->projmat;
	}
protected:
private:
	virtual glw::Light* self_clone() const = 0;
};

class DirLight: public Light
{
protected:
	glm::mat4 projmat;
public:
	DirLight(float width, float height)
	{
		this->projmat = glm::ortho(width, -width, -height, height);
	}
	virtual ~DirLight() = default;
	DirLight(DirLight const& other) = default;
	DirLight(DirLight&& other) = default;
	DirLight& operator=(DirLight const& other) = default;
	DirLight& operator=(DirLight&& other) = default;
	glm::fmat4 getDirLightMat() const
	{
		return this->projmat;
	}
protected:
private:
	virtual glw::DirLight* self_clone() const
	{
		return new DirLight(*this);
	}
};

class CubeLight: public Light
{
protected:
	glm::mat4 projmat;
public:
	CubeLight(float near, float far)
	{
		this->projmat = glm::perspective(float(M_PI / 4.0f), 1.0f, near, far);
	}
	virtual ~CubeLight() = default;
	CubeLight(CubeLight const& other) = default;
	CubeLight(CubeLight&& other) = default;
	CubeLight& operator=(CubeLight const& other) = default;
	CubeLight& operator=(CubeLight&& other) = default;
	glm::fmat4 getCubeLightMat() const
	{
		return this->projmat;
	}
protected:
private:
	virtual glw::CubeLight* self_clone() const
	{
		return new CubeLight(*this);
	}
};

} /* namespace glw */

#endif /* GLW_MODEL_LIGHT_H_ */
