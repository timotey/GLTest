/*
 * gltype.hpp
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#ifndef GLW_UTILS_GLTYPE_HPP_
#define GLW_UTILS_GLTYPE_HPP_

#include "../dependencies.h"

namespace glw
{

namespace utils
{

template <typename T>
constexpr GLenum glGetEnum();

template<>
constexpr GLenum glGetEnum<float>()
{
	return GL_FLOAT;
}

template<>
constexpr GLenum glGetEnum<unsigned int>()
{
	return GL_UNSIGNED_INT;
}

template<>
constexpr GLenum glGetEnum<int>()
{
	return GL_INT;
}

template<>
constexpr GLenum glGetEnum<unsigned short>()
{
	return GL_UNSIGNED_SHORT;
}

template<>
constexpr GLenum glGetEnum<short>()
{
	return GL_SHORT;
}

template<>
constexpr GLenum glGetEnum<unsigned char>()
{
	return GL_UNSIGNED_BYTE;
}

template<>
constexpr GLenum glGetEnum<char>()
{
	return GL_BYTE;
}

}  // namespace utils

}  // namespace glw

#endif /* GLW_UTILS_GLTYPE_HPP_ */
