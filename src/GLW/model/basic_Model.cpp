/*
 * basic_Model.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#include "tuple"
#include "regex"

#include "../Program.h"
#include "basic_Model.h"
namespace glw
{

glw::Movable::Movable(glm::vec3 position, glm::quat rotation, glm::vec3 scale) :
		translation(position),
		rotation(rotation),
		scale(scale)
{
}

glm::mat4 glw::Movable::getTransformMat() const
{
	glm::mat4 ret(1);
	ret = glm::translate(ret, this->translation);
	ret = glm::scale(ret, this->scale);
	ret *= glm::mat4_cast(this->rotation);
	return ret;
}

const glm::fvec3& glw::Movable::getTranslation() const
{
	return translation;
}

void glw::Movable::setTranslation(const glm::vec3& position)
{
	this->translation = position;
}

const glm::fquat& glw::Movable::getRotation() const
{
	return rotation;
}

void glw::Movable::setRotation(const glm::quat& rotation)
{
	this->rotation = rotation;
}

const glm::fvec3& glw::Movable::getScale() const
{
	return scale;
}

void glw::Movable::setScale(const glm::vec3& scale)
{
	this->scale = scale;
}

template <>
void Movable::translate<translation_mode::absl>(const glm::vec3& position)
{
	this->translation += position;
}

template <>
void Movable::translate<translation_mode::rel>(const glm::vec3& position)
{
	this->translation += glm::vec3(
	        glm::vec4(position, 0.0) * this->getTransformMat());
}

void Movable::rotate(const glm::quat& rotation)
{
	this->rotation *= rotation;
}

glw::Object::Object(glm::vec3 position, glm::quat rotation) :
		Movable(position, rotation)
{

}
//
//template <class Function>
//static typename std::vector<std::result_of_t<Function(const std::smatch&)>> parse(
//        Function parsefunc, const std::regex& r, const std::string& s)
//{
//	std::vector<std::result_of_t<Function(const std::smatch&)>> ret;
//	for (auto it = std::sregex_iterator(s.begin(), s.end(), r);
//	        it != std::sregex_iterator(); ++it)
//	{
//		ret.push_back(parsefunc(*it));
//	}
//	return ret;
//}
//
//basic_Model make_Model(const std::string& filename,
//        std::shared_ptr<glw::Program> s, Texture&& t)
//{
//	struct Vertex
//	{
//		glm::vec3 pos;
//		glm::vec2 texCoord;
//	};
//	std::regex vertex("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
//	std::regex texture("vt ((?:0|1)\\.\\d+) ((?:0|1)\\.\\d+)");
//	std::regex normal("vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
//	std::regex face(
//	        "f (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)?");
//
//	std::string file = glw::utils::dump(filename);
//	auto verts = parse([](const std::smatch& a)
//	{
//		return glm::vec3
//		( std::stof(a[1]), std::stof(a[2]), std::stof(a[3]));
//	}, vertex, file);
//
//	auto texcoords = parse([](const std::smatch& a)
//	{
//		return glm::vec2
//		( std::stof(a[1]), std::stof(a[2]));
//	}, texture, file);
//
////	std::map<std::tuple<size_t, size_t, size_t>, size_t> vertexlink;
////	std::vector<unsigned int> indices;
////	for (auto it = sregex_iterator(file.begin(), file.end(), face);
////	        it != sregex_iterator(); ++it)
////	{
////		smatch match;
////		match = *it;
////		for (size_t i = 0; i < 9; i += 3)
////		{
////			std::tuple<size_t, size_t, size_t> result = std::make_tuple(
////			        (match[1 + i].length()) ? std::stoi(match[1 + i]) : 0,
////			        (match[2 + i].length()) ? std::stoi(match[2 + i]) : 0,
////			        (match[3 + i].length()) ? std::stoi(match[3 + i]) : 0);
////			try
////			{
////				indices.push_back(vertexlink.at(result));
////			}
////			catch (const std::out_of_range &e)
////			{
////				indices.push_back(vertexlink.size());
////				vertexlink[result] = vertexlink.size();
////			}
////		}
////	}
//
//	std::vector<glm::uvec3> vertexlink;
//	std::vector<unsigned int> indices;
//	for (auto it = std::sregex_iterator(file.begin(), file.end(), face);
//	        it != std::sregex_iterator(); ++it)
//	{
//		std::smatch match;
//		match = *it;
//		for (size_t i = 0; i < 3; i++)
//		{
//			glm::uvec3 result(
//			        (match[1 + i * 3].length()) ?
//			                std::stoi(match[1 + i * 3]) : 0,
//			        (match[2 + i * 3].length()) ?
//			                std::stoi(match[2 + i * 3]) : 0,
//			        (match[3 + i * 3].length()) ?
//			                std::stoi(match[3 + i * 3]) : 0);
//			auto a = std::find(vertexlink.begin(), vertexlink.end(), result);
//			if (a == vertexlink.end())
//			{
//				vertexlink.push_back(result);
//				indices.push_back(vertexlink.size() - 1);
//			}
//			else
//			{
//				size_t offset = size_t(a - vertexlink.begin());
//				indices.push_back(offset);
//			}
//		}
//	}
//	glw::VertexBufferLayout l;
//	l.push<float>(3);
//	l.push<float>(2);
////	l.push<unsigned short>(1);
//
//	std::vector<Vertex> outvertecies(vertexlink.size());
//	std::transform(vertexlink.begin(), vertexlink.end(), outvertecies.begin(),
//	        [&verts, &texcoords](const glm::uvec3& val)
//	        {
//		        return Vertex
//		        {	verts[val[0]-1],texcoords[val[1]-1]};
//	        });
//
//	glw::IndexBuffer a(indices.data(), indices.size());
//	glw::VertexBuffer b(outvertecies.data(),
//	        outvertecies.size() * sizeof(Vertex));
//	glw::VertexArray c(std::move(a), std::move(b), l);
//	return
//	{	std::move(c), std::move(t),s};
//}
//basic_Model make_Model(const std::string& filename, glw::Program&& s,
//        Texture&& t)
//{
//	struct Vertex
//	{
//		glm::vec3 pos;
//		glm::vec2 texCoord;
//	};
//	std::regex vertex("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
//	std::regex texture("vt ((?:0|1)\\.\\d+) ((?:0|1)\\.\\d+)");
//	std::regex normal("vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
//	std::regex face(
//	        "f (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)?");
//
//	std::string file = glw::utils::dump(filename);
//	auto verts = parse([](const std::smatch& a)
//	{
//		return glm::vec3
//		( std::stof(a[1]), std::stof(a[2]), std::stof(a[3]));
//	}, vertex, file);
//
//	auto texcoords = parse([](const std::smatch& a)
//	{
//		return glm::vec2
//		( std::stof(a[1]), std::stof(a[2]));
//	}, texture, file);
//
////	std::map<std::tuple<size_t, size_t, size_t>, size_t> vertexlink;
////	std::vector<unsigned int> indices;
////	for (auto it = sregex_iterator(file.begin(), file.end(), face);
////	        it != sregex_iterator(); ++it)
////	{
////		smatch match;
////		match = *it;
////		for (size_t i = 0; i < 9; i += 3)
////		{
////			std::tuple<size_t, size_t, size_t> result = std::make_tuple(
////			        (match[1 + i].length()) ? std::stoi(match[1 + i]) : 0,
////			        (match[2 + i].length()) ? std::stoi(match[2 + i]) : 0,
////			        (match[3 + i].length()) ? std::stoi(match[3 + i]) : 0);
////			try
////			{
////				indices.push_back(vertexlink.at(result));
////			}
////			catch (const std::out_of_range &e)
////			{
////				indices.push_back(vertexlink.size());
////				vertexlink[result] = vertexlink.size();
////			}
////		}
////	}
//
//	std::vector<glm::uvec3> vertexlink;
//	std::vector<unsigned int> indices;
//	for (auto it = std::sregex_iterator(file.begin(), file.end(), face);
//	        it != std::sregex_iterator(); ++it)
//	{
//		std::smatch match;
//		match = *it;
//		for (size_t i = 0; i < 3; i++)
//		{
//			glm::uvec3 result(
//			        (match[1 + i * 3].length()) ?
//			                std::stoi(match[1 + i * 3]) : 0,
//			        (match[2 + i * 3].length()) ?
//			                std::stoi(match[2 + i * 3]) : 0,
//			        (match[3 + i * 3].length()) ?
//			                std::stoi(match[3 + i * 3]) : 0);
//			auto a = std::find(vertexlink.begin(), vertexlink.end(), result);
//			if (a == vertexlink.end())
//			{
//				vertexlink.push_back(result);
//				indices.push_back(vertexlink.size() - 1);
//			}
//			else
//			{
//				size_t offset = size_t(a - vertexlink.begin());
//				indices.push_back(offset);
//			}
//		}
//	}
//	glw::VertexBufferLayout l;
//	l.push<float>(3);
//	l.push<float>(2);
////	l.push<unsigned short>(1);
//
//	std::vector<Vertex> outvertecies(vertexlink.size());
//	std::transform(vertexlink.begin(), vertexlink.end(), outvertecies.begin(),
//	        [&verts, &texcoords](const glm::uvec3& val)
//	        {
//		        return Vertex
//		        {	verts[val[0]-1],texcoords[val[1]-1]};
//	        });
//
//	glw::IndexBuffer a(indices.data(), indices.size());
//	glw::VertexBuffer b(outvertecies.data(),
//	        outvertecies.size() * sizeof(Vertex));
//	glw::VertexArray c(std::move(a), std::move(b), l);
//	return
//	{	std::move(c), std::move(t), std::move(s)};
//}

} /* namespace glw */
