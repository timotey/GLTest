/*
 * utils.hpp
 *
 *  Created on: Feb 9, 2020
 *      Author: timotey
 */

#ifndef GLW_UTILS_HPP_
#define GLW_UTILS_HPP_

#include "../dependencies.h"

#include <csignal>

namespace glw
{

namespace utils
{

std::string dump(const std::string filename);

template <class Function, class ... Args, std::enable_if_t<
        !std::is_void<std::result_of_t<Function(Args...)>>::value>* = nullptr>
typename std::result_of_t<Function(Args...)> glcall(const unsigned line,
        const char* file, Function&& f, Args&& ... a)
{
	while (glGetError());
	typename std::result_of_t<Function(Args...)> r = f(a...);
	auto err = glGetError();
	if (err)
	{
		std::cerr << "At line " << std::dec << std::setfill(' ') << std::setw(6)
		        << line << " in file " << file << std::endl;
        std::cerr << "With args: ";
        ([&]{std::cerr << a << ", ";}(),...);
        std ::cerr << "\n";

		do
		{
			switch (err)
			{
				case GL_INVALID_ENUM:
					std::cerr
					        << "\tAn unacceptable value is specified for an enumerated argument\n";
					break;
				case GL_INVALID_VALUE:
					std::cerr << "\tA numeric argument is out of range\n";
					break;
				case GL_INVALID_OPERATION:
					std::cerr
					        << "\tThe specified operation is not allowed in the current state\n";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cerr << "\tThe framebuffer object is not complete\n";
					break;
				case GL_OUT_OF_MEMORY:
					std::cerr
					        << "\tThere is not enough memory left to execute the command\n";
					break;
				case GL_STACK_OVERFLOW:
					std::cerr
					        << "\tAn attempt has been made to perform an operation that would cause an internal stack to overflow\n";
					break;
				case GL_STACK_UNDERFLOW:
					std::cerr
					        << "\tAn attempt has been made to perform an operation that would cause an internal stack to underflow\n";
					break;
				default:
					std::cerr << "\tAn unknown error has occured(" << std::hex
					        << err << ")\n";
					break;
			}
		}
		while ( (err = glGetError()));
		std::raise(SIGTRAP);
	}
	return r;
}

template <class Function, class ... Args, std::enable_if_t<
        std::is_void<std::result_of_t<Function(Args...)>>::value>* = nullptr>
typename std::result_of_t<Function(Args...)> glcall(const unsigned line,
        const char* file, Function&& f, Args&& ... a)
{
	while (glGetError());
	f(a...);
	auto err = glGetError();
	if (err)
	{
		std::cerr << "At line " << std::dec << std::setfill(' ') << std::setw(6)
		        << line << " in file " << file << std::endl;
        std::cerr << "With args: ";
        ([&]{std::cerr << a << ", ";}(),...);
        std::cerr << "\n";

		do
		{
			std::cerr << "\t(0x" << std::hex << err << ") ";
			switch (err)
			{
				case GL_INVALID_ENUM:
					std::cerr << "GL_INVALID_ENUM\n";
					break;
				case GL_INVALID_VALUE:
					std::cerr << "GL_INVALID_VALUE\n";
					break;
				case GL_INVALID_OPERATION:
					std::cerr << "GL_INVALID_OPERATION\n";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
					break;
				case GL_OUT_OF_MEMORY:
					std::cout << "GL_OUT_OF_MEMORY\n";
					break;
				case GL_STACK_OVERFLOW:
					std::cerr << "GL_STACK_OVERFLOW\n";
					break;
				case GL_STACK_UNDERFLOW:
					std::cerr << "GL_STACK_UNDERFLOW\n";
					break;
				default:
					std::cerr << "An unknown error has occured\n";
					break;
			}
		}
		while ( (err = glGetError()));
		std::raise(SIGTRAP);
	}
	return;
}

template <class Function, std::enable_if_t<
        !std::is_void<std::result_of_t<Function()>>::value>* = nullptr>
typename std::result_of_t<Function()> lglcall(const unsigned line,
        const char* file, Function&& f)
{
	while (glGetError());
	typename std::result_of_t<Function()> r = f();
	auto err = glGetError();
	if (err)
	{
		std::cerr << "At line " << std::dec << std::setfill(' ') << std::setw(6)
		        << line << " in file " << file << std::endl;

		do
		{
			switch (err)
			{
				case GL_INVALID_ENUM:
					std::cerr
					        << "\tAn unacceptable value is specified for an enumerated argument\n";
					break;
				case GL_INVALID_VALUE:
					std::cerr << "\tA numeric argument is out of range\n";
					break;
				case GL_INVALID_OPERATION:
					std::cerr
					        << "\tThe specified operation is not allowed in the current state\n";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cerr << "\tThe framebuffer object is not complete\n";
					break;
				case GL_OUT_OF_MEMORY:
					std::cerr
					        << "\tThere is not enough memory left to execute the command\n";
					break;
				case GL_STACK_OVERFLOW:
					std::cerr
					        << "\tAn attempt has been made to perform an operation that would cause an internal stack to overflow\n";
					break;
				case GL_STACK_UNDERFLOW:
					std::cerr
					        << "\tAn attempt has been made to perform an operation that would cause an internal stack to underflow\n";
					break;
				default:
					std::cerr << "\tAn unknown error has occured(" << std::hex
					        << err << ")\n";
					break;
			}
		}
		while ( (err = glGetError()));
		std::raise(SIGTRAP);
	}
	return r;
}

template <class Function, std::enable_if_t<
        std::is_void<std::result_of_t<Function()>>::value>* = nullptr>
void lglcall(const unsigned line, const char* file, Function&& f)
{
	while (glGetError());
	f();
	auto err = glGetError();
	if (err)
	{
		std::cerr << "At line " << std::dec << std::setfill(' ') << std::setw(6)
		        << line << " in file " << file << std::endl;

		do
		{
			std::cerr << "\t(0x" << std::hex << err << ") ";
			switch (err)
			{
				case GL_INVALID_ENUM:
					std::cerr << "GL_INVALID_ENUM\n";
					break;
				case GL_INVALID_VALUE:
					std::cerr << "GL_INVALID_VALUE\n";
					break;
				case GL_INVALID_OPERATION:
					std::cerr << "GL_INVALID_OPERATION\n";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
					break;
				case GL_OUT_OF_MEMORY:
					std::cout << "GL_OUT_OF_MEMORY\n";
					break;
				case GL_STACK_OVERFLOW:
					std::cerr << "GL_STACK_OVERFLOW\n";
					break;
				case GL_STACK_UNDERFLOW:
					std::cerr << "GL_STACK_UNDERFLOW\n";
					break;
				default:
					std::cerr << "An unknown error has occured\n";
					break;
			}
		}
		while ( (err = glGetError()));
		std::raise(SIGTRAP);
	}
	return;
}

}
// namespace utils

}// namespace GLW

#endif /* GLW_UTILS_HPP_ */
