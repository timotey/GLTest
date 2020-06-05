/*
 * PerspectiveCamera.h
 *
 *  Created on: Feb 18, 2020
 *      Author: timotey
 */

#ifndef GLW_CAMERA_PERSPECTIVECAMERA_H_
#define GLW_CAMERA_PERSPECTIVECAMERA_H_

#include "Camera.h"

namespace glw
{

class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera()
	{
	}
	PerspectiveCamera(float const _fov) :
			fov(_fov)
	{
	}
	PerspectiveCamera(float const _fov, float _near, float _far) :
			fov(_fov),
			near(_near),
			far(_far)
	{
	}
	virtual ~PerspectiveCamera() = default;
	PerspectiveCamera(PerspectiveCamera const& other) = default;
	PerspectiveCamera(PerspectiveCamera&& other) = default;
	PerspectiveCamera& operator=(PerspectiveCamera const& other) = default;
	PerspectiveCamera& operator=(PerspectiveCamera&& other) = default;
private:
	float fov = 45.0f / 3.141593f;
	float near = 0.0001f, far = 10000.0f;
	glw::Camera* self_clone() const override;
protected:
	void setCameraMat() override;
};

} /* namespace glw */

#endif /* GLW_CAMERA_PERSPECTIVECAMERA_H_ */
