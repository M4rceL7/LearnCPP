#include <iostream>
#include <array>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <cassert>

#include "random.h"

//----------------------------------------Potion Emperium---------------------------------------------//

namespace Potion
{
	enum Type
	{
		healing,
		mana,
		speed,
		invisibility,
		max_potions,
	};
	constexpr std::array types{ healing, mana, speed, invisibility };

	constexpr std::array<int, max_potions> cost{20, 30, 12, 50};
	constexpr std::array<std::string_view, max_potions> name{ "healing", "mana", "speed", "invisibility" };

	static_assert(std::ssize(types) == max_potions); 
	static_assert(std::ssize(cost) == max_potions);
	static_assert(std::ssize(name) == max_potions);
}

class Player
{
private:
	static constexpr int s_minStartingGold{ 80 };
	static constexpr int s_maxStartingGold{ 120 };

	std::string m_name{};
	std::array<int, Potion::max_potions> m_inventory{};
	int m_gold{};

public:
	explicit Player() :
		m_gold{ Random::get(s_minStartingGold, s_maxStartingGold) }
	{
	}

	int getGold() const { return m_gold; }
	int getInventory(Potion::Type type) const { return m_inventory[type]; }

	void setName()
	{
		std::cout << "Enter your name: ";
		std::getline(std::cin >> std::ws, m_name);
		std::cout << "Hello, " << m_name << ", you have " << m_gold << " gold.\n";
		std::cout << "\n";
	}

	bool addToInventory(Potion::Type type)
	{
		if (m_gold < Potion::cost[type])
		{
			std::cout << "You dont have enough Gold!\n";
			return false;
		}
		m_gold -= Potion::cost[type];
		++m_inventory[type];
		
			
		
	}

	int charNumToInt(char c)
	{
		return c - '0';
	}

	Potion::Type purchase()
	{
		std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";

		char input{};
		while (true)
		{
			std::cin >> input;
			if (!std::cin) // handle bad input
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}

			// If there is extraneous input, treat as failure case
			if (!std::cin.eof() && std::cin.peek() != '\n')
			{
				std::cout << "I didn't understand what you said.  Try again: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any extraneous input
				continue;
			}

			if (input == 'q')
			{
				return Potion::max_potions;
			}

			int num{ charNumToInt(input) };
			if (num >= 0 && num < Potion::max_potions)
			{
				return static_cast<Potion::Type>(num);
			}

			std::cout << "That is an invalid input.   Try again: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
};

void shop(Player &player)
{
	while (true)
	{
		std::cout << "Here is out selection for today: \n";
		for (auto i : Potion::types)
		{
			std::cout << i << ") " << Potion::name[i] << " costs " << Potion::cost[i] << '\n';
		}

		Potion::Type potionToBuy{ player.purchase() };
		if (potionToBuy == Potion::max_potions)
		{
			return;
		}

		bool success{ player.addToInventory(potionToBuy) };
		if (!success)
		{
			std::cout << "You cant afford that.\n\n";
		}
		else
		{
			std::cout << "You purchased a potion of " << Potion::name[potionToBuy] << ".  You have " << player.getGold() << " gold left.\n\n";
		}
	}
}

void printInventory(Player& player)
{
	std::cout << "Your inventory contains:\n";
	for (auto index : Potion::types)
	{
		if (player.getInventory(index) != 0)
		{
			std::cout << player.getInventory(index) << "x potion of " << Potion::name[index] << '\n';
		}
	}

	std::cout << "You escaped with " << player.getGold() << " gold remaining.\n";
}

//------------------------------BlackJack---------------------------------------------------------------------------//

namespace Settings
{
	constexpr int playerScoreLimit{ 21 };
	constexpr int dealerScoreLimit{ 17 };
	constexpr int maxPoints{ 21 };
}

struct Card
{
	enum Ranks
	{
		rank_ace,
		rank_2,
		rank_3,
		rank_4,
		rank_5,
		rank_6,
		rank_7,
		rank_8,
		rank_9,
		rank_10,
		rank_jack,
		rank_queen,
		rank_king,

		max_ranks,
	};

	enum Suits
	{
		suit_club,
		suit_diamond,
		suit_heart,
		suit_spade,

		max_suits,
	};

	static constexpr std::array allRanks{ rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
	static constexpr std::array allSuits{ suit_club, suit_diamond, suit_heart, suit_spade };

	

	Ranks rank{};
	Suits suit{};

	friend std::ostream& operator<<(std::ostream& out, const Card& card)
	{

		static constexpr std::array ranks{ 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
		static constexpr std::array suits{ 'C', 'D', 'H', 'S' };
		out << ranks[card.rank] << suits[card.suit];
			return out;
	}

	int value() const
	{
		static constexpr std::array cardValues{ 11,2,3,4,5,6,7,8,9,10,10,10,10 };
		return cardValues[rank];
	}
};

constexpr int deckSize{ 52 };
class Deck
{
private:
	
	std::array<Card, deckSize> m_deck{};
	std::size_t m_nextCardIndex{ 0 };

public:
	Deck()
	{
		for (auto suit : Card::allSuits)
		{
			for (auto rank : Card::allRanks)
			{
				m_deck[m_nextCardIndex++] = Card{ rank, suit };
			}
		}
		m_nextCardIndex = 0;
	}

	void shuffle()
	{
		std::shuffle(m_deck.begin(), m_deck.end(), Random::mt);
		m_nextCardIndex = 0;
	}

	Card dealCard()
	{
		assert(m_nextCardIndex != deckSize && "Deck ran out of cards");
		m_nextCardIndex++;
		return m_deck[m_nextCardIndex];
	}
};

namespace BlackJack
{
	struct Player
	{
		int score{};
	};
}

bool checkIfPlayerWon(BlackJack::Player& player, BlackJack::Player& dealer)
{
	if ((player.score > dealer.score && player.score <= Settings::playerScoreLimit) || dealer.score > Settings::maxPoints)
	{
		return true;
	}
	return false;
}

bool playerTurn(BlackJack::Player& player, Deck& deck)
{
	while (player.score < Settings::playerScoreLimit)
	{
		std::cout << "(h) to hit, or (s) to stand: ";
		char input{};
		std::cin >> input;
		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (input == 'h')
		{
			Card flippedCard{ deck.dealCard() };
			player.score += flippedCard.value();
			std::cout << "You were dealt " << flippedCard << ".   You now have: " << player.score << '\n';
			if (player.score > Settings::playerScoreLimit)
			{
				std::cout << "You went bust!\n";
				return false;
			}
		}
		if (input == 's')
		{
			return true;
		}
		continue;
	}
}

void dealerTurn(BlackJack::Player& dealer, Deck& deck)
{
	while (dealer.score < Settings::dealerScoreLimit)
	{
		Card flippedCard{ deck.dealCard() };
		dealer.score += flippedCard.value();
		std::cout << "The dealer flips a " << flippedCard << ".   They now have: " << dealer.score << '\n';
	}
}

void game(BlackJack::Player& player, BlackJack::Player& dealer, Deck& deck)
{
	deck.shuffle();

	dealer.score += deck.dealCard().value();

	std::cout << "The dealer is showing: " << dealer.score << '\n';

	player.score += (deck.dealCard().value()) + deck.dealCard().value();

	std::cout << "You have score: " << player.score << '\n';

	if (dealer.score >= Settings::maxPoints && player.score <= Settings::playerScoreLimit)
	{
		std::cout << "You Won!\n";
	}
	if (dealer.score == Settings::maxPoints || player.score > Settings::maxPoints)
	{
		std::cout << "You Lost!\n";
	}

	if (playerTurn(player, deck))
	{
		dealerTurn(dealer, deck);
	}

	if (checkIfPlayerWon(player, dealer))
	{
		std::cout << "You Win!\n";
	}
	else
	{
		std::cout << "You Lost!\n";
	}
}


int main()
{
	while (true)
	{
		std::cout << "Which game would you like to play? \n1 for Potion imperium.\n2 for Blackjack.\n";
		int d{};
		std::cin >> d;

		if (d == 1)
		{
			std::cout << "Welcome to Roscoe's potion emporium!\n";

			Player player1{};

			player1.setName();

			shop(player1);

			std::cout << '\n';

			printInventory(player1);

			std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
		}

		if (d == 2)
		{
			BlackJack::Player dealer{};
			BlackJack::Player player{};
			Deck deck{};

			game(player, dealer, deck);

		}

		std::cout << "Would you like to play again ? (y/n): ";
		char c{};
		std::cin >> c;
		if (c == 'y')
		{
			continue;
		}
		else
		{
			break;
		}
	}
	
	return 0;
}


