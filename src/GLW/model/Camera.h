/*
 * Camera.h
 *
 *  Created on: Apr 23, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_CAMERA_H_
#define GLW_MODEL_CAMERA_H_

#include "Movable.h"

namespace glw
{

class Camera: public virtual Movable
{
	friend class Renderer;
	virtual Camera* self_clone() const = 0;
protected:
	glm::mat4 camMat;
	float aspectRatio;
	virtual void setCameraMat() = 0;
	void _cameramatupdate()
	{
		this->setCameraMat();
	}
public:
	Camera(float _aspectRatio = 16.0f / 9.0f) :
			aspectRatio(_aspectRatio)
	{
	}
	virtual ~Camera() = default;
	Camera(const Camera& other) = default;
	Camera(Camera&& other) = default;
	Camera& operator=(const Camera& other) = default;
	Camera& operator=(Camera&& other) = default;
	glm::fmat4 getViewMat() const;
	virtual glm::fmat4 getCameraMat() const
	{
		return this->camMat;
	}

	float getAspectRatio() const
	{
		return aspectRatio;
	}

	void setAspectRatio(float _aspectRatio)
	{
		this->aspectRatio = _aspectRatio;
		this->setCameraMat();
	}
};

} /* namespace glw */

#endif /* GLW_MODEL_CAMERA_H_ */
