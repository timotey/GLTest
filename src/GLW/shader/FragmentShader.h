/*
 * FragmentShader.h
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_SHADER_FRAGMENTSHADER_H_
#define GLW_SHADER_FRAGMENTSHADER_H_

#include "Shader.h"

namespace glw
{

class FragmentShader: public Shader
{
public:
	FragmentShader(const char *src);
	virtual ~FragmentShader() = default;
	FragmentShader(const FragmentShader &other) = delete;
	FragmentShader(FragmentShader &&other) = default;
	FragmentShader& operator=(const FragmentShader &other) = delete;
	FragmentShader& operator=(FragmentShader &&other) = default;
};

} /* namespace glw */

#endif /* GLW_SHADER_FRAGMENTSHADER_H_ */
