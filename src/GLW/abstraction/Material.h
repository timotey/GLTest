/*
 * Material.h
 *
 *  Created on: Feb 13, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_MATERIAL_H_
#define GLW_MODEL_MATERIAL_H_

#include "../dependencies.h"
#include "../Program.h"

namespace glw
{

class Material
{
public:
	glm::fvec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::fvec3 diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::fvec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
	float shininess = 32.0f;
	Material() = default;
	virtual ~Material() = default;
	Material(const Material& other) = default;
	Material(Material&& other) = default;
	Material& operator=(const Material& other) = delete;
	Material& operator=(Material&& other) = default;

	virtual void bind(const Program& shader) const;
};

} /* namespace glw */

#endif /* GLW_MODEL_MATERIAL_H_ */
