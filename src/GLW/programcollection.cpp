/*
 * programcollection.cpp
 *
 *  Created on: May 10, 2020
 *      Author: timotey
 */

#include "programcollection.h"

namespace glw
{

namespace shader
{

Program& PBR()
{
	static Program prog{glw::FragmentShader(
	        glw::utils::dump("Resource/Shader/PBR/fragment.glsl").c_str()),
	        glw::GeometryShader(
	                glw::utils::dump("Resource/Shader/PBR/geometry.glsl").c_str()),
	        glw::VertexShader(
	                glw::utils::dump("Resource/Shader/PBR/vertex.glsl").c_str())};
	return prog;
}

Program& Basic()
{
	static Program prog{glw::FragmentShader(
	        glw::utils::dump("Resource/Shader/fragment.glsl").c_str()),
	        glw::GeometryShader(
	                glw::utils::dump("Resource/Shader/geometry.glsl").c_str()),
	        glw::VertexShader(
	                glw::utils::dump("Resource/Shader/vertex.glsl").c_str())};
	return prog;
}

Program& Cubemap()
{
	static Program prog{glw::FragmentShader(
	        glw::utils::dump("Resource/Shader/Cubemap/fragment.glsl").c_str()),
	        glw::VertexShader(
	                glw::utils::dump("Resource/Shader/Cubemap/vertex.glsl").c_str())};
	return prog;
}

Program& Post_process()
{
	static Program prog{
	        glw::FragmentShader(
	                glw::utils::dump(
	                        "Resource/Shader/Post-process/fragment.glsl").c_str()),
	        glw::VertexShader(
	                glw::utils::dump("Resource/Shader/Post-process/vertex.glsl").c_str())};
	return prog;
}

}  // namespace shader

}  // namespace glw
