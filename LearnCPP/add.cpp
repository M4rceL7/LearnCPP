#include "add.h"
#include <iostream>

int getInteger()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;
	return x;

}

int add(int x, int y)
{
	return x + y;
}

