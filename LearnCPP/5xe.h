#pragma once
#include <string>

std::string namePerson(int num);

int agePerson(std::string_view name);

void printWhoIsOlder(std::string_view person1, int age1, std::string_view person2, int age2);