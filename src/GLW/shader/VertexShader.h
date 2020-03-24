/*
 * VertexShader.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_SHADER_VERTEXSHADER_H_
#define GLW_SHADER_VERTEXSHADER_H_

#include "Shader.h"

namespace glw
{

class VertexShader: public Shader
{
public:
	VertexShader(const char *src);
	virtual ~VertexShader() = default;
	VertexShader(const VertexShader &other) = delete;
	VertexShader(VertexShader &&other) = default;
	VertexShader& operator=(const VertexShader &other) = delete;
	VertexShader& operator=(VertexShader &&other) = default;
};

} /* namespace glw */

#endif /* GLW_SHADER_VERTEXSHADER_H_ */
