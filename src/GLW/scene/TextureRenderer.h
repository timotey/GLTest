/*
 * TextureRenderer.h
 *
 *  Created on: Feb 25, 2020
 *      Author: timotey
 */

#ifndef GLW_SCENE_TEXTURERENDERER_H_
#define GLW_SCENE_TEXTURERENDERER_H_

#include "Renderer.h"

namespace glw
{

class TextureRenderer: public Renderer, public Texture
{
public:
	explicit TextureRenderer(const Camera &camera,
	        const std::weak_ptr<Scene> &scene, glm::uvec2 size = glm::uvec2());
	explicit TextureRenderer(const Camera &camera,
	        const std::shared_ptr<Scene> &scene, glm::uvec2 size =
	                glm::uvec2());
	virtual ~TextureRenderer() = default;
	TextureRenderer(const TextureRenderer &other) = delete;
	TextureRenderer(TextureRenderer &&other);
	TextureRenderer& operator=(const TextureRenderer &other) = delete;
	TextureRenderer& operator=(TextureRenderer &&other);
	void render() override;
};

} /* namespace glw */

#endif /* GLW_SCENE_TEXTURERENDERER_H_ */
