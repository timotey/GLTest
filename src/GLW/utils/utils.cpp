/*
 * utoils.cpp
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */
#include "../utils/utils.hpp"

namespace glw
{

namespace utils
{

std::string dump(const std::string filename)
{
	std::ifstream file(filename);
	if (!file)
		return "";
	file.seekg(0, std::ios::end);
	auto length = file.tellg();
	file.seekg(0, std::ios::beg);
	std::string ret(length, ' ');
	file.read(&ret[0], length);
	return ret;
}

}  // namespace utilse

}  // namespace glw
