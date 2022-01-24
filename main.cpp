#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "textrenderer.h"
#include <irrKlang.h>

#include <iostream>
#include <fstream>

#include <windows.h>


using namespace irrklang;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//void welcomeScreen(GLFWwindow* window);
void characterCallback(GLFWwindow* window, unsigned int keycode);
void CharacterModCallback(GLFWwindow* window, unsigned keycode, int modifierkey);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void userInput(GLFWwindow* window, int modifierkey);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "solveIt", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//welcomeScreen(window);

	// When user resizes the screen
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// OpenGL state
	// ------------
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("Shaders/glyph.vs", "Shaders/glyph.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// FreeType
	TextRenderer txt("Fonts/Antonio-Bold.ttf");

	//Irrklang audio 
	//irrklang::ISoundEngine* SoundEngine = createIrrKlangDevice();
	

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		txt.RenderText(shader, "Welcome to SolveIt ", 200.0f, 500.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		txt.RenderText(shader, "Please Input username", 300.0f, 400.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
		txt.RenderText(shader, "Press X to start game", 600.0f, 10.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
		glfwSetCharCallback(window, characterCallback);

		SoundEngine->play2D("Game files/audio/breakout.mp3", true);
	
		
		glfwSetKeyCallback(window, key_callback);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	//userInput(window, 1);
	glfwTerminate();
	return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void characterCallback(GLFWwindow* window, unsigned int keycode) {

	std::cout << keycode << std::endl;

	if (keycode == 120) {

		glfwTerminate();
	}
}

void CharacterModCallback(GLFWwindow* window, unsigned keycode, int modifierkey) {

	std::cout << keycode <<":"  << modifierkey << std::endl;

	if (modifierkey == 0) {
		std::cout << "CapsLock key is pressed" << std::endl; 
	}
}

void userInput( int modifierkey) {

	string username;
	std::cin >> username;

	if (modifierkey == 1) {

		ofstream myfile;
		myfile.open("C:\\OpenGLRoot\\solveIt\\Game files\\nameusers.txt");
		myfile << username;
		myfile.close();
		
		std::cout << "Username saved successfuly" << std::endl;

	}

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		Sleep(200000);
}





