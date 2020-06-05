/*
 * PBRModel.h
 *
 *  Created on: May 10, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_PBRMODEL_H_
#define GLW_MODEL_PBRMODEL_H_

#include "basic_Model.h"
#include "../programcollection.h"

namespace glw
{

class PBRModel: public basic_Model
{
	glw::VertexArray vao;
	glw::Texture2 alb;
	glw::Texture2 norm;
	glw::Texture2 ao_roug_met;
public:
	friend PBRModel make_PBRModel(const std::string& path);
	PBRModel(glw::VertexArray&& _vao, glw::Texture2&& _alb, glw::Texture2&& _norm,
	        glw::Texture2&& _ao_roug_met);
	virtual ~PBRModel() = default;
	PBRModel(const PBRModel& other) = delete;
	PBRModel(PBRModel&& other) = default;
	PBRModel& operator=(const PBRModel& other) = delete;
	PBRModel& operator=(PBRModel&& other) = default;

	void draw(glw::GBuffer&, const glw::Scene&, const glw::Camera&,
	        const glw::Object&) override;
	void drawBatched(glw::GBuffer&, const glw::Scene&, const glw::Camera&,
	        const glw::Object**, size_t size) override;
};

PBRModel make_PBRModel(const std::string& path);

} /* namespace glw */

#endif /* GLW_MODEL_PBRMODEL_H_ */
