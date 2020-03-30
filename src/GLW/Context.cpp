/*
 * Context.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: timotey
 */

#include "Context.h"

namespace glw
{

Context::Context(GLVersion v, unsigned w, unsigned h)
		: version(v)
{
	if ( !glfwInit())
		throw context_error();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	this->window = glfwCreateWindow(w, h, "SHS",
	NULL, NULL);
	if ( !this->window)
	{
		glfwTerminate();
		throw context_error();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(this->window);
	if (glewInit())
	{
		glfwTerminate();
		throw context_error();
	}
}

} /* namespace obj */
