#include <iostream>

namespace _2x
{
	int readNumber()
	{
		std::cout << "Input any number: ";
		int number{};
		std::cin >> number;

		return number;
	}

	void writeAnswer(int output)
	{
		std::cout << "The output is: " << output << '\n';
	}
}