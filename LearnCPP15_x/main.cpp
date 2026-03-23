#include <iostream>
#include <string>
#include <string_view>
#include "random.h"


class Monster
{
public:
	enum Type
	{
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,
		maxMonsterTypes,

	};

	Monster(Type monster, std::string name, std::string roar, int hp)
		: m_type{ monster }, m_name{ name },
		m_roar{ roar }, m_hitPoints{ hp }
	{}

	constexpr std::string_view getTypeString() const 
	{
		switch (m_type)
		{
		case Type::dragon: return "Dragon";
		case Type::goblin: return "Goblin";
		case Type::ogre: return "Ogre";
		case Type::orc: return "Orc";
		case Type::skeleton: return "Skeleton";
		case Type::troll: return "Troll";
		case Type::vampire: return "Vampire";
		case Type::zombie: return "Zombie";
		default: return "Unknonw type";
		}
	}

	void print()
	{
		std::cout << m_name << " the " << getTypeString();

		if (m_hitPoints <= 0)
		{
			std::cout << " is dead.\n";
		}
		else
		{
			std::cout << " has " << m_hitPoints << " hit points and says "
				<< m_roar << '\n';
		}
	}

private:
	Type m_type{};
	std::string m_name{ "???" };
	std::string m_roar{ "???" };
	int m_hitPoints{ 1 };
};

namespace MonsterGenerator
{
	

	std::string getName(int number)
	{
		switch (number)
		{
		case 0: return "Name1";
		case 1: return "Name2";
		case 2: return "Name3";
		case 3: return "Name4";
		case 4: return "Name5";
		case 5: return "Name6";
		default: return "Olaf";
		}
	}

	std::string getRoar(int num)
	{
		switch (num)
		{
		case 0: return "ROAR1";
		case 1: return "ROAR2";
		case 2: return "ROAR3";
		case 3: return "ROAR4";
		case 4: return "ROAR5";
		case 5: return "ROAR6";
		default: return "OLAAF";
		}
	}

	Monster generate()
	{
		return Monster{
			static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterTypes)),
			getName(Random::get(0,5)),
			getRoar(Random::get(0,5)),
			Random::get(1,100)
		};
	}


}


int main()
{
	Monster m{ MonsterGenerator::generate() };
	m.print();

	return 0;
}