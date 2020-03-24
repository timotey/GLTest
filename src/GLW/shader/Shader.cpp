/*
 * Shader.cpp
 *
 *  Created on: Feb 10, 2020
 *      Author: timotey
 */

#include "Shader.h"

namespace glw
{

Shader::Shader(const char * src, GLenum type)
	:handle(glw::utils::glcall(__LINE__, __FILE__, glCreateShader, type))
{
	glw::utils::glcall(__LINE__, __FILE__, glShaderSource, this->handle, 1, &src, nullptr);
	glw::utils::glcall(__LINE__, __FILE__, glCompileShader, this->handle);

	int result;
	glw::utils::glcall(__LINE__, __FILE__, glGetShaderiv, this->handle, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		int len = 0;
		glw::utils::glcall(__LINE__, __FILE__, glGetShaderiv, this->handle, GL_INFO_LOG_LENGTH, &len);
		char* message = reinterpret_cast<char*>(alloca(len*sizeof(char)));
		glw::utils::glcall(__LINE__, __FILE__, glGetShaderInfoLog, this->handle, len, &len, message);
		std::cout << message << std::endl;;
	}
}

Shader::~Shader()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteShader, this->handle);
}

Shader::operator bool  () const
{
		GLint result;
		glw::utils::glcall(__LINE__, __FILE__, glGetShaderiv, this->handle, GL_COMPILE_STATUS, &result);
		return result;
}

Shader::operator size_t () const
{
	return this->handle;
}

} /* namespace glw */
