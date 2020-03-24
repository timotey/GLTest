/*
 * Camera.h
 *
 *  Created on: Feb 16, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_CAMERA_H_
#define GLW_MODEL_CAMERA_H_

#include "../model/Movable.h"

namespace glw
{

class Renderer;

class Camera: public virtual Movable
{
	friend class Renderer;
	virtual Camera* self_clone() const = 0;
protected:
	float aspectRatio;
public:
	Camera(float aspectRatio = 16.0f / 9.0f)
			: aspectRatio(aspectRatio)
	{
	}
	virtual ~Camera() = default;
	Camera(const Camera &other) = default;
	Camera(Camera &&other) = default;
	Camera& operator=(const Camera &other) = default;
	Camera& operator=(Camera &&other) = default;
	glm::fmat4 getTransformMat() const final;
	virtual glm::fmat4 getCameraMat() const = 0;

	float getAspectRatio() const
	{
		return aspectRatio;
	}

	void setAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
	}
};

} /* namespace glw */

#endif /* GLW_MODEL_CAMERA_H_ */
