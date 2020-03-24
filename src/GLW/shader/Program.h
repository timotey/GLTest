/*
 * Program.h
 *
 *  Created on: Feb 10, 2020
 *      Author: timotey
 */

#ifndef GLW_PROGRAM_H_
#define GLW_PROGRAM_H_

#include "../dependencies.h"
#include "Shader.h"
#include "../utils/utils.hpp"

namespace glw
{

class Program
{
private:
	unsigned int handle;
	mutable std::map<std::string, int> uniforms;
public:
	template <typename ... Args>
	Program(Args &&... args)
			: handle(glw::utils::glcall(__LINE__, __FILE__, glCreateProgram))
	{
		//	glw::utils::pcall(__LINE__, __FILE__, glAttachShader, this->handle, size_t(first));
		this->make(std::forward<Args>(args)...);
	}
	virtual ~Program();
	Program(Program &&other);
	Program& operator=(Program &&other);
	operator bool() const;
	operator size_t() const;
	void bind() const;
	void unbind() const;
	template <size_t count, typename T>
	void setUniform(const std::string name,
	        const glm::vec<count, T> value) const;
	template <size_t x, size_t y, typename T>
	void setUniformMatrix(const std::string name,
	        const glm::mat<y, x, T> value) const;
private:
	unsigned int getUniformLocation(std::string) const;
	void make(glw::Shader &&s)
	{
		int result;
		glw::utils::glcall(__LINE__, __FILE__, glAttachShader, this->handle,
		        size_t(s));
		glw::utils::glcall(__LINE__, __FILE__, glLinkProgram, this->handle);
		glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
		GL_LINK_STATUS, &result);
		if (!result)
		{
			int len = 0;
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
			GL_INFO_LOG_LENGTH, &len);
			char *message = reinterpret_cast<char*>(alloca(len * sizeof(char)));
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramInfoLog,
			        this->handle, len, &len, message);
			std::cout << message << std::endl;
		}
		glw::utils::glcall(__LINE__, __FILE__, glValidateProgram, this->handle);
		glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
		GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			int len = 0;
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
			GL_INFO_LOG_LENGTH, &len);
			char *message = reinterpret_cast<char*>(alloca(len * sizeof(char)));
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramInfoLog,
			        this->handle, len, &len, message);
			std::cout << message << std::endl;
		}

		s.~Shader();
	}

	template <typename ... Args>
	void make(glw::Shader &&s, Args ... args)
	{
		glw::utils::glcall(__LINE__, __FILE__, glAttachShader, this->handle,
		        size_t(s));
		this->make(std::forward<Args>(args)...);
		s.~Shader();
	}

};

} /* namespace glw */

#endif /* GLW_PROGRAM_H_ */
