#include "5xe.h"
#include <iostream>
#include <string>
#include <string_view>

std::string namePerson(int num)
{
	std::cout << "Enter the name of person #" << num << ": ";
	std::string name{};
	std::getline(std::cin >> std::ws, name);

	return name;
}

int agePerson(std::string_view name)
{
	std::cout << "Enter the age of " << name << ": ";
	int age{};
	std::cin >> age;

	return age;
}

void printWhoIsOlder(std::string_view person1, int age1, std::string_view person2, int age2 ) 
{
	if (age1 == age2)
	{
		std::cout << person1 << " (age " << age1 << ") and " << person2 << " (age " << age2 << ") are the same age .\n";
	}
	else if (age1 > age2)
	{
		std::cout << person1 << " (age " << age1 << ") is older than " << person2 << " (age " << age2 << ") .\n";
	}
	else
	{
		std::cout << person2 << " (age " << age2 << ") is older than " << person1 << " (age " << age1 << ") .\n";
	}
}