#include "ConstantsAndStrings.h"
#include <iostream>
#include <string>
#include <string_view>

using namespace std;
namespace ConstantsAndStrings
{
    void EnterTwoNames () {
        string firstName {};
        string secondName {};

        int age1 {};
        int age2 {};

       int person_number {1};

        cout << "Enter the name of person #"<< person_number << " : ";
        person_number++;
        getline(cin >> ws ,firstName);
        cout << "Enter the age of " << firstName << ": ";
        cin >> age1;
    
        cout << "Enter the name of person #"<< person_number << " : ";
        person_number++;
        getline (cin >> ws , secondName);
        cout << "Enter the age of " << secondName << ": ";
        cin >> age2;

        (age1 > age2) ? cout << firstName << " ( age " << age1 << " ) is older than "
                             << secondName << " age ( " << age2 << " ) \n" :
        
                        cout << secondName << " age ( " << age2 << " ) is older than "
                             << firstName << " ( age " << age1 << " ) \n";
    }

    constexpr string getQuantityPhrase(int quantity)
    {
        string phrase{};

        if (quantity < 0) phrase = "negative" ;
        else if (quantity == 0) phrase = "no" ;
        else if (quantity == 1) phrase = "a single" ;
        else if (quantity == 2) phrase = "a couple of" ;
        else if (quantity == 3) phrase = "a few" ;
        else if (quantity > 3)  phrase = "many" ;
        
        return phrase;
    }

    constexpr string getApplesPluralized(int amount)
    {
        return (amount == 1) ? "apple" : "apples";
    }
}


