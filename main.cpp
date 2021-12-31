#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "textrenderer.h"

#include <iostream>

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
			cout << "\n LEVEL 1: Addition Quiz \n\n";
			int A = rand() % 10 + 1 + 10 * (i - 1);
			int B = rand() % 10 + 1 + 10 * (i - 1);
			cout << "Question " << i << " : " << A << " + " << B << " = \n";
			int numInput;
			cin >> numInput;

			if (numInput == A + B) {
				cout << "Correct Answer\n";
				score = score + 10;
				cout << "Score : " << score ;
			}
			else {
				cout << "Wrong Answer \n Try Again! ";
				exit(0);
			}
		}
		else {
			break;
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
int C, D;
void subtraction_quiz()
{
	for (int i = 1; i <= 5; i++)
	{
		if (i <= 5) {
			cout << "\n\n LEVEL 2: Subtraction Quiz\n\n";
			int A = rand()% 100 + 1;
			int B = rand()% 100 + 1;
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
			cin >> numInput;
			if (numInput ==  D - C) {
				cout << "Correct Answer\n ";
				score = score + 10;
				cout << "Score : " << score;
			}
			else {
				cout << "Wrong Answer\n  Try Again!";
				exit(0);
			}
		}
			else {
				break;
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
				cout << "\n\n LEVEL 3 : Multiplication Quiz\n\n";
				int A = rand() % (5 * i) + 1;
				int B = rand() % (5 * i) + 1;
				cout << "Question " << i << " : " << A << " x " << B << " = \n ";
				int numInput;
				cin >> numInput;
				if (numInput == A * B) {
					cout << "Correct Answer\n ";
					score = score + 10;
					cout << "Score : " << score;
				}
				else {
					cout << "Wrong Answer\n Try Again!";
					exit(0);
				}
			}
			else {
				break;
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
				int A = rand() % 100;
				int B = rand() % 99 + 1;
				cout << "Question " << " : " << A << " / " << B << " = \n";
				int numInput;
				cin >> numInput;
				if (numInput == A / B) {
					cout << "Correct Answer\n";
					score = score + 10;
					cout << "Score : " << score;
				}
				else {
					cout << "Wrong Answer\n  Try Again!";
					exit(0);
				}
			}
			else {
				break;
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

