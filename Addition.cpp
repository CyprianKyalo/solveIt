#include "Addition.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

Addition::Addition()
{
	srand(time(0));
	Addition::A = rand() % 10;
	Addition::B = rand() % 10 + 1;
	//return 0;
}

int Addition::randomize()
{
	srand(time(0));
	Addition::A = rand() % 10;
	Addition::B = rand() % 10 + 1;
	return 0;
}

int Addition::sum()
{
	//randomize();
	int A, B;
	A = Addition::A;
	B = Addition::B;

	int numInput;
	time_t start = time(0);
	int y = 30;
	int j = 0;
	int score = 0;
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
		exit(0);
		//j = 2;
	}
	else
	{
		cin >> numInput;
		if ((time(0) - start) > 30)
		{
			cout << "Time's up";
			exit(0);
			j = 2;
		}
		else if (numInput == A + B) {
			cout << "Correct Answer\n";
			score = score + 10;
			cout << "Score : " << score << endl;
			//cout << "op1 is : " << op1[i] << endl << endl;
		}
		else {
			cout << "Wrong Answer\n";
			score = score - 10;
			if (score < 0)
				score = 0;
			cout << "Score : " << score << endl;
		}
	}
	
	/*if (j == 2) break;
	{
		Beep(2000, 100); Beep(1500, 100); Beep(2000, 100); Beep(1500, 100); Beep(2000, 700); Beep(0, 400);
	}*/
}