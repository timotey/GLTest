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
constexpr GLenum glEnum = 0;

template <>
constexpr GLenum glEnum<float> = GL_FLOAT;
template <>
constexpr GLenum glEnum<unsigned int> = GL_UNSIGNED_INT;
template <>
constexpr GLenum glEnum<int> = GL_INT;
template <>
constexpr GLenum glEnum<unsigned short> = GL_UNSIGNED_SHORT;
template <>
constexpr GLenum glEnum<short> = GL_SHORT;
template <>
constexpr GLenum glEnum<unsigned char> = GL_UNSIGNED_BYTE;
template <>
constexpr GLenum glEnum<char> = GL_BYTE;

}
// namespace utils

}// namespace glw

#endif /* GLW_UTILS_GLTYPE_HPP_ */
