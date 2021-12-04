#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "textrenderer.h"
#include "equation.h"

#include <stdlib.h>
#include <time.h>
#include <map>	

#include <iostream>

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action);
void mouse_button_callback(GLFWwindow* window);
void display(GLFWwindow* window);

void window_refresh_callback(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//string answer;

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

	// When user resizes the screen
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Mouse cursor callback
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);

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

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);
		mouse_button_callback(window);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(window);
		//glfwSwapBuffers(window);
	}
}

void mouse_button_callback(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		//glfwSetWindowShouldClose(window, true);
		//cout << "I was pressed" << endl;
	}
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	//std::cout << xPos << " : " << yPos << std::endl;
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		//display(window);
	}
}

void window_refresh_callback(GLFWwindow* window)
{
	//display(window);
	glfwSwapBuffers(window);
}

void display(GLFWwindow* window) {
	Shader shader("Shaders/glyph.vs", "Shaders/glyph.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// FreeType
	TextRenderer txt("Fonts/Antonio-Bold.ttf");

	map<int, string> randAnswers;
	int eqns[10], random;
	string q, v, answer1, answer2, answer, answer3;
	string op1, op2 = "";
	Equation eqn;

	eqn.generate_rand_nums(eqns);
	for (unsigned int i = 0; i < 10; i += 2)
	{
		int ans = eqns[i] + eqns[i + 1];
		op1 = to_string(eqns[i]);
		op2 = to_string(eqns[i + 1]);
		q += op1;
		q += "+";
		q += op2;
		cout << eqns[i] << " + " << eqns[i + 1] << " is " << ans << endl;

		answer += to_string(ans);
		answer1 += to_string(ans + 22);
		answer2 += to_string(ans + 34);
		answer3 += to_string(ans + 12);
		
		// This piece of code randomizes the answers
		srand(time(0));
		random = rand() % 4;
		if (random == 0)
		{
			randAnswers[0] = answer;
			randAnswers[1] = answer2;
			randAnswers[2] = answer1;
			randAnswers[3] = answer3;

		}
		else if (random == 1)
		{
			randAnswers[0] = answer2;
			randAnswers[1] = answer;
			randAnswers[2] = answer3;
			randAnswers[3] = answer1;
		}
		else if (random == 2)
		{
			randAnswers[0] = answer2;
			randAnswers[1] = answer3;
			randAnswers[2] = answer;
			randAnswers[3] = answer1;
		}
		else if (random == 3)
		{
			randAnswers[0] = answer2;
			randAnswers[1] = answer3;
			randAnswers[2] = answer1;
			randAnswers[3] = answer;
		}

		txt.RenderText(shader, op1, 50.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, "+", 100.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, op2, 130.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

		txt.RenderText(shader, randAnswers[0], 130.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[1], 130.0f, 400.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[2], 130.0f, 300.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[3], 130.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		break;
	}
}