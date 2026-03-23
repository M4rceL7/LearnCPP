#include <iostream>
#include <cassert>
#include <vector>
#include <string_view>
#include "random.h"

namespace Items
{
	enum Type: int
	{
		health_potion,
		torch,
		arrow,
		max_items
	};
}

std::string_view getItemNamePlural(Items::Type type)
{
	switch (type)
	{
	case Items::health_potion:  return "health potions";
	case Items::torch:          return "torches";
	case Items::arrow:          return "arrows";

	default:                    return "???";
	}
}

std::string_view getItemNameSingular(Items::Type type)
{
	switch (type)
	{
	case Items::health_potion:  return "health potion";
	case Items::torch:          return "torch";
	case Items::arrow:          return "arrow";

	default:                    return "???";
	}
}

void printInventoryItem(const std::vector<int>& inv, Items::Type type)
{
	bool plural{ inv[static_cast<std::size_t>(type)] != 1 };
	std::cout << "You have " << inv[static_cast<std::size_t>(type)] << ' ';
	std::cout << (plural ? getItemNamePlural(type) : getItemNameSingular(type)) << '\n';
}

template <typename T>
T countItems(const std::vector<T>& arr)
{
	int total{ 0 };
	for (const auto& num : arr)
	{
		total += num;
	}
	return total;
}

template <typename T>
std::pair<std::size_t, std::size_t> findMinMaxIndices(const std::vector<T>& v)
{
	// Assume element 0 is the minimum and the maximum
	std::size_t minIndex{ 0 };
	std::size_t maxIndex{ 0 };

	// Look through the remaining elements to see if we can find a smaller or larger element
	for (std::size_t index{ 1 }; index < v.size(); ++index)
	{
		if (v[index] < v[minIndex])
			minIndex = index;
		if (v[index] > v[maxIndex])
			maxIndex = index;
	}

	return { minIndex, maxIndex };
}

template <typename T>
void printArray(const std::vector<T>& v)
{
	bool comma{ false };
	std::cout << "With array ( ";
	for (const auto& e : v)
	{
		if (comma)
			std::cout << ", ";

		std::cout << e;
		comma = true;
	}
	std::cout << " ):\n";
}

//-------------------------------------------

namespace WordList
{
	std::vector<std::string_view> words{"mystery", "broccoli", "account", "spaghetti", "opinion", "meeperinio", "beautiful", "distance", "mlem", "luggage"};

	std::string_view getRandomWord()
	{
		
		return words[Random::get(0, (std::ssize(words) - 1))];
	}
	
}

namespace Settings
{
	constexpr int wrongGuessesAllowed{ 9 };
}

class Session
{
private:
	// Game session data
	std::string_view m_word{ WordList::getRandomWord() };
	int m_wrongGuessesLeft{ Settings::wrongGuessesAllowed };
	std::vector<bool> m_letterGuessed{ std::vector<bool>(26) };

	std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32) - 1); }

public:
	std::string_view getWord() const { return m_word; }

	int wrongGuessesLeft() const { return m_wrongGuessesLeft; }
	void removeGuess() { --m_wrongGuessesLeft; }

	bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
	void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }

	bool isLetterInWord(char c) const
	{
		for (auto ch : m_word) // step through each letter of word
		{
			if (ch == c)
				return true;
		}

		return false;
	}

	bool won()
	{
		for (auto c : m_word) // step through each letter of word
		{
			if (!isLetterGuessed(c))
				return false;
		}

		return true;
	}
};

void draw(const Session& s)
{
	std::cout << '\n';

	std::cout << "The word: ";
	for (auto c : s.getWord()) // step through each letter of word
	{
		if (s.isLetterGuessed(c))
			std::cout << c;
		else
			std::cout << '_';
	}

	std::cout << "   Wrong guesses: ";
	for (int i = 0; i < s.wrongGuessesLeft(); ++i)
		std::cout << '+';


	for (char c = 'a'; c <= 'z'; ++c)
		if (s.isLetterGuessed(c) && !s.isLetterInWord(c))
			std::cout << c;

	std::cout << '\n';
}

char getGuess(const Session& s)
{
	while (true)
	{
		std::cout << "Enter your next letter: ";

		char c{};
		std::cin >> c;

		// If user did something bad, try again
		if (!std::cin)
		{
			// Fix it
			std::cin.clear();
			std::cout << "That wasn't a valid input.  Try again.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// Clear out any extraneous input
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// If the user entered an invalid char, try again
		if (c < 'a' || c > 'z')
		{
			std::cout << "That wasn't a valid input.  Try again.\n";
			continue;
		}

		// If the letter was already guessed, try again
		if (s.isLetterGuessed(c))
		{
			std::cout << "You already guessed that.  Try again.\n";
			continue;
		}

		// If we got here, this must be a valid guess
		return c;
	}
}

void handleGuess(Session& s, char c)
{
	s.setLetterGuessed(c);

	if (s.isLetterInWord(c))
	{
		std::cout << "Yes, '" << c << "' is in the word!\n";
		return;
	}

	std::cout << "No, '" << c << "' is not in the word!\n";
	s.removeGuess();
}

int main()
{
	std::cout << "Welcome to C++man (a variant of Hangman)\n";
	std::cout << "To win: guess the word.  To lose: run out of pluses.\n";

	Session s{};

	while (s.wrongGuessesLeft() && !s.won())
	{
		draw(s);
		char c{ getGuess(s) };
		handleGuess(s, c);
	}

	// Draw the final state of the game
	draw(s);

	if (!s.wrongGuessesLeft())
		std::cout << "You lost!  The word was: " << s.getWord() << '\n';
	else
		std::cout << "You won!\n";

	return 0;

	std::vector<int> inventory{ 1,5,10 };
	assert(std::ssize(inventory) == Items::max_items);

	for (int i = 0; i < Items::max_items; ++i)
	{
		auto item{ static_cast<Items::Type>(i) };
		printInventoryItem(inventory, item);
	}

	std::cout << countItems(inventory) << "Items\n";



	std::vector v1{ 3, 8, 2, 5, 7, 8, 3 };
	printArray(v1);

	auto m1{ findMinMaxIndices(v1) };
	std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
	std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';

	std::cout << '\n';

	std::vector v2{ 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
	printArray(v2);

	auto m2{ findMinMaxIndices(v2) };
	std::cout << "The min element has index " << m2.first << " and value " << v2[m2.first] << '\n';
	std::cout << "The max element has index " << m2.second << " and value " << v2[m2.second] << '\n';

	std::vector<int> v3{ };
	std::cout << "Enter numbers to add (use -1 to stop): ";

	while (true)
	{
		int input{};
		std::cin >> input;
		if (input == -1)
			break;

		if (!std::cin) // if the previous extraction failed
		{
			std::cin.clear(); // put us back in 'normal' operation mode
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
			continue;
		}

		v3.push_back(input);
	}

	// If the array is empty
	if (v3.size() == 0)
	{
		std::cout << "The array has no elements\n";
	}
	else
	{
		printArray(v3);

		auto m1{ findMinMaxIndices(v3) };
		std::cout << "The min element has index " << m1.first << " and value " << v3[m1.first] << '\n';
		std::cout << "The max element has index " << m1.second << " and value " << v3[m1.second] << '\n';
	}


	return 0;
	/*std::vector evenNum{2,4,6,8,10,12};
	const std::vector valuesDouble{1.2, 3.4, 5.6, 7.8 };
	const std::vector<std::string_view> names {"Alex", "Brad", "Charles", "Dave"};
	std::vector singleNum{ 12 };
	std::vector<int> nums(12);*/
}