/*
 * Model.h
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#define GLW_MODEL_MODEL_H_
#ifndef GLW_MODEL_MODEL_H_
#define GLW_MODEL_MODEL_H_

#include "Mesh.h"

namespace glw
{

class Renderer;

class Model: public Mesh
{
private:
public:
	std::vector<Texture> textures;
	friend class Renderer;
	Model(Mesh&&);
	virtual ~Model() = default;
	Model(const Model &other) = delete;
	Model(Model &&other) = default;
	Model& operator=(const Model &other) = delete;
	Model& operator=(Model &&other) = default;
};

} /* namespace glw */

#endif /* GLW_MODEL_MODEL_H_ */
