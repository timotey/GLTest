/*
 * Model.h
 *
 *  Created on: May 9, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_MODEL_H_
#define GLW_MODEL_MODEL_H_

#include "basic_Model.h"

namespace glw
{

class Model: public virtual basic_Model
{
	struct MatrixData
	{
		glm::mat4 MV;
		MatrixData(const glm::mat4& o, const glm::mat4& c) :
				MV(c * o)
		{
		}
	};
	Texture2 tex;
	std::vector<MatrixData> data;
	VertexArray vao;
public:
	Model(VertexArray&&, Texture2&&);
	virtual ~Model() = default;
	Model(const Model& other) = delete;
	Model(Model&& other) = default;
	Model& operator=(const Model& other) = delete;
	Model& operator=(Model&& other) = default;
	void draw(GBuffer&, const Scene&, const Camera&, const Object&) override;
	void drawBatched(GBuffer&, const Scene&, const Camera&,
	        const Object** const, size_t size) override;
};

} /* namespace glw */

#endif /* GLW_MODEL_MODEL_H_ */
