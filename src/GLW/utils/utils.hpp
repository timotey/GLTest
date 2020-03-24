/*
 * utils.hpp
 *
 *  Created on: Feb 9, 2020
 *      Author: timotey
 */

#ifndef GLW_UTILS_HPP_
#define GLW_UTILS_HPP_

#include "../dependencies.h"

namespace glw
{

namespace utils
{

std::string dump(const std::string filename);

template <class Function, class ... Args, std::enable_if_t<
        !std::is_void<std::result_of_t<Function(Args...)>>::value>* = nullptr>
typename std::result_of_t<Function(Args...)> glcall(const unsigned line,
        const char *file, Function &&f, Args &&... a)
{
	while (glGetError());
	typename std::result_of_t<Function(Args...)> r = f(a...);
	auto err = glGetError();
	if (err)
	{
		std::cout << "At line " << std::dec << std::setfill(' ') << std::setw(6)
		        << line << " in file " << file << std::endl;

		do
		{
			switch (err)
			{
				case GL_INVALID_ENUM:
					std::cout
					        << "\tAn unacceptable value is specified for an enumerated argument\n";
					break;
				case GL_INVALID_VALUE:
					std::cout << "\tA numeric argument is out of range\n";
					break;
				case GL_INVALID_OPERATION:
					std::cout
					        << "\tThe specified operation is not allowed in the current state\n";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cout << "\tThe framebuffer object is not complete\n";
					break;
				case GL_OUT_OF_MEMORY:
					std::cout
					        << "\tThere is not enough memory left to execute the command\n";
					break;
				case GL_STACK_OVERFLOW:
					std::cout
					        << "\tAn attempt has been made to perform an operation that would cause an internal stack to overflow\n";
					break;
				case GL_STACK_UNDERFLOW:
					std::cout
					        << "\tAn attempt has been made to perform an operation that would cause an internal stack to underflow\n";
					break;
				default:
					std::cout << "\tAn unknown error has occured(" << std::hex
					        << err << ")\n";
					break;
			}
		}
		while ((err = glGetError()));
	}
	return r;
}

template <class Function, class ... Args, std::enable_if_t<
        std::is_void<std::result_of_t<Function(Args...)>>::value>* = nullptr>
typename std::result_of_t<Function(Args...)> glcall(const unsigned line,
        const char *file, Function &&f, Args &&... a)
{
	while (glGetError());
	f(a...);
	auto err = glGetError();
	if (err)
	{
		std::cout << "At line " << std::dec << std::setfill(' ') << std::setw(6)
		        << line << " in file " << file << std::endl;

		do
		{
			std::cout << "\t(0x" << std::hex << err << ") ";
			switch (err)
			{
				case GL_INVALID_ENUM:
					std::cout << "GL_INVALID_ENUM\n";
					break;
				case GL_INVALID_VALUE:
					std::cout << "GL_INVALID_VALUE\n";
					break;
				case GL_INVALID_OPERATION:
					std::cout << "GL_INVALID_OPERATION\n";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
					break;
				case GL_OUT_OF_MEMORY:
					std::cout << "GL_OUT_OF_MEMORY\n";
					break;
				case GL_STACK_OVERFLOW:
					std::cout << "GL_STACK_OVERFLOW\n";
					break;
				case GL_STACK_UNDERFLOW:
					std::cout << "GL_STACK_UNDERFLOW\n";
					break;
				default:
					std::cout << "An unknown error has occured\n";
					break;
			}
		}
		while ((err = glGetError()));
	}
	return;
}

}  // namespace utils

}  // namespace GLW

#endif /* GLW_UTILS_HPP_ */
