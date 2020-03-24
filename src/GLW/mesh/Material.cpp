/*
 * Material.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#include "Material.h"

namespace glw
{
} /* namespace glw */

void glw::Material::bind(const Program &shader) const
{
	shader.setUniform<3, float>("u_Material.ambient", this->ambient);
	shader.setUniform<3, float>("u_Material.diffuse", this->diffuse);
	shader.setUniform<3, float>("u_Material.specular", this->specular);
	shader.setUniform<1, float>("u_Material.shininess", glm::fvec1(this->shininess));
}
