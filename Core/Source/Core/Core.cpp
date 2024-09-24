#include "Core.h"

#include <iostream>

namespace Core {


    //Fundamental Datatypes
    void InputTwoNumbers () {
        double x {};
        double y {};
        char operation {};
        
        std::cout << "Enter number 1: ";
        std::cin >> x;
        
        std::cout << "Enter number 2: ";
        std::cin >> y;
        
        std::cout << "Enter math operation: ";
        std::cin >> operation;
        bool checkoperator = 1;
            while (checkoperator) {
             switch (operation) {
                    case '+':
                    std::cout << x + y << "\n";
                    checkoperator = 0;
                    break;
                    
                    case '-':
                    std::cout << x - y << "\n";
                    checkoperator = 0;
                    break;
                    
                    case '*':
                    std::cout << x * y << "\n";
                    checkoperator = 0;
                    break;
                    
                    case '/':
                    std::cout << x / y << "\n";
                    checkoperator = 0;
                    break;
                    
                    default:
                    std::cout << "Wrong operation, please Enter a new 1: " << "\n";
                    std::cin >> operation;
                    break;
                    
             }
                
        }
        
    }

    void TimeForBallDrop () {
        double height {};
        double fallen_distance{};
        double seconds {0};
        const double gravity {9.8};
        
        std::cout << "Enter the height of the tower in meters: ";
        std::cin >> height;
        fallen_distance = height;
        std::cout << "At " << seconds << " seconds, the ball is at height: " << height << "\n";
        while (fallen_distance >= 0) {
                seconds += 1;
                fallen_distance = height - (gravity * (seconds * seconds) / 2.0);
            
            if (fallen_distance < 0) {
                std::cout << "At " << seconds << " seconds the ball is on the ground." << "\n";
                break;
            }
            std::cout << "At " << seconds << " seconds, the ball is at height: " << fallen_distance << "\n";
                
                
            
            
        }
        
        
        
    }
    
    //
    
    
    
    
    
}