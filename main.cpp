#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "textrenderer.h"
#include "equation.h"
#include <irrKlang.h>
#include "addition.h"
#include <stdlib.h>
#include <time.h>
#include <map>	
#include <cmath>

#include <iostream>
#include <stdlib.h> //for system()
#include <windows.h> //for Sleep() and Beep()
#include <cmath>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>

using namespace std;
#include <windows.h>
using namespace irrklang;

int j = 0;
int key = 0;
int refpoint = 1;
int selpoint = 1;
int score_value = 0;
string sc = "";

void enterController(int& refpoint, int& selpoint);

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void characterCallback(GLFWwindow * window, unsigned int keycode);
void CharacterModCallback(GLFWwindow* window, unsigned keycode, int modifierkey);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void userInput(GLFWwindow* window, int modifierkey);

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
void window_refresh_callback(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void display_add(GLFWwindow* window);
void display_sub(GLFWwindow* window);
void display_multiply(GLFWwindow* window);
void display_division(GLFWwindow* window);
void display_square(GLFWwindow* window);
void display_cube(GLFWwindow* window);

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
				
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);	

		cout << "Cursor Position at (" << xpos << " : " << ypos << ")" << endl;
		if (key == 0 && xpos >= 300.0 && xpos <= 500.0 && ypos >= 100.0 && ypos <= 300.0)
		{
			cout << "Correct" << endl;
			score_value = score_value + 10;
			cout << "Score is " << score_value << endl;
		}
		else if (key == 1 && xpos >= 300.0 && xpos <= 500.0 && ypos >= 400.0 && ypos <= 600.0) {
			cout << "Correct" << endl;
			score_value = score_value + 10;
			cout << "Score is " << score_value << endl;
		}
		else if (key == 2 && xpos >= 600.0 && xpos <= 800.0 && ypos >= 100.0 && ypos <= 300.0) {
			cout << "Correct" << endl;
			score_value = score_value + 10;
			cout << "Score is " << score_value << endl;
		}
		else if (key == 3 && xpos >= 600.0 && xpos <= 800.0 && ypos >= 400.0 && ypos <= 600.0) {
			cout << "Correct" << endl;
			score_value = score_value + 10;
			cout << "Score is " << score_value << endl;
		}
		else {
			cout << "Wrong answer" << endl;
			score_value = score_value - 10;
			cout << "Score is " << score_value << endl;
		}
	}
}

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
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwSetKeyCallback(window, key_callback);
	//glfwSetWindowRefreshCallback(window, window_refresh_callback);

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
	TextRenderer txt("Fonts/OCRAEXT.ttf");

	//Irrklang audio 
	irrklang::ISoundEngine* SoundEngine = createIrrKlangDevice();

	//Irrklang audio 
	//irrklang::ISoundEngine* SoundEngine = createIrrKlangDevice();
	
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
	
		switch (refpoint)
		{
		case 0:
			glfwSetWindowShouldClose(window, true);
			break;
		case 1:
			txt.RenderText(shader, "Welcome to SolveIt ", 350.0f, 700.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			txt.RenderText(shader, "121660 Alex Kariuki", 400.0f, 600.0f, 0.7f, glm::vec3(0.3, 0.7f, 0.9f));
			txt.RenderText(shader, "121457 Cyprian Kyalo", 400.0f, 550.0f, 0.7f, glm::vec3(0.3, 0.7f, 0.9f));
			txt.RenderText(shader, "120357 BettyRose Waithera ", 400.0f, 500.0f, 0.7f, glm::vec3(0.3, 0.7f, 0.9f));
			txt.RenderText(shader, "121289 WHitney Atonya", 400.0f, 450.0f, 0.7f, glm::vec3(0.3, 0.7f, 0.9f));
			txt.RenderText(shader, "Press Enter to Continue", 930.0f, 10.0f, 0.4f, glm::vec3(1.0, 1.0f, 1.0f));
			break;
		case 2:
			display_add(window);
			break;
		case 3:
			display_sub(window);
			break;
		case 4:
			display_multiply(window);
			break;
		case 5:
			display_division(window);
			break;
		case 6:
			display_square(window);
			break;
		case 7:
			display_cube(window);
			break;
		case 8:
			sc += to_string(score_value);
			txt.RenderText(shader, "Your score is ", 450.0f, 400.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));
			txt.RenderText(shader, sc, 550.0f, 350.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));
			break;

		default:
			break;
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void enterController(int& refpoint, int& selpoint) {
	if (refpoint == 1) {
		refpoint += 1;
	}
	else if (refpoint == 2 || refpoint > 2) {
		refpoint += selpoint;
	}
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ENTER:
			enterController(refpoint, selpoint);
			std::cout << refpoint << std::endl;
			break;

		default:
			break;
		}
	}
}


string ans1, ans2 = "";
string p;
int numInput, A, B;
int score = 0;
string p1, p2 = "";

static void cursorPositionCallback(GLFWwindow * window, double xPos, double yPos)
{
	std::cout << "Cursor t " << xPos << " : " << yPos << std::endl;

}


void display_add(GLFWwindow* window) {
	glfwSwapInterval(250);

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

	txt.RenderText(shader, "Level 1 : Addition Quiz", 400.0f, 700.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

	eqn.generate_rand_nums(eqns);
	for (unsigned int i = 0; i < 3; i += 2)
	{
		int ans = eqns[i] + eqns[i + 1];
		op1 = to_string(eqns[i]);
		op2 = to_string(eqns[i + 1]);
		q += op1;
		q += "+";
		q += op2;
		//cout << eqns[i] << " + " << eqns[i + 1] << " is " << ans << endl;

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

		for (auto& i : randAnswers) {
			if (i.second == answer) {
				key = i.first;
				break; // to stop searching
			}
		}
		cout << "The answer is in position " << key << endl;

		txt.RenderText(shader, op1, 480.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, "+", 550.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, op2, 600.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

		txt.RenderText(shader, randAnswers[0], 400.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[1], 400.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[2], 700.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[3], 700.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		break;
	}
}

void display_sub(GLFWwindow* window) {
	glfwSwapInterval(250);

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

	txt.RenderText(shader, "Level 2 : Subtrction Quiz", 400.0f, 700.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

	eqn.generate_rand_nums(eqns);
	for (unsigned int i = 0; i < 3; i += 2)
	{
		int ans = eqns[i] - eqns[i + 1];
		op1 = to_string(eqns[i]);
		op2 = to_string(eqns[i + 1]);
		q += op1;
		q += "-";
		q += op2;
		// cout << eqns[i] << " - " << eqns[i + 1] << " is " << ans << endl;

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

		cout << "The answer is in position " << key << endl;

		txt.RenderText(shader, op1, 480.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, "-", 550.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, op2, 600.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));


		txt.RenderText(shader, randAnswers[0], 400.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[1], 400.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[2], 700.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[3], 700.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		break;
	}
}

void display_multiply(GLFWwindow* window) {
	glfwSwapInterval(350);

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

	txt.RenderText(shader, "Level 3 : Multiplication Quiz", 400.0f, 700.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	
	eqn.generate_rand_nums(eqns);
	for (unsigned int i = 0; i < 3; i += 2)
	{
		int ans = eqns[i] * eqns[i + 1];
		op1 = to_string(eqns[i]);
		op2 = to_string(eqns[i + 1]);
		q += op1;
		q += "x";
		q += op2;

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
		
		cout << "The answer is in position " << key << endl;

		txt.RenderText(shader, op1, 480.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, "x", 550.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, op2, 600.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));


		for (auto& i : randAnswers) {
			if (i.second == answer) {
				key = i.first;
				break; // to stop searching
			}
		}
		cout << "The answer is in position " << key << endl;

		txt.RenderText(shader, randAnswers[0], 400.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[1], 400.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[2], 700.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[3], 700.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		break;
		
	}
}

void display_division(GLFWwindow * window) {
	glfwSwapInterval(350);

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

	txt.RenderText(shader, "Level 4 : Division Quiz", 400.0f, 700.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));


	eqn.generate_rand_nums(eqns);
	for (unsigned int i = 0; i < 3; i += 2)
	{
				
		int ans = eqns[i] / eqns[i + 1];
		op1 = to_string(eqns[i]);
		op2 = to_string(eqns[i + 1]);
		q += op1;
		q += "/";
		q += op2;
		
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
		
		cout << "The answer is in position " << key << endl;

		txt.RenderText(shader, op1, 480.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, "/", 550.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

		txt.RenderText(shader, op2, 600.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

		txt.RenderText(shader, randAnswers[0], 400.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[1], 400.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[2], 700.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		txt.RenderText(shader, randAnswers[3], 700.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
		break;
	}
}
		
void display_square(GLFWwindow * window) {
		glfwSwapInterval(350);

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

		txt.RenderText(shader, "Level 5 : Square Quiz", 400.0f, 700.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

		eqn.generate_rand_nums(eqns);
		for (unsigned int i = 0; i < 3; i += 2)
		{
			int ans = eqns[i] * eqns[i];
			op1 = to_string(eqns[i]);
			// op2 = to_string(eqns[i + 1]);
			q += op1;
			q += "*";
			q += op1;
			

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

			cout << "The answer is in position " << key << endl;

			txt.RenderText(shader, op1, 480.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, "^", 550.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, "2", 600.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, "(squared)", 700.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));


			txt.RenderText(shader, randAnswers[0], 400.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, randAnswers[1], 400.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, randAnswers[2], 700.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, randAnswers[3], 700.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			break;
		}
	}

void display_cube(GLFWwindow * window) {
		glfwSwapInterval(350);

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

		txt.RenderText(shader, "Level 6 : Cube Quiz", 400.0f, 700.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

		eqn.generate_rand_nums(eqns);
		for (unsigned int i = 0; i < 3; i += 2)
		{
			int ans = eqns[i] * eqns[i] * eqns[i];
			op1 = to_string(eqns[i]);
			// op2 = to_string(eqns[i + 1]);
			q += op1;
			q += "*";
			q += op1;
			// cout << eqns[i] << " / " << eqns[i + 1] << " is " << ans << endl;

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

			cout << "The answer is in position " << key << endl;

			txt.RenderText(shader, op1, 480.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, "^", 550.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, "3", 600.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, "(cubed)", 700.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));


			txt.RenderText(shader, randAnswers[0], 400.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, randAnswers[1], 400.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, randAnswers[2], 700.0f, 200.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			txt.RenderText(shader, randAnswers[3], 700.0f, 500.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
			break;
		}
	}