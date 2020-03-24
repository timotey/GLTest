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
	PerspectiveCamera(){}
	PerspectiveCamera(const float _fov) : fov(_fov){}
	PerspectiveCamera(const float _fov, float _near, float _far) : fov(_fov), near(_near), far(_far){}
	virtual ~PerspectiveCamera() = default;
	PerspectiveCamera(const PerspectiveCamera &other) = default;
	PerspectiveCamera(PerspectiveCamera &&other) = default;
	PerspectiveCamera& operator=(const PerspectiveCamera &other) = default;
	PerspectiveCamera& operator=(PerspectiveCamera &&other) = default;

	virtual glm::fmat4 getCameraMat() const;

private:
	float fov = 45.0f/M_PI;
	float near = 1.0f, far = 100.0f;
	virtual glw::Camera* self_clone() const;
};

} /* namespace glw */

#endif /* GLW_CAMERA_PERSPECTIVECAMERA_H_ */
