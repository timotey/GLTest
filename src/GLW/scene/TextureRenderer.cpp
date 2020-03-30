/*
 * TextureRenderer.cpp
 *
 *  Created on: Feb 25, 2020
 *      Author: timotey
 */

#include "TextureRenderer.h"

namespace glw
{

TextureRenderer::TextureRenderer(const Camera& camera,
        const std::weak_ptr<Scene>& scene, glm::uvec2 size)
		: Renderer(camera, scene), Texture(size)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
	        this->handle(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
}

TextureRenderer::TextureRenderer(const Camera& camera,
        const std::shared_ptr<Scene>& scene, glm::uvec2 size)
		: Renderer(camera, scene), Texture(size)
{
}

TextureRenderer::TextureRenderer(TextureRenderer&& other)
		:
		        Renderer(std::move(static_cast<Renderer&>(other))),
		        Texture(std::move(static_cast<Texture&>(other)))
{
}

TextureRenderer& TextureRenderer::operator =(TextureRenderer&& other)
{
	this->Renderer::operator =(std::move(static_cast<Renderer&>(other)));
	this->Texture::operator =(std::move(static_cast<Texture&>(other)));
	return *this;
}

void TextureRenderer::render()
{
}

} /* namespace glw */
