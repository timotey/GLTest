/*
 * Program.cpp
 *
 *  Created on: Feb 10, 2020
 *      Author: timotey
 */

#include "Program.h"

namespace glw
{

//template<typename... Args>
//Program::Program(Args&&... args) : handle(glw::utils::pcall(__LINE__, __FILE__, glCreateProgram))
//{
////	glw::utils::pcall(__LINE__, __FILE__, glAttachShader, this->handle, size_t(first));
//	this->make(std::forward<Args>(args)...);
//}

//template<>
//void Program::make(glw::shader& s)
//{
//	glw::utils::pcall(__LINE__, __FILE__, glAttachShader, this->handle, size_t(s));
//	glw::utils::pcall(__LINE__, __FILE__, glLinkProgram, this->handle);
//	glw::utils::pcall(__LINE__, __FILE__, glValidateProgram, this->handle);
//	s.~shader();
//}

//template<typename... Args>
//void Program::make(glw::shader& s, Args... args)
//{
//	glw::utils::pcall(__LINE__, __FILE__, glAttachShader, this->handle, size_t(s));
//	this->make(args...);
//	s.~shader();
//}

unsigned int Program::getUniformLocation(std::string name) const
{
	int location =
	        (!this->uniforms.count(name)) ?
	                this->uniforms[name] = glw::utils::glcall(__LINE__,
	                __FILE__, glGetUniformLocation, this->handle,
	                        name.c_str()) :
	                this->uniforms[name];
	if (location == -1)
		std::cout << "Uniform " << name << " does not exist!" << std::endl;
	return location;
}

Program::operator size_t() const
{
	return this->handle;
}

Program::~Program()
{
	glw::utils::glcall(__LINE__, __FILE__, glDeleteProgram, this->handle);
}

void Program::bind() const
{
	unsigned binding = 0;
	glw::utils::glcall(__LINE__, __FILE__, glGetIntegerv, GL_CURRENT_PROGRAM,
	        reinterpret_cast<int*>(&binding)); //check if thing is already bound

	if (binding != this->handle)
		glw::utils::glcall(__LINE__, __FILE__, glUseProgram, this->handle);
}

void Program::unbind() const
{
	glw::utils::glcall(__LINE__, __FILE__, glUseProgram, 0);
}

template <>
void Program::setUniform<4, float>(const std::string name,
        const glm::vec<4, float> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform4fv,
	        this->getUniformLocation(name), 1, glm::value_ptr(value));
}

template <>
void Program::setUniform<3, float>(const std::string name,
        const glm::vec<3, float> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform3fv,
	        this->getUniformLocation(name), 1, glm::value_ptr(value));
}

template <>
void Program::setUniform<2, float>(const std::string name,
        const glm::vec<2, float> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform2fv,
	        this->getUniformLocation(name), 1, glm::value_ptr(value));
}

template <>
void Program::setUniform<1, float>(const std::string name,
        const glm::vec<1, float> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform1f,
	        this->getUniformLocation(name), value.x);
}

template <>
void Program::setUniform<4, int>(const std::string name,
        const glm::vec<4, int> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform4iv,
	        this->getUniformLocation(name), 1, glm::value_ptr(value));
}

template <>
void Program::setUniform<3, int>(const std::string name,
        const glm::vec<3, int> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform3iv,
	        this->getUniformLocation(name), 1, glm::value_ptr(value));
}

template <>
void Program::setUniform<2, int>(const std::string name,
        const glm::vec<2, int> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform2iv,
	        this->getUniformLocation(name), 1, glm::value_ptr(value));
}

template <>
void Program::setUniform<1, int>(const std::string name,
        const glm::vec<1, int> value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniform1i,
	        this->getUniformLocation(name), value.x);
}

template <>
void Program::setUniformMatrix<4, 4, float>(const std::string name,
        const glm::fmat4 value) const
{
	glw::utils::glcall(__LINE__, __FILE__, glUniformMatrix4fv,
	        this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

Program::Program(Program &&other)
{
	this->handle = other.handle;
	other.handle = 0;
}

Program& Program::operator =(Program &&other)
{
	this->handle = other.handle;
	other.handle = 0;
	return *this;
}

} /* namespace glw */
