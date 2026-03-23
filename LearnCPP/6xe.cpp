#include "6xe.h"
#include <iostream>
#include <iomanip>
#include <climits>
#include <format>
#include <string>

std::string getQuantityPhrase(int num)
{
	if (num < 0)
	{
		return std::string("negative");
	}
	else if (num == 0)
	{
		return std::string("no");
	}
	else if (num == 1)
	{
		return std::string("a single");
	}
	else if (num == 2)
	{
		return std::string("a couple");
	}
	else if (num == 3)
	{
		return std::string("a few");
	}
	else
	{
		return std::string("many");
	}
}

std::string getApplesPluralized(int num)
{
	return ((num == 1) ? std::string("apple") : std::string("apples"));
}