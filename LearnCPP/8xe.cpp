#include "8xe.h"
#include "constants.h"
#include "random.h"
#include <iostream>
#include <limits>

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Gets tower height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns the current ball height after "seconds" seconds
void calculateBallHeight(double towerHeight)
{
	for (int seconds{ 0 }; towerHeight >= 0.0; ++seconds)
	{
		// Using formula: s = (u * t) + (a * t^2) / 2
	// here u (initial velocity) = 0, so (u * t) = 0
		const double fallDistance{ Constants::gravity * (seconds * seconds) / 2.0 };
		const double ballHeight{ towerHeight - fallDistance };

		if (ballHeight > 0.0)
		{
			std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
		}		
		else
		{
			std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
			break;
		}
					
	}
}

bool isPrime(int x)
{
	if (x <= 1) 
		return false;
	if (x == 2)
		return true;
	if (x % 2 == 0)
		return false;

	for (int test{ 3 }; test*test < x; test += 2)
	{
		if (x % test == 0) // if x is evenly divisible
			return false;  // then this number isn't prime
	}

	return true; // if we didn't find any divisors, then x must be prime
}

int guessedNumber(int min, int max)
{
	int num{};
	while (true)
	{
		std::cin >> num;
		if (num > max || num < min)
		{
			std::cout << "Invalid number, please try again.\n";
			std::cin.clear();
			ignoreLine();
		}
		else
		{
			return num;
		}
	}
	ignoreLine();
	return num;
}

char playAgain()
{
	while (true)
	{
		char playAgain{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> playAgain;

		ignoreLine();

		
		switch (playAgain)
		{
		case 'y': return true;
		case 'n': return false;
		}
	}
	
}

void highLowGame(int min, int max, int numGuesses) 
{
	bool continuep {true};
	while (continuep)
	{
		const int numberToGuess{ Random::get(min, max) };
		bool Won{ false };
		std::cout << "Let's play a game. Im thinking of a number between " << min << " and " << max << ". "
			<< "You have " << numGuesses << " tries to guess what is is.\n";

		for (int i{ 1 }; i <= numGuesses; ++i)
		{
			std::cout << "Guess #" << i << ": ";
			int numberGuessed{};
			numberGuessed = guessedNumber(min, max);

			if (numberGuessed == numberToGuess)
			{
				Won = true;
				break;
			}
			if (numberGuessed > numberToGuess)
			{
				std::cout << "Your guess it to high.\n";
			}
			if (numberGuessed < numberToGuess)
			{
				std::cout << "Your guess is to low.\n";
			}
		}
		if (Won)
		{
			std::cout << "Correct! You Win!\n";
		}
		else
		{
			std::cout << "Sorry, you lose. The correct number was " << numberToGuess << ".\n";
		}
		if (!playAgain())
		{
			break;
		}
		
	}
	std::cout << "Thank you for playing.\n";

}