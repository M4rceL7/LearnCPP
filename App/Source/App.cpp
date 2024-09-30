#include <cassert>
#include <iostream>
#include <random>
#include <algorithm>
#include <format>
#include <cmath>
//#include "Core/ConstantsAndStrings.h"
//#include "Core/Core.h"


//Try around

class Log
{
    public:
    
    enum Level
    {
        LevelError, LevelWarning, LevelInfo
    };
    

    private:

    Level m_LogLevel = LevelInfo;
        
    public:

    void setLogLevel(Level Level)
    {
        m_LogLevel = Level;
    }

    void ErrorM (const char* message)
    {
        if (m_LogLevel >= LevelError)
            std::cout << "[ERROR] : " << message << '\n';
    }

    void WarnM (const char* message)
    {
        if (m_LogLevel >= LevelWarning)
            std::cout << "[WARNING] : " << message << '\n';
    }

    void InfoM (const char* message)
    {
        if (m_LogLevel >= LevelInfo)
            std::cout << "[INFO] : " << message << '\n';
    }
};

//Debugging
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

//Function Overloading and Function Templates

template <typename T>
T add(T x, T y)
{
    return x + y;
}

template <typename T>
T mult(T x, int y)
{
    return x * y;
}

template <typename T, typename U>
auto sub (T x, U y)
{
    return x - y;
}

//Reference and Pointers

void sort2 (int& lesser, int& greater) 
{
     if (greater >= lesser) return;

    std::swap(lesser, greater);
     
}

//Enums and Structs

struct Monster
{

    enum Type
    {
        ogre,
        dragon,
        orc,
        giant_spider,
        slime,
    };

    Type type {};
    std::string m_name {};
    int m_health {};

    
    Monster(Type mtype ,std::string name, int health)
    {
        type = mtype;
        m_name = name;
        m_health = health;
        
    }
    
};

constexpr std::string_view getMonsterTypeString(Monster::Type type)
{
    switch (type)
    {
    case Monster::ogre:          return "Ogre";
    case Monster::dragon:        return "Dragon";
    case Monster::orc:           return "Orc";
    case Monster::giant_spider:  return "Giant Spider";
    case Monster::slime:         return "Slime";
    }

    return "Unknown";
}

void printMonster (const Monster& monster)
{
    std::cout << "This "  << getMonsterTypeString(monster.type) <<
        " is named " << monster.m_name << " and has " << monster.m_health << " HP.\n";
} 

template <typename T>
class Triad
{
    public:
    T first {};
    T second {};
    T third {};

    Triad (T first, T second, T third )
    {
        this->first = first;
        this->second = second;
        this -> third = third;
    }
    
};

template <typename T>
void print (const Triad<T>& triad)
{
    std::cout << "[ " << triad.first << ", " << triad.second << ", " << triad.third << " ]\n";    
}

//Classes

class Point2d
{
public:
    
    double m_x {0.0};
    double m_y {0.0};

    Point2d () = default;

    Point2d (double x, double y)
        : m_x {x}, m_y {y}
    {
        
    }

    void print ()
    {
        std::cout << "( " << m_x << ", " << m_y << " )\n";
    }

    double distanceTo (const Point2d& point) const
    {
       return std::sqrt((m_x - point.m_x)*(m_x - point.m_x) +
                            (m_y - point.m_y)*(m_y - point.m_y));
    }
};


int main() /////////////////////////////////////////////////////////////////////////////////////
{

//Classes

    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // Point2d third{ 4.0 }; // should error if uncommented

    first.print();
    second.print();

    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';

//Enums and Structs

   /* Monster ogre = {Monster::ogre,"Ogre", 150};
    Monster dragon = {Monster::dragon, "Dragon", 2000};
    Monster slime = {Monster::slime, "Slimy", 2};
    printMonster(ogre);
    printMonster(dragon);
    printMonster(slime); */

    /*Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
    print(t1);

    Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
    print(t2);*/    
    
//Reference and Pointers

   /* int x { 7 };
    int y { 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7*/
//Function Overloading and Function Templates

    /*std::cout << add(2, 3) << '\n';
    std::cout << add(1.2, 3.4) << '\n';
    std::cout << mult(2, 3) << '\n';
    std::cout << mult(1.2, 3) << '\n';
    std::cout << sub(3, 2) << '\n';
    std::cout << sub(3.5, 2) << '\n';
    std::cout << sub(4, 1.5) << '\n';*/

    
//Debugging
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
    //RandomGuessGameRGG();



    //Try around

    std::cout << "---------------------------------------Try Out Area------------------------------------------- \n ";
    Log log;
    log.setLogLevel(Log::LevelWarning);
    log.WarnM("Warning");
    std::cin.get();
    
    
	return 0;
}
