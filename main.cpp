#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "textrenderer.h"
#include "equation.h"

#include <stdlib.h>
#include <time.h>
#include <map>	

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

void addition_quiz();
void subtraction_quiz();
void multiplication_quiz();
void division_quiz();



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
		
		addition_quiz();
		subtraction_quiz();
		multiplication_quiz();
		division_quiz();

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
}
void mouse_button_callback(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		//glfwSetWindowShouldClose(window, true);
		//cout << "I was pressed" << endl;
	}
}

string ans1, ans2 = "";
string p;
int numInput, A, B;
int score = 0;
string p1, p2 = "";

/*Level 1*/
void addition_quiz()
{
	for (int i = 1; i <= 5; i++)
	{
		if (i <= 5) {
			cout << "\n LEVEL 1: Addition Quiz (YOU ONLY HAVE 30 SECONDS TO SOLVE EACH QUESTION) \n\n";
			Beep(0, 4000);
			//int h, m, s;
			//cout << "Hours: "; cin >> h;
			//cout << "Minutes: "; cin >> m;
			//cout << "Seconds: "; cin >> s;

			//timer(h, m, s);
			//for (int i = 100; ; i = i + 50)
				//Beep(i, 1000);
			for (int i = 1; i <= 30; i++)
			{
				srand(time(0));
				int A = rand() % 10 + 1 + 10 * (i - 1);
				int B = rand() % 10 + 1 + 10 * (i - 1);
				cout << "Question " << i << " : " << A << " + " << B << " = \n";
				int numInput;
				time_t start = time(0);
				int y = 30;
				while (!_kbhit())
				{
					if (abs(time(0) - start) > 30)
					{
						j = 1;
						break;
					}
				}
				if (j == 1)
				{
					cout << "Time's up";
					j = 2;
				}
				else
				{
					cin >> numInput;
					if ((time(0) - start) > 30)
					{
						cout << "Time's up";
						j = 2;
					}
					else if (numInput == A + B) {
						cout << "Correct Answer\n";
						score = score + 10;
						cout << "Score : " << score;
					}
					else {
						cout << "Wrong Answer \n Try Again! ";
						j = 2;
					}

				}
				if (j == 2) break;
				{
					Beep(2000, 100);Beep(1500, 100);Beep(2000, 100);Beep(1500, 100);Beep(2000, 700);Beep(0, 400);
				}











			}






		}

	}
	Shader shader("Shaders/glyph.vs", "Shaders/glyph.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// FreeType
	TextRenderer txt("Fonts/Antonio-Bold.ttf");

	p1 = to_string(A);
	p2 = to_string(B);
	p += p1;
	p += "+";
	p += p2;
	txt.RenderText(shader, "Level 1 : Addition Quiz", 50.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p1, 100.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, "+", 130.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p2, 150.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));

}
/*Level 2*/

void subtraction_quiz()
{
	for (int i = 1; i <= 5; i++)
	{
		if (i <= 5) {
			cout << "\n\n LEVEL 2: Subtraction Quiz (YOU ONLY HAVE 30 SECONDS TO SOLVE  EACH QUESTION)\n\n";
			Beep(0, 4000);
			for (int i = 1; i <= 30; i++)
			{
				srand(time(0));
				int C, D;
				int A = rand() % 100 + 1;
				int B = rand() % 100 + 1;
				if (A >= B)
				{
					D = A;
					C = B;
				}
				else
				{
					D = B;
					C = A;
				}
				cout << "Question " << i << " :  " << D << " - " << C << " =\n ";
				int numInput;
				time_t start = time(0);
				int y = 30;
				while (!_kbhit())
				{
					if (abs(time(0) - start) > 30)
					{
						j = 1;
						break;
					}
				}
				if (j == 1)
				{
					cout << "Time's Up!!";
					j = 2;
				}
				else
				{
					cin >> numInput;
					if ((time(0) - start) > 30)
					{
						cout << "Time's Up!!";
						j = 2;
					}
					else if (numInput == D - C) {
						cout << "Correct Answer\n ";
						score = score + 10;
						cout << "Score : " << score;
					}
					else {
						cout << "Wrong Answer\n  Try Again!";
						j = 2;
					}


				}
				if (j == 2) break;
				{
					Beep(2000, 100);Beep(1500, 100);Beep(2000, 100);Beep(1500, 100);Beep(2000, 700);Beep(0, 400);
				}




			}
		}
	}

	Shader shader("Shaders/glyph.vs", "Shaders/glyph.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// FreeType
	TextRenderer txt("Fonts/Antonio-Bold.ttf");

	p1 = to_string(A);
	p2 = to_string(B);
	p += p1;
	p += "-";
	p += p2;
	txt.RenderText(shader, "Level 2 : Subtraction Quiz", 50.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p1, 100.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, "+", 130.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p2, 150.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
}
/*Level 3*/
void multiplication_quiz()
{
	int j = 0;
	for (int Y = 1; j != 2 && Y != 2; Y++)
	{
		for (int i = 1; i <= 5; i++)
		{
			if (i <= 5) {
				cout << "\n\n LEVEL 3 : Multiplication Quiz (YOU ONLY HAVE 30 SECONDS TO SOLVE  EACH QUESTION)\n\n";
				Beep(0, 4000);
				for (int i = 1; i <= 30; i++)
				{
					srand(time(0));
					int A = rand() % (5 * i) + 1;
					int B = rand() % (5 * i) + 1;
					cout << "Question " << i << " : " << A << " x " << B << " = \n ";
					int numInput;
					time_t start = time(0);
					int y = 30;
					while (!_kbhit())
					{
						if (abs(time(0) - start) > 30)
						{
							j = 1;
							break;
						}
					}
					if (j == 1)
					{
						cout << "Time's Up!!";
						j = 2;
					}
					else
					{
						cin >> numInput;
						if ((time(0) - start) > 30)
						{
							cout << "Time's Up!!";
							j = 2;
						}
						else  if (numInput == A * B) {
							cout << "Correct Answer\n ";
							score = score + 10;
							cout << "Score : " << score;
						}
						else {
							cout << "Wrong Answer\n Try Again!";
							j = 2;
						}
					}
					if (j == 2) break;
					{
						Beep(2000, 100);Beep(1500, 100);Beep(2000, 100);Beep(1500, 100);Beep(2000, 700);Beep(0, 400);
					}

				}



			}
		}
	}




	Shader shader("Shaders/glyph.vs", "Shaders/glyph.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// FreeType
	TextRenderer txt("Fonts/Antonio-Bold.ttf");

	p1 = to_string(A);
	p2 = to_string(B);
	p += p1;
	p += "*";
	p += p2;
	txt.RenderText(shader, "Level 3 : Multiplication Quiz", 50.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p1, 100.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, "+", 130.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p2, 150.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
}
/*LEVEL 4*/
void division_quiz()
{
	int j = 0;
	for (int Y = 1; j != 2 && Y != 2; Y++)
	{
		for (int i = 1; i <= 5; i++)
		{
			if (i <= 5) {
				cout << "\n\n LEVEL 4:Division Quiz\n\n";
				Beep(0, 4000);
				srand(time(0));
				int A = rand() % 100;
				int B = rand() % 99 + 1;
				cout << "Question " << " : " << A << " / " << B << " = \n";
				int numInput;
				time_t start = time(0);
				int y = 30;
				while (!_kbhit())
				{
					if (abs(time(0) - start) > 30)
					{
						j = 1;
						break;
					}
				}
				if (j == 1)
				{
					cout << "Time's Up!!";
					j = 2;
				}
				else
				{
					cin >> numInput;
					if ((time(0) - start) > 30)
					{
						cout << "Time's Up!!";
						j = 2;
					}
					else if (numInput == A / B) {
						cout << "Correct Answer\n";
						score = score + 10;
						cout << "Score : " << score;
					}
					else {
						cout << "Wrong Answer\n  Try Again!";
						j = 2;
					}


				}
				if (j == 2) break;
				{
					Beep(2000, 100);Beep(1500, 100);Beep(2000, 100);Beep(1500, 100);Beep(2000, 700);Beep(0, 400);
				}


			}

		}
	}

	Shader shader("Shaders/glyph.vs", "Shaders/glyph.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// FreeType
	TextRenderer txt("Fonts/Antonio-Bold.ttf");

	p1 = to_string(A);
	p2 = to_string(B);
	p += p1;
	p += "/";
	p += p2;
	txt.RenderText(shader, "Level 4 : Divisoon Quiz", 50.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p1, 100.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, "+", 130.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
	txt.RenderText(shader, p2, 150.0f, 600.0f, 1.0f, glm::vec3(0.2, 0.6f, 0.5f));
}

	//else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	display(window);
	//	//glfwSwapBuffers(window);
	//}
//}

//void mouse_button_callback(GLFWwindow* window)
//{
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
//		//glfwSetWindowShouldClose(window, true);
//		//cout << "I was pressed" << endl;
//	}
//}

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