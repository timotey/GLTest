/*
 * Mesh.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#include "../mesh/Mesh.h"
#include "../utils/utils.hpp"
#include <fstream>
#include <vector>
#include <regex>
#include <string>
using namespace std;

namespace glw
{

template <class Function>
static typename std::vector<std::result_of_t<Function(const smatch&)>> parse(
        Function parsefunc, const regex& r, const std::string& s)
{
	std::vector<std::result_of_t<Function(const smatch&)>> ret;
	for (auto it = sregex_iterator(s.begin(), s.end(), r);
	        it != sregex_iterator(); ++it)
	{
		ret.push_back(parsefunc( *it));
	}
	return ret;
}

Mesh make_Mesh(const std::string& filename)
{

	regex vertex("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex texture("vt (0\\.\\d+) (0\\.\\d+)(?: (\\d+))?");
	regex normal("vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	regex face(
	        "f (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)?");

	string file = glw::utils::dump(filename);
	auto verts = parse([](const smatch& a)
	{
		return make_tuple<float, float, float>
		( std::stof(a[1]), std::stof(a[2]), std::stof(a[3]));
	}, vertex, file);

	auto texcoords = parse([](const smatch& a)
	{
		return make_tuple<float, float>
		( std::stof(a[1]), std::stof(a[2]));
	}, texture, file);

//	std::map<std::tuple<size_t, size_t, size_t>, size_t> vertexlink;
//	std::vector<unsigned int> indices;
//	for (auto it = sregex_iterator(file.begin(), file.end(), face);
//	        it != sregex_iterator(); ++it)
//	{
//		smatch match;
//		match = *it;
//		for (size_t i = 0; i < 9; i += 3)
//		{
//			std::tuple<size_t, size_t, size_t> result = std::make_tuple(
//			        (match[1 + i].length()) ? std::stoi(match[1 + i]) : 0,
//			        (match[2 + i].length()) ? std::stoi(match[2 + i]) : 0,
//			        (match[3 + i].length()) ? std::stoi(match[3 + i]) : 0);
//			try
//			{
//				indices.push_back(vertexlink.at(result));
//			}
//			catch (const std::out_of_range &e)
//			{
//				indices.push_back(vertexlink.size());
//				vertexlink[result] = vertexlink.size();
//			}
//		}
//	}

	std::vector<std::tuple<size_t, size_t, size_t>> vertexlink;
	std::vector<unsigned int> indices;
	for (auto it = sregex_iterator(file.begin(), file.end(), face);
	        it != sregex_iterator(); ++it)
	{
		smatch match;
		match = *it;
		for (size_t i = 0; i < 3; i++)
		{
			std::tuple<size_t, size_t, size_t> result = std::make_tuple(
			        (match[1 + i * 3].length()) ?
			                std::stoi(match[1 + i * 3]) : 0,
			        (match[2 + i * 3].length()) ?
			                std::stoi(match[2 + i * 3]) : 0,
			        (match[3 + i * 3].length()) ?
			                std::stoi(match[3 + i * 3]) : 0);
			auto a = std::find(vertexlink.begin(), vertexlink.end(), result);
			if (a == vertexlink.end())
			{
				vertexlink.push_back(result);
				indices.push_back(vertexlink.size() - 1);
			}
			else
			{
				int offset = a - vertexlink.begin();
				indices.push_back(offset);
			}
		}
	}
	glw::VertexBufferLayout l;
	l.push<float>(3);
	l.push<float>(2);
//	l.push<unsigned short>(1);

	std::vector<tuple<tuple<float, float>, tuple<float, float, float>>> outvertecies(
	        vertexlink.size());
	std::transform(vertexlink.begin(), vertexlink.end(), outvertecies.begin(),
	        [&verts, &texcoords](
	                const std::tuple<size_t, size_t, size_t>& val)
	                {
		                return std::make_tuple(texcoords[std::get<1>(val)], verts[std::get<0>(val)-1] );
	                });

	glw::IndexBuffer a(indices.data(), indices.size());
	glw::VertexBuffer b(outvertecies.data(),
	        outvertecies.size()
	                * sizeof(tuple<tuple<float, float, float>,
	                        tuple<float, float>> ));
	glw::VertexArray c(std::move(b), l);
//	return
//	{
//		{
//			indices.data(), indices.size()},
//		{
//			{
//				outvertecies.data(), outvertecies.size()
//			},
//			l
//		},
//		d};
	return
	{	std::move(a),std::move(c),Material()};
}

} /* namespace glw */
