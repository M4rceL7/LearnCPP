#include "Core/Core.h"
#include "Core/ConstantsAndStrings.h"
#include <iostream>

//Debuging
int readNumber()
{
    std::cout << "Please enter a number: ";
    int x{};
    std::cin >> x;

    return x;
}

void writeAnswer(int x)
{
    std::cout << "The sum is: " << x << '\n';
}

//Fundamental Data Types


int main()
{
//Debuging
    /*
     int x { readNumber() };
     int y { readNumber() };
     writeAnswer(x + y);
     */


//Fundamental Data Types
    
    //Core::InputTwoNumbers();
    //Core::TimeForBallDrop();

//Constants and Strings

    //ConstantsAndStrings::EnterTwoNames();

    constexpr int maryApples { 3 };
    std::cout << "Mary has " << ConstantsAndStrings::getQuantityPhrase(maryApples) << ' '
              << ConstantsAndStrings::getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << ConstantsAndStrings::getQuantityPhrase(numApples) << ' '
              << ConstantsAndStrings::getApplesPluralized(numApples) << ".\n";
    
	return 0;
}