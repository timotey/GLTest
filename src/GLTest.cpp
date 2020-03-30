//============================================================================
// Name        : GLTest.cpp
// Author      : Timotey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "GLW/shader/FragmentShader.h"
#include "GLW/shader/VertexShader.h"
#include "GLW/shader/GeometryShader.h"
#include "GLW/shader/Program.h"
#include "GLW/utils/utils.hpp"
#include "GLW/utils/typenames.h"
#include "GLW/mesh/Texture.h"
#include "GLW/mesh/Mesh.h"
#include "GLW/scene/Renderer.h"
#include "GLW/camera/OrthoCamera.h"
#include "GLW/camera/PerspectiveCamera.h"
#include "GLW/dependencies.h"

constexpr glm::uvec2 initwindowsize = glm::vec2(640, 480);

float aspectRatio = 4.0f / 3.0f;
bool changedaspectRatio = 1;
bool escapestate = false;
bool escapepressed = false;

auto vpcallback = [](GLFWwindow* window = nullptr, int width,
        int height) -> void
        {
	        glViewport(0, 0, width, height);
	        aspectRatio = static_cast<float>(width)/static_cast<float>(height);
	        changedaspectRatio = true;

        };

const float a = M_PI;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if ( !glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(initwindowsize.x, initwindowsize.y, "SHS",
	NULL, NULL);
	if ( !window)
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

	std::shared_ptr<glw::Program> p = std::make_shared<glw::Program>(
	        glw::FragmentShader(
	                glw::utils::dump("Resource/Shader/fragment.glsl").c_str()),
	        glw::GeometryShader(
	                glw::utils::dump("Resource/Shader/geometry.glsl").c_str()),
	        glw::VertexShader(
	                glw::utils::dump("Resource/Shader/vertex.glsl").c_str()));

	std::shared_ptr<glw::Mesh> model;
	std::shared_ptr<glw::Mesh> model1;
	std::shared_ptr<glw::Mesh> model2;
	std::shared_ptr<glw::Object> o = std::make_shared<glw::Object>();
	std::shared_ptr<glw::Object> o2 = std::make_shared<glw::Object>();
	std::shared_ptr<glw::Object> o3 = std::make_shared<glw::Object>(
	        glm::vec3(0, 0, 5));
	{
		glw::Material mat;
		mat.ambient = glm::vec3(0.25, 0.25, 0.25);
		mat.diffuse = glm::vec3(0.4, 0.4, 0.4);
		mat.specular = glm::vec3(0.774597, 0.774597, 0.774597);
		mat.shininess = 0.6;
		model = std::make_shared<glw::Mesh>(
		        glw::make_Mesh("Resource/Meshes/cube.obj"));
	}
	{
		glw::Material mat;
		mat.ambient = glm::vec3(0.25, 0.25, 0.25);
		mat.diffuse = glm::vec3(0.4, 0.4, 0.4);
		mat.specular = glm::vec3(0.774597, 0.774597, 0.774597);
		mat.shininess = 0.6;
		model1 = std::make_shared<glw::Mesh>(
		        glw::make_Mesh("Resource/Meshes/1.obj"));

	}
	{
		glw::Material mat;
		mat.ambient = glm::vec3(0.25, 0.25, 0.25);
		mat.diffuse = glm::vec3(0.4, 0.4, 0.4);
		mat.specular = glm::vec3(0.774597, 0.774597, 0.774597);
		mat.shininess = 0.6;
		model2 = std::make_shared<glw::Mesh>(
		        glw::make_Mesh("Resource/Meshes/quad.obj"));

	}

	glw::PerspectiveCamera cam(45.0_deg, 0.01f, 1000.0f);
	std::shared_ptr<glw::Scene> scene = std::make_shared<glw::Scene>();

	glw::Renderer main(cam, scene);
	scene->push("Cube", model);
	scene->push("Quad", model2);
	scene->push("monkey", model1);
	scene->push("Cube", p);
	scene->push("Quad", p);
	scene->push("monkey", p);
	scene->push("Cube", o);
	scene->push("Quad", o3);
	scene->push("monkey", o2);

	model->textures[0] = glw::make_Texture("Resource/Texture/Chrome.jpg");
	model1->textures[0] = glw::make_Texture("Resource/Texture/Chrome.jpg");
	model2->textures[0] = glw::make_Texture("Resource/Texture/Chrome.jpg");

	float phase = 0;
	glm::dvec2 cursorPos(0, 0);
	glm::vec3 position;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, vpcallback);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
//    glDepthMask(GL_FALSE);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glClearColor(0.2, 0.2, 0.8, 1.0);
	glfwSetCursorPos(window, 0, 0);
	main.cam().setTranslation(glm::fvec3(0.0_m, 0.0_m, 6.0_m));
	o->setTranslation(glm::fvec3(0.0_m, 0.0_m, -3.0_m));
	o->setScale(glm::fvec3(3.0_m, 3.0_m, 3.0_m));
	/* Loop until the user closes the window */
	while ( !glfwWindowShouldClose(window))
	{

		if (escapestate)
		{
			glm::dvec2 mouseDelta;
			glfwSetInputMode(window, GLFW_CURSOR,
			GLFW_CURSOR_DISABLED);
			glfwGetCursorPos(window, &mouseDelta.x, &mouseDelta.y);
			glfwSetCursorPos(window, 0, 0);
			constexpr float scalefactor = 500;
			mouseDelta /= glm::dvec2
			{scalefactor * aspectRatio, scalefactor};
			mouseDelta =
			{std::clamp(mouseDelta.x, -1.0, 1.0), std::clamp(mouseDelta.y, -1.0,
			        1.0)};
			cursorPos += mouseDelta;
			cursorPos.y = std::clamp(cursorPos.y, -90.0_deg, 90.0_deg);
			cursorPos.x = std::fmod(cursorPos.x, 360.0_deg);

			if (glfwGetKey(window, GLFW_KEY_W))
				main.cam().translate(
				        glm::perp(
				                glm::fvec3(
				                        glm::vec4(0, 0, -1, 0)
				                                * glm::mat4_cast(
				                                        main.cam().getRotation())),
				                glm::fvec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(window, GLFW_KEY_S))
				main.cam().translate(
				        glm::perp(
				                glm::fvec3(
				                        glm::vec4(0, 0, 1, 0)
				                                * glm::mat4_cast(
				                                        main.cam().getRotation())),
				                glm::fvec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(window, GLFW_KEY_A))
				main.cam().translate(
				        glm::perp(
				                glm::fvec3(
				                        glm::vec4( -1, 0, 0, 0)
				                                * glm::mat4_cast(
				                                        main.cam().getRotation())),
				                glm::fvec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(window, GLFW_KEY_D))
				main.cam().translate(
				        glm::perp(
				                glm::fvec3(
				                        glm::vec4(1, 0, 0, 0)
				                                * glm::mat4_cast(
				                                        main.cam().getRotation())),
				                glm::fvec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
				main.cam().translate(
				        glm::proj(
				                glm::fvec3(
				                        glm::vec4(0, -1, 0, 0)
				                                * glm::mat4_cast(
				                                        main.cam().getRotation())),
				                glm::fvec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(window, GLFW_KEY_SPACE))
				main.cam().translate(
				        glm::proj(
				                glm::fvec3(
				                        glm::vec4(0, 1, 0, 0)
				                                * glm::mat4_cast(
				                                        main.cam().getRotation())),
				                glm::fvec3(0.0f, 1.0f, 0.0f)));
		}
		else
			glfwSetInputMode(window, GLFW_CURSOR,
			GLFW_CURSOR_NORMAL);

		if (changedaspectRatio)
		{
			changedaspectRatio = false;
			main.cam().setAspectRatio(aspectRatio);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			if ( !escapepressed)
			{
				glfwSetCursorPos(window, 0, 0);
				escapepressed = true;
				escapestate = !escapestate;
			}
		}
		else
		{
			escapepressed = false;
		}

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		phase = std::fmod(phase + 2.0_deg, 360.0_deg);
//        model->textures[0] = glw::make_Texture("Resource/Texture/Chrome.jpg");

		main.cam().setRotation(
		        glm::quat(glm::fvec3(cursorPos.y, 0, 0))
		                * glm::quat(glm::fvec3(0, cursorPos.x, 0)));
		o->setRotation(
		        glm::fvec3(0.5 * std::sin(phase), 0.5 * std::cos(phase),
		                0.0_m));
		o2->setTranslation(
		        glm::fvec3(3 * std::cos(phase), -3 * std::sin(phase), 2.0_m));
		o2->setRotation(glm::fvec3(0.0_m, 0.0_m, -phase));
		main.render();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	std::cout << "Terminated." << std::endl;
	glfwTerminate();
	return 0;
}
