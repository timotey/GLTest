/*
 * Shader.h
 *
 *  Created on: Feb 10, 2020
 *      Author: timotey
 */

#ifndef GLW_SHADER_H_
#define GLW_SHADER_H_

#include "../dependencies.h"
#include "../utils/utils.hpp"

namespace glw
{

class Shader
{
private:
	const size_t handle = 0;
public:
	Shader(const char * src, GLenum type);
	virtual ~Shader();
	Shader(const Shader &other) = delete;
	Shader(Shader &&other) = default;
	Shader& operator=(const Shader &other) = delete;
	Shader& operator=(Shader &&other) = default;
	operator bool () const;
	operator size_t () const;
};

} /* namespace glw */

#endif /* GLW_SHADER_H_ */
