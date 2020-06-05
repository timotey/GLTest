/*
 * Texture2.cpp
 *
 *  Created on: Feb 22, 2020
 *      Author: timotey
 */

#include "../abstraction/Texture.h"

namespace glw
{

template <tex_type>
static GLenum binding_conversion;
template <>
GLenum binding_conversion<tex_type::Cubemap> =
GL_TEXTURE_BINDING_CUBE_MAP;
template <>
GLenum binding_conversion<tex_type::Texture2> =
GL_TEXTURE_BINDING_2D;

template <tex_type T>
static int common_tex_construct(Texture_settings s)
{
	unsigned int handle;
	glw::utils::glcall(__LINE__, __FILE__, glGenTextures, 1, &handle);
	glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GLenum(T), handle);
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GLenum(T),
	GL_TEXTURE_MIN_FILTER, GLenum(s.min));
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GLenum(T),
	GL_TEXTURE_MAG_FILTER, GLenum(s.mag));
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GLenum(T),
	GL_TEXTURE_WRAP_R, GLenum(s.wrap));
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GLenum(T),
	GL_TEXTURE_WRAP_S, GLenum(s.wrap));
	glw::utils::glcall(__LINE__, __FILE__, glTexParameteri, GLenum(T),
	GL_TEXTURE_WRAP_T, GLenum(s.wrap));
	return handle;
}

template <tex_type T>
class bind_guard
{
	int h;
	int slot;
public:
	bind_guard() :
			h(0),
			slot(0)
	{
		glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv,
		        binding_conversion<T>, &h);
		glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv,
		GL_ACTIVE_TEXTURE, &slot);
	}
	~bind_guard()
	{
		glw::utils::glcall(__LINE__, __FILE__, glActiveTexture, slot);
		glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GLenum(T),
		        this->h);
	}
};

//template <tex_type T>
//void Texture<T>::setImage(void const* const data, size_t side);
template <>
void Texture<tex_type::Texture2>::setImage(void const* const data, size_t side)
{
	bind_guard<tex_type::Texture2> g;
	glw::utils::glcall(__LINE__, __FILE__, glBindTexture,
	        GLenum(tex_type::Texture2), this->h);
	glw::utils::glcall(__LINE__, __FILE__, glTexImage2D,
	        GLenum(tex_type::Texture2), 0, GLenum(this->s.layout), this->size.x,
	        this->size.y, 0, GLenum(this->s.format), GLenum(this->s.internal),
	        data);
}

//template <>
//void Texture<tex_type::Texture2Array>::setImage(void const* const data,
//        size_t layer)
//{
//	bind_guard < tex_type::Texture2Array > g;
//	glw::utils::glcall(__LINE__, __FILE__, glBindTexture,
//	        GLenum(tex_type::Texture2Array), this->h);
//	glw::utils::glcall(__LINE__, __FILE__, glTexImage2D,
//	        GLenum(tex_type::Texture2Array), 0, GLenum(this->s.layout),
//	        this->size.x, this->size.y, 0, GLenum(this->s.format),
//	        GLenum(this->s.internal), data);
//}

template <>
void Texture<tex_type::Cubemap>::setImage(void const* const data, size_t side)
{
	bind_guard<tex_type::Cubemap> g;
	glw::utils::glcall(__LINE__, __FILE__, glBindTexture,
	GL_TEXTURE_CUBE_MAP, this->h);
	glw::utils::glcall(__LINE__, __FILE__, glTexImage2D,
	GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, 0, GLenum(this->s.layout),
	        this->size.x, this->size.y, 0, GLenum(this->s.format),
	        GLenum(this->s.internal), data);
}

template <tex_type T>
Texture<T>::Texture(size_t width, size_t height, Texture_settings _s) :
		size(width, height),
		s(_s)
{
	bind_guard<T> g;
	this->h = common_tex_construct<T>(s);
	if constexpr (T == tex_type::Cubemap)
		for (size_t i = 0; i < 6; i++)
			this->setImage(nullptr, 6);
	else
		this->setImage(nullptr);
}

template <tex_type T>
Texture<T>::Texture(glm::uvec2 _size, Texture_settings _s) :
		size(_size),
		s(_s)
{
	bind_guard<T> g;
	this->h = common_tex_construct<T>(s);
	this->setImage(nullptr);
}

template <tex_type T>
Texture<T>::~Texture()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteTextures, 1, &this->h);
}

template <tex_type T>
Texture<T>::Texture(Texture&& other)
{
	this->BPP = other.BPP;
	this->size = other.size;
	this->h = other.h;
	this->s = other.s;
	other.h = 0;
}

template <tex_type T>
Texture<T>& Texture<T>::operator=(Texture<T>&& other)
{
	this->BPP = other.BPP;
	this->size = other.size;
	this->h = other.h;
	this->s = other.s;
	other.h = 0;
	return *this;
}

Texture2 make_Texture2(std::string const& file)
{
	glm::uvec2 size;
	int ignore;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* input = stbi_load(file.c_str(),
	        &reinterpret_cast<int&>(size.x), &reinterpret_cast<int&>(size.y),
	        &ignore, 4);

	Texture2 tex(size);
	tex.setImage(input);

	stbi_image_free(input);
	return tex;
}

template <tex_type T>
void Texture<T>::bind(unsigned int slot) const
{
	if (!this->h)
		return;
	if (slot > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)
		std::cout << std::dec << "no texture slot" << slot << std::endl;
	int value;
	glw::utils::glcall(__LINE__, __FILE__, glActiveTexture,
	GL_TEXTURE0 + slot);
	glw::utils::glcall(__LINE__, __FILE__, glGetIntegeri_v,
	GL_TEXTURE_BINDING_2D, slot, &value);
	if (this->h != static_cast<unsigned>(value))
		glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GLenum(T),
		        this->h);
}

template <tex_type T>
void Texture<T>::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glBindTexture, GLenum(T), 0);
}

template <tex_type T>
void Texture<T>::setSize(glm::uvec2 _size)
{
	if (this->size == _size)
		return;
	Texture<T> t(_size, this->s);
	this->swap(t);
}

template <tex_type T>
void Texture<T>::swap(Texture& t)
{
	Texture_settings sm = t.s;
	size_t hm = t.h;
	glm::uvec2 sizem = t.size;
	t.s = this->s;
	t.h = this->h;
	t.size = this->size;
	this->s = sm;
	this->h = hm;
	this->size = sizem;
}

Cubemap make_Cubemap(std::string const& file)
{
	glm::uvec2 size;
	unsigned BPP;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* input = stbi_load(file.c_str(),
	        &reinterpret_cast<int&>(size.x), &reinterpret_cast<int&>(size.y),
	        reinterpret_cast<int*>(&BPP), 4);

	size_t stride = size.x * 4;
	size.x /= 4;
	size_t width = size.x * 4;
	size.y /= 3;
	size_t facesize = size.x * size.y * 4;
	Cubemap tex(size, {
	GL_RGBA8, GL_UNSIGNED_BYTE, Texture_settings::format::rgba});
	tex.bind(0);
	std::vector<unsigned char> face;
	face.reserve(facesize);
	//@formatter:off
	size_t offsetmap[] = {
			width * 1 + stride * size.y * 0,
			width * 0 + stride * size.y * 1,
			width * 1 + stride * size.y * 1,
			width * 2 + stride * size.y * 1,
	        width * 3 + stride * size.y * 1,
	        width * 1 + stride * size.y * 2};                                                                                //@formatter:on
	if (!input)
	{
		for (int i = 0; i < 6; ++i)
			tex.setImage(nullptr, i);
		return tex;
	}
	for (auto i = 0; i < 6; ++i)
	{
		for (size_t j = 0; j < size.y - 1; j++)
		{
			std::copy(&input[offsetmap[i] + (stride * i)],
			        &input[offsetmap[i] + (stride * i) + width],
			        std::back_inserter(face));
		}
		tex.setImage(face.data(), i);
		face.clear();
	}

	stbi_image_free(input);
	return tex;
}

Cubemap make_Cubemap(std::array<char const*, 6> file)
{
	unsigned BPP;
	glm::uvec2 size;
	stbi_image_free(
	        stbi_load(file[1], &reinterpret_cast<int&>(size.x),
	                &reinterpret_cast<int&>(size.y),
	                reinterpret_cast<int*>(&BPP), 4));
	stbi_set_flip_vertically_on_load(false);

	Cubemap tex(size, {
	GL_RGBA8, GL_UNSIGNED_BYTE, Texture_settings::format::rgba});
	tex.bind(0);
	for (size_t i = 0; i < 6; i++)
	{
		unsigned char* input = stbi_load(file[i],
		        &reinterpret_cast<int&>(size.x),
		        &reinterpret_cast<int&>(size.y), reinterpret_cast<int*>(&BPP),
		        4);
		tex.setImage(input, i);
		stbi_image_free(input);
	}

	return tex;
}

template class Texture<tex_type::Texture2> ;
template class Texture<tex_type::Cubemap> ;

} /* namespace glw */
