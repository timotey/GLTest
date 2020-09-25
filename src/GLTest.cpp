//============================================================================
// Name        : GLTest.cpp
// Author      : Timotey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "GLW/abstraction/Framebuffer.h"
#include "GLW/Program.h"
#include "GLW/model/PerspectiveCamera.h"
#include "GLW/model/Scene.h"
#include "GLW/dependencies.h"
#include "GLW/utils/typenames.h"
#include "GLW/model/basic_Model.h"
#include "GLW/Renderer.h"

double pi = 3.14;

constexpr glm::uvec2 initwindowsize = glm::vec2(640, 480);

float aspectRatio = 4.0f / 3.0f;
bool changedaspectRatio = 1;
bool escapestate = false;
bool escapepressed = false;

auto vpcallback = [](GLFWwindow* window, int width, int height) -> void
{
	glViewport(0, 0, width, height);
	aspectRatio = static_cast<float>(width)/static_cast<float>(height);
	changedaspectRatio = true;

};

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(initwindowsize.x, initwindowsize.y, "GLTest",
	NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	vpcallback(window, initwindowsize.x, initwindowsize.y);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (glewInit())
	{
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glw::utils::glcall(__LINE__, __FILE__, glEnable, GL_BLEND);

	float phase = 0;
	float time = 0;
	float ampl = 2;
	glm::dvec2 cursorPos(0, 0);
	glm::vec3 position;

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, vpcallback);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
//    glDepthMask(GL_FALSE);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glClearColor(0.0, 0.0, 0.0, 0.00001);
	glfwSetCursorPos(window, 0, 0);

	std::shared_ptr<glw::Program> p = std::make_shared<glw::Program>(
	        glw::FragmentShader(
	                glw::utils::dump("Resource/Shader/fragment.glsl").c_str()),
	        glw::GeometryShader(
	                glw::utils::dump("Resource/Shader/geometry.glsl").c_str()),
	        glw::VertexShader(
	                glw::utils::dump("Resource/Shader/vertex.glsl").c_str()));
	glw::Scene s{glw::make_Cubemap(std::array<char const*, 6>{
	        "Resource/Texture/Cubemap/Lycksele/posx.jpg",
	        "Resource/Texture/Cubemap/Lycksele/negx.jpg",
	        "Resource/Texture/Cubemap/Lycksele/posy.jpg",
	        "Resource/Texture/Cubemap/Lycksele/negy.jpg",
	        "Resource/Texture/Cubemap/Lycksele/posz.jpg",
	        "Resource/Texture/Cubemap/Lycksele/negz.jpg"})};
	glw::Renderer r(glm::uvec2{2000, 1500});
	glw::PerspectiveCamera c(45.0_deg);
	c.setAspectRatio(aspectRatio);
	c.setTranslation({0, 0, 3});
	std::array<glw::Object, 3000> o;
	for (size_t i = 0; i < o.size(); ++i)
		o[i] = {glm::vec3{std::sin(i * pi * 2 / o.size()) * ampl, std::cos(
		        i * pi * 2 / o.size()) * ampl, 0}};
	s.push("torus",
	        std::unique_ptr<glw::Model>(
	                new glw::Model(
	                        glw::make_vao("Resource/Meshes/untitled.obj"),
	                        glw::make_Texture2(
	                                "Resource/Texture/Chrome.jpg"))));
	s.push("cube",
	        std::unique_ptr<glw::Model>(
	                new glw::Model(glw::make_vao("Resource/Meshes/cube.obj"),
	                        glw::make_Texture2(
	                                "Resource/Texture/Chrome.jpg"))));
	glw::Object cube{glm::vec3{0, -5, 0}};
	cube.setScale({50, 1, 50});
	s.push("cube", &cube);
	for (auto& v : o)
		s.push("torus", &v);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		time = glfwGetTime();
		phase = time / 1;

		if (changedaspectRatio)
			c.setAspectRatio(aspectRatio);
		c.setRotation(glm::quat(glm::vec3(0, phase / 12, 0)));
		c.setTranslation(
		        glm::vec3(5 * std::sin(-phase / 12), 0,
		                5 * std::cos(phase / 12)));
		for (size_t i = 0; i < o.size(); ++i)
		{
			o[i].setTranslation(
			        {std::sin(phase + (i * pi * 2 / o.size())) * ampl, std::cos(
			                phase + (i * pi * 2 / o.size())) * ampl, 0});
			o[i].setRotation(glm::vec3{0, 0, -phase - (i * pi * 2 / o.size())});
			o[i].setScale(glm::vec3{std::cos(phase) + 1} * 0.1f);
		}
//		o->setTranslation(
//		        glm::vec3(2 * sin( (phase / 3) + pi / 2 * 3) + 2,
//		                -2 * sin( (phase / 3) + pi / 2 * 3) - 2, 0));
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		r.draw(window, s, c);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	std::cout << "Terminated." << std::endl;
	glfwTerminate();
	return 0;
}
