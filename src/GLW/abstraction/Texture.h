/*
 * Texture2.h
 *
 *  Created on: Feb 22, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_TEXTURE_H_
#define GLW_MODEL_TEXTURE_H_

#include "../abstraction/Material.h"
#include "../dependencies.h"
#include "../vendor/stb_image.h"
#include "../utils/utils.hpp"

namespace glw
{

enum class tex_type
{
	Texture2 = GL_TEXTURE_2D,
//	Texture2Array = GL_TEXTURE_2D_ARRAY,
	Cubemap = GL_TEXTURE_CUBE_MAP,
//	CubemapArray = GL_TEXTURE_BINDING_CUBE_MAP_ARRAY
};

struct Texture_settings
{
	GLenum layout = GL_RGBA8;
	GLenum internal = GL_UNSIGNED_BYTE;
	enum class format : GLenum
	{
		r = GL_RED,
		rg = GL_RG,
		rgb = GL_RGB,
		bgr = GL_BGR,
		rgba = GL_RGBA,
		bgra = GL_BGRA,
		ds = GL_DEPTH_STENCIL
	} format = format::rgba;
	enum class min_filter : GLenum
	{
		nearest = GL_NEAREST,
		linear = GL_LINEAR,
		mip_nearest_nearest = GL_NEAREST_MIPMAP_NEAREST,
		mip_linear_nearest = GL_LINEAR_MIPMAP_NEAREST,
		mip_nearest_linear = GL_NEAREST_MIPMAP_LINEAR,
		mip_linear_linear = GL_LINEAR_MIPMAP_LINEAR
	} min = min_filter::linear;
	enum class mag_filter : GLenum
	{
		nearest = GL_NEAREST, linear = GL_LINEAR
	} mag = mag_filter::nearest;
	enum class wrap : GLenum
	{
		repeat = GL_REPEAT,
		edge = GL_CLAMP_TO_EDGE,
		mirrored = GL_MIRRORED_REPEAT,

	} wrap = wrap::edge;
};

template <tex_type T>
class Texture;

template <tex_type T>
class Texture
{
private:
	unsigned int h = 0;
	glm::uvec2 size;
	int BPP = 0;
	Texture_settings s;
protected:
public:
	unsigned int handle() const
	{
		return this->h;
	}
	explicit Texture(size_t width, size_t height, Texture_settings _s =
	        Texture_settings());
	explicit Texture(glm::uvec2 _size = glm::uvec2(), Texture_settings s =
	        Texture_settings());
	virtual ~Texture();
	Texture(Texture const& other) = delete;
	Texture(Texture&& other);
	Texture& operator=(Texture const& other) = delete;
	Texture& operator=(Texture&& other);
	void bind(unsigned int slot) const;
	void unbind() const;
	void setSize(glm::uvec2 _size);
	void setImage(void const* const data, size_t index = 0);
	void swap(Texture&);
};

using Texture2 = Texture<tex_type::Texture2>;
using Cubemap = Texture<tex_type::Cubemap>;

Texture2 make_Texture2(std::string const& file);
Cubemap make_Cubemap(std::string const& file);
Cubemap make_Cubemap(std::array<char const*, 6> file);

//extern template class Texture<tex_type::Texture2> ;
//extern template class Texture<tex_type::Cubemap> ;

} /* namespace glw */

#endif /* GLW_MODEL_TEXTURE_H_ */
