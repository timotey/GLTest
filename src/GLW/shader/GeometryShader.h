/*
 * GeometryShader.h
 *
 *  Created on: Feb 19, 2020
 *      Author: timotey
 */

#ifndef GLW_SHADER_GEOMETRYSHADER_H_
#define GLW_SHADER_GEOMETRYSHADER_H_

#include "Shader.h"

namespace glw
{

class GeometryShader: public Shader
{
public:
	GeometryShader(const char *src);
	virtual ~GeometryShader() = default;
	GeometryShader(const GeometryShader &other) = delete;
	GeometryShader(GeometryShader &&other) = default;
	GeometryShader& operator=(const GeometryShader &other) = delete;
	GeometryShader& operator=(GeometryShader &&other) = default;
};

} /* namespace glw */

#endif /* GLW_SHADER_GEOMETRYSHADER_H_ */
