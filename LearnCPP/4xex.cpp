#include "4xex.h"
#include <iostream>

double userInputNum()
{
	std::cout << "Enter a double value: ";
	double num{};
	std::cin >> num;

	return num;

}

char userInputChar()
{
	std::cout << "Enter +, -, *, or /: ";
	char sym{};
	std::cin >> sym;

	return sym;
}

void printResult(double num1, double num2, char op)
{
	if (op == '+')
	{
		std::cout << num1 << " " << op << " " << num2 << " is " << num1 + num2 << '\n';
	}
	else if (op == '-')
	{
		std::cout << num1 << " " << op << " " << num2 << " is " << num1 - num2 << '\n';
	}
	else if (op == '*')
	{
		std::cout << num1 << " " << op << " " << num2 << " is " << num1 * num2 << '\n';
	}
	else if (op == '/')
	{
		std::cout << num1 << " " << op << " " << num2 << " is " << num1 / num2 << '\n';
	}
	else
	{
		return;
	}
}

double towerHight()
{
	std::cout << "Enter height of tower: ";
	double height{};
	std::cin >> height;

	return height;
}

void calcDistanceFallen(double towerHeight, int seconds)
{
	double gravity{ 9.8 };
	double distanceFallen{ towerHeight - (gravity * (seconds*seconds) /2) };

	printDistanceFallen(distanceFallen, seconds);
}

void printDistanceFallen(double distanceFallen, int seconds)
{
	if (distanceFallen <= 0.0)
		std::cout << "At " << seconds << " seconds, the ball is on the ground." << '\n';
	else
		std::cout << "At " << seconds << " seconds, the ball is at height: " << distanceFallen << " meters" << '\n';
}
