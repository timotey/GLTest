/*
 * Context.h
 *
 *  Created on: Mar 30, 2020
 *      Author: timotey
 */

#ifndef GLW_CONTEXT_H_
#define GLW_CONTEXT_H_

#include "dependencies.h"

namespace glw
{

struct GLVersion
{
	unsigned major = 3;
	unsigned minor = 3;
	enum class profile
	{
		compat = GLFW_OPENGL_COMPAT_PROFILE,
		core = GLFW_OPENGL_CORE_PROFILE,
		any = GLFW_OPENGL_ANY_PROFILE
	};
};

class context_error: public std::exception
{
private:
	const std::string m_what;
public:
	context_error(std::string what)
			: m_what(what)
	{
	}
	context_error(const char* what)
			: m_what(what)
	{
	}
	context_error()
			: m_what("")
	{
	}

	const char* what() const noexcept override
	{
		return this->m_what.c_str();
	}
};

class Context
{
private:
	GLVersion version;
	GLFWwindow* window = nullptr;
public:
	explicit Context(GLVersion, unsigned w, unsigned h);
	virtual ~Context() = default;
	Context(const Context& other) = delete;
	Context(Context&& other) = default;
	Context& operator=(const Context& other) = delete;
	Context& operator=(Context&& other) = default;
};

} /* namespace obj */

#endif /* GLW_CONTEXT_H_ */
