#include "Addition.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "equation.h"
#include "textrenderer.h"
#include <map>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

Addition::Addition()
{

}

void Addition::display_add() {
	int key = 0;
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

