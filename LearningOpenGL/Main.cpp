#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<iostream>
#include<vector>

#include"Shader.h"
#include"stb_image.h"
#include"Texture.h"
#include"Camera.h"
#include"Mesh.h"
#include"Random.h"
#include"FastNoise.h"
#include"Chunk.h"
#include"World.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// settings
const int SCR_WIDTH = 960;
const int SCR_HEIGHT = 540;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 55.0f, 3.0f));
World* worldPtr;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learning OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << '\n';
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	double startTime = glfwGetTime();

	World world(std::random_device{}() );
	Renderer renderer(&world);
	
	worldPtr = &world;

	double previousTime = glfwGetTime();

	std::cout << previousTime - startTime << '\n';

	// 8 seconds : 

	int frameCount = 0;

	glm::mat4 projection = glm::perspective(glm::radians(65.0f),
		(float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 450.0f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);

		// render
		// ------
		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.getViewMatrix();

		renderer.getShader(ShaderType::DEFAULT_SHADER).use();
		renderer.getShader(ShaderType::DEFAULT_SHADER).setMatrix("projection", projection);
		renderer.getShader(ShaderType::DEFAULT_SHADER).setMatrix("view", view);

		world.updateChunks(camera.getPosition());
		renderer.render();

		glfwSwapBuffers(window);
		glfwPollEvents();	

		double currentTime = glfwGetTime();
		frameCount++;
		// If a second has passed.
		if (currentTime - previousTime >= 1.0)
		{
			// Display the frame count here any way you want.
			std::string str = "Learning OpenGL ";
			str.append(std::to_string(frameCount))
				.append(" X: " + std::to_string((camera.getPosition().x)) + " ")
				.append("Y: " + std::to_string((camera.getPosition()).y) + " ")
				.append("Z: " + std::to_string((camera.getPosition()).z) + " ")
				.append(" Xdir: " + std::to_string(camera.getDirectionVector().x) + " ")
				.append("Ydir: " + std::to_string(camera.getDirectionVector().y) + " ")
				.append("Zdir: " + std::to_string(camera.getDirectionVector().z));
				glfwSetWindowTitle(window, str.c_str());
			frameCount = 0;
			previousTime = currentTime;
		}

	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.moveAround(Camera::Movement::FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.moveAround(Camera::Movement::BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveAround(Camera::Movement::LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveAround(Camera::Movement::RIGHT, deltaTime);

}

void mouse_callback(GLFWwindow* window, double x, double y)
{
	camera.lookAround(static_cast<float>(x), static_cast<float>(y));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		worldPtr->castRay(camera);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}