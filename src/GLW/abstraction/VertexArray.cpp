/*
 * VertexArray.cpp
 *
 *  Created on: Feb 12, 2020
 *      Author: timotey
 */

#include "../abstraction/VertexArray.h"

#include <exception>
#include "regex"

namespace glw
{

template <class Function>
static typename std::vector<std::result_of_t<Function(std::smatch const&)>> parse(
        Function parsefunc, std::regex const& r, std::string const& s)
{
	std::vector<std::result_of_t<Function(std::smatch const&)>> ret;
	for (auto it = std::sregex_iterator(s.begin(), s.end(), r);
	        it != std::sregex_iterator(); ++it)
	{
		ret.push_back(parsefunc(*it));
	}
	return ret;
}

glw::VertexArray make_vao(std::string const& filename)
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec2 tex;
	};
	std::regex vertex("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	std::regex texture("vt ((?:0|1)\\.\\d+) ((?:0|1)\\.\\d+)");
	std::regex normal("vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
	std::regex face(
	        "f (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)? (\\d+)(?:\\/(\\d+)?)?(?:\\/(\\d+)?)?");

	std::string file = glw::utils::dump(filename);
	auto verts = parse([](std::smatch const& a)
	{
		return glm::vec3
		( std::stof(a[1]), std::stof(a[2]), std::stof(a[3]));
	}, vertex, file);

	auto texcoords = parse([](std::smatch const& a)
	{
		return glm::vec2
		( std::stof(a[1]), std::stof(a[2]));
	}, texture, file);

//	std::map<glm::uvec3, size_t> vertexlink;
//	std::vector<unsigned int> indices;
//	for (auto it = sregex_iterator(file.begin(), file.end(), face);
//	        it != std::sregex_iterator(); ++it)
//	{
//		std::smatch match;
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
//			catch (const std::out_of_range& e)
//			{
//				indices.push_back(vertexlink.size());
//				vertexlink[result] = vertexlink.size();
//			}
//		}
//	}

	std::vector<glm::uvec3> vertexlink;
	std::vector<unsigned int> indices;
	for (auto it = std::sregex_iterator(file.begin(), file.end(), face);
	        it != std::sregex_iterator(); ++it)
	{
		std::smatch match;
		match = *it;
		for (size_t i = 0; i < 3; i++)
		{
			glm::uvec3 result(
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
				size_t offset = size_t(a - vertexlink.begin());
				indices.push_back(offset);
			}
		}
	}
	glw::VertexBufferLayout l;
	l.push<float>(3, 0, 0);
	l.push<float>(2, 0, 0);
//	l.push<unsigned short>(1);

	std::vector<Vertex> outvertecies(vertexlink.size());
	std::transform(vertexlink.begin(), vertexlink.end(), outvertecies.begin(),
	        [&verts, &texcoords](glm::uvec3 const& val)
	        {
		        return Vertex
		        {	verts[val[0]-1], texcoords[val[1]-1]};
	        });

	glw::IndexBuffer a(indices.data(), indices.size());
	glw::VertexBuffer b(outvertecies.data(),
	        outvertecies.size() * sizeof(Vertex));
	glw::VertexArray c(std::move(a), std::move(b), l);
	return c;
}
VertexArray& quad()
{
	static VertexBufferLayout l;
	l.push<float>(2, 0, 0);
	static float a[] = {-1, -1, -1, 1, 1, -1, 1, 1};
	static unsigned i[] = {0, 1, 2, 3};

	static VertexArray s(IndexBuffer(i, sizeof (i) / sizeof (i[0])),
	        VertexBuffer(a, sizeof (a)), l);
	return s;
}
VertexArray& cube()
{
	static VertexArray s = make_vao("Resource/Meshes/cube.obj");
	return s;
}

VertexArray::VertexArray(IndexBuffer&& _ib, VertexBuffer&& _vb,
        VertexBufferLayout const& _layout) :
		ib(std::move(_ib)),
		layout(_layout)
{
	glw::utils::glcall(__LINE__, __FILE__, glGenVertexArrays, 1, &this->handle);
	this->vb.push_back(std::move(_vb));
	this->bind();
}

VertexArray::~VertexArray()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteVertexArrays, 1,
	        &this->handle);
}

void VertexArray::bind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindVertexArray, this->handle);
	//if (!glw::utils::glcall(__LINE__, __FILE__, glIsVertexArray, this->handle))
	//	throw std::logic_error("Not a vao");
	this->ib.bind();
	if (!this->layout.isDirty())
		return;
	size_t i = 0;
	for (auto e : layout.getLayout())
	{
		this->vb[e.bufferID].bind();
		glw::utils::glcall(__LINE__, __FILE__, glEnableVertexAttribArray, i);
		glw::utils::glcall(__LINE__, __FILE__, glVertexAttribPointer, i,
		        e.count, e.type, GL_FALSE, layout.getStrides().at(e.bufferID),
		        reinterpret_cast<void*>(e.offset));
		glw::utils::glcall(__LINE__, __FILE__, glVertexAttribDivisor, i,
		        e.divisor);
		i++;
	}
	this->layout.unDirty();
}

void VertexArray::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindVertexArray, 0);
	this->ib.unbind();
}

VertexArray::VertexArray(VertexArray&& other) :
		ib(std::move(other.ib)),
		vb(std::move(other.vb)),
		layout(std::move(other.layout))
{
	this->handle = other.handle;
	other.handle = 0;
}

VertexArray& VertexArray::operator =(VertexArray&& other)
{
	this->layout = std::move(other.layout);
	this->vb = std::move(other.vb);
	this->ib = std::move(other.ib);
	this->handle = other.handle;
	other.handle = 0;
	return *this;
}

} /* namespace glw */
