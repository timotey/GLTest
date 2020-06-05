/*
 * PBRModel.cpp
 *
 *  Created on: May 10, 2020
 *      Author: timotey
 */

#include "PBRModel.h"

namespace glw
{

PBRModel::PBRModel(glw::VertexArray&& _vao, glw::Texture2&& _alb,
        glw::Texture2&& _norm, glw::Texture2&& _ao_roug_met) :
		vao(std::move(_vao)),
		alb(std::move(_alb)),
		norm(std::move(_norm)),
		ao_roug_met(std::move(_ao_roug_met))
{
}

void PBRModel::draw(glw::GBuffer&, const glw::Scene&, const glw::Camera&,
        const glw::Object&)
{
}

void PBRModel::drawBatched(glw::GBuffer&, const glw::Scene&, const glw::Camera&,
        const glw::Object**, size_t size)
{
}
//
//PBRModel make_PBRModel(const std::string& path)
//{
//
//}

} /* namespace glw */

