#pragma once
#ifndef EQUATION_H
#define EQUATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Equation {
public:
	int operand1, operand2;
	int arr[3], eqns[10], answers[10];
	string s = "";

	Equation() {
		operand1 = 0;
		operand2 = 0;
	}

	// This function is a test - not being called in main
	string randomize(int arr[], string sign = nullptr) {

		srand(time(0));
		operand1 = rand() % 100 + 1;
		operand2 = rand() % 100 + 1;

		for (unsigned i = 0; i < 10; i++)
		{
			//srand(time(0));
			operand1 = rand() % 100 + 1;
			eqns[i] = operand1;
		}


		if (sign == "-")
		{
			if (operand1 >= operand2) {
				arr[0] = operand1;
				arr[1] = operand2;
				arr[2] = operand1 - operand2;
			}
			else {
				arr[0] = operand2;;
				arr[1] = operand1;
				arr[2] = operand2 - operand1;
			}
		}
		else if (sign == "+")
		{
			arr[0] = operand1;
			arr[1] = operand2;
			arr[2] = operand1 + operand2;
		}


		s += to_string(arr[0]);
		s += sign;
		s += to_string(arr[1]);
		s += "=";

		return s;

	}

	// Function that generates random equations
	void generate_rand_nums(int eqns[]) {
		srand(time(0));
		for (unsigned int i = 0; i < 10; i++)
		{
			//srand(time(0));
			operand1 = rand() % 100 + 1;
			eqns[i] = operand1;
		}
	}

	// This fxn is a test - not being called in main
	void answer(int eqns[]) {
		this->generate_rand_nums(eqns);
		for (unsigned int i = 0; i < 10; i += 2)
		{
			int ans = eqns[i] + eqns[i + 1];
			answers[i] = ans;
		}
	}
};


#endif // !EQUATION_H

