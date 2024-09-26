#include <cassert>
#include <iostream>
#include <random>
#include "Core/ConstantsAndStrings.h"
#include "Core/Core.h"

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

//Control Flow
bool isPrime(int x)
{
    if (x <= 1) return false;
    for (int i = 2; i <= std::sqrt(x); i++) {
        if (x % i == 0) return false;
    }
    return true;
    
}

int RGGGenerator (int min, int max)
{
    // Create a random number engine
    std::mt19937 generator(std::random_device{}());

    // Define the distribution
    std::uniform_int_distribution<int> distribution(min, max);
    int random_number = distribution(generator);
    return random_number;
    
}

void WantToContinueRGG ();

void RandomGuessGameRGG ()
{
    constexpr int min {1};
    constexpr int max {100};
    int number_to_guess {RGGGenerator(min, max)};
    int number_of_guesses {7};
    int guessed_number {};

    std::cout << "Let's play a game. I'm thinking of a number between " << min <<
         " and " << max <<". You have 7 tries to guess what it is." << "\n";
    std::cout << "If you wanna Leave the Game write (-1). \n";

    for (int i {0}; i < number_of_guesses; i++)
    {
        
        std::cin >> guessed_number;
        if (guessed_number == -1)
        {
            exit(EXIT_SUCCESS);
        }
        
        if (guessed_number > max)
        {
            std::cout << "Guessed number is over the allowed MAX, PLS try again. \n";
            i--;
        }
        else if (guessed_number < min)
        {
            std::cout << "Guessed number is under the allowed MIN, PLS try again. \n";
            i--;
        }
        else if (guessed_number == number_to_guess)
        {
            std::cout << "Correct! You win! \n";
            WantToContinueRGG();
        }
        else if (guessed_number < number_to_guess)
        {
            std::cout << "Your guess is too low. \n";
            number_of_guesses --;
            std::cout << "You have " << number_of_guesses << " guesses left\n";
            
        } else if (guessed_number > number_to_guess)
        {
            std::cout << "Your guess is too high. \n";
            number_of_guesses --;
            std::cout << "You have " << number_of_guesses << " guesses left\n";
            
        }
    }
    std::cout << "Sorry, you lose. The correct number was " << number_to_guess << " . \n";
    WantToContinueRGG();
    
}

void WantToContinueRGG ()
{
    char answer {};
    
    while (true)
    {
        std::cout << "Do you want to continue? [Y/N] \n";
        std::cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            RandomGuessGameRGG();
        }else if (answer == 'N' || answer == 'n')
        {
            std::cout << "Thank you for playing!";
            exit(EXIT_SUCCESS);
        }
        else
        {
            std::cout << "Please answer with (Y/y) for yes and with (N/n) for no. \n";
        }
    }
}



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

   /* constexpr int maryApples { 3 };
    std::cout << "Mary has " << ConstantsAndStrings::getQuantityPhrase(maryApples) << ' '
              << ConstantsAndStrings::getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << ConstantsAndStrings::getQuantityPhrase(numApples) << ' '
              << ConstantsAndStrings::getApplesPluralized(numApples) << ".\n";
              */

    //Control Flow
    /*assert(!isPrime(0)); // terminate program if isPrime(0) is true
    assert(!isPrime(1));
    assert(isPrime(2));  // terminate program if isPrime(2) is false
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";*/
    
    //Control Flow RGG
    RandomGuessGameRGG();
    
    
    
	return 0;
}