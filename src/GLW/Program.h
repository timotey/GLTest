/*
 * Program.h
 *
 *  Created on: Feb 10, 2020
 *      Author: timotey
 */

#ifndef GLW_PROGRAM_H_
#define GLW_PROGRAM_H_

#include "dependencies.h"
#include "utils/utils.hpp"

#include <alloca.h>

namespace glw
{

class Shader
{
private:
	const size_t handle = 0;
public:
	Shader(const char* src, GLenum type);
	virtual ~Shader();
	Shader(const Shader& other) = delete;
	Shader(Shader&& other) = default;
	Shader& operator=(const Shader& other) = delete;
	Shader& operator=(Shader&& other) = default;
	operator bool() const;
	operator size_t() const;
};

class VertexShader: public Shader
{
public:
	VertexShader(const char* src);
	virtual ~VertexShader() = default;
	VertexShader(const VertexShader& other) = delete;
	VertexShader(VertexShader&& other) = default;
	VertexShader& operator=(const VertexShader& other) = delete;
	VertexShader& operator=(VertexShader&& other) = default;
};

class GeometryShader: public Shader
{
public:
	GeometryShader(const char* src);
	virtual ~GeometryShader() = default;
	GeometryShader(const GeometryShader& other) = delete;
	GeometryShader(GeometryShader&& other) = default;
	GeometryShader& operator=(const GeometryShader& other) = delete;
	GeometryShader& operator=(GeometryShader&& other) = default;
};

class FragmentShader: public Shader
{
public:
	FragmentShader(const char* src);
	virtual ~FragmentShader() = default;
	FragmentShader(const FragmentShader& other) = delete;
	FragmentShader(FragmentShader&& other) = default;
	FragmentShader& operator=(const FragmentShader& other) = delete;
	FragmentShader& operator=(FragmentShader&& other) = default;
};

class Program
{
private:
	unsigned int handle;
	mutable std::map<std::string, int> uniforms;
	struct fold_functor
	{
		unsigned int& handle;
		fold_functor operator +(glw::Shader&& s)
		{
			return *this;
		}
	};
public:
	template <typename ... Args>
	Program(Args&& ... args) :
			handle(glw::utils::glcall(__LINE__, __FILE__, glCreateProgram))
	{
		(glw::utils::glcall(__LINE__, __FILE__, glAttachShader, this->handle,
						size_t(args)), ...);

		int result;
		glw::utils::glcall(__LINE__, __FILE__, glLinkProgram, this->handle);
		glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
		GL_LINK_STATUS, &result);
		if (!result)
		{
			int len = 0;
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
			GL_INFO_LOG_LENGTH, &len);
			char* message = reinterpret_cast<char*>(alloca(
			        size_t(len + 1) * sizeof(char)));
			message[0] = 0;
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramInfoLog,
			        this->handle, len, &len, message);
			std::cout << message;
		}
		glw::utils::glcall(__LINE__, __FILE__, glValidateProgram, this->handle);
		glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
		GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			int len = 0;
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramiv, this->handle,
			GL_INFO_LOG_LENGTH, &len);
			char* message = reinterpret_cast<char*>(alloca(
			        size_t(len + 1) * sizeof(char)));
			message[0] = 0;
			glw::utils::glcall(__LINE__, __FILE__, glGetProgramInfoLog,
			        this->handle, len, &len, message);
			std::cout << message;
		}

	}
	virtual ~Program();
	Program(Program&& other);
	Program& operator=(Program&& other);
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
	unsigned int getUniformLocation(const std::string&) const;
};

} /* namespace glw */

#endif /* GLW_PROGRAM_H_ */
