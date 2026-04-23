#include "constants.h"
#include "io.h"
#include "add.h"
#include "4xex.h"
#include "5xe.h"
#include "6xe.h"
#include "8xe.h"
#include "Creature.h"
#include "Point2D.h"
#include "IntArray.h"

#include <iostream>
#include <iomanip>
#include <climits>
#include <format>
#include <string>
#include <cassert>
#include <limits>
#include <random>
#include <chrono>
#include <vector>
#include <array>
#include <functional>
#include <memory>
#include <exception>


using namespace std::string_literals;		//s suffix
using namespace std::string_view_literals; //sv suffix
//s_ suffix for local static variables
//g_ suffix for globals
//m_ for private member variables

//const std::string& getName() const& { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects, returns by reference
//std::string        getName() const&& { return m_name; } // && qualifier overloads function to match only rvalue implicit objects, returns by value



//// Return true if the difference between a and b is within epsilon percent of the larger of a and b
//bool approximatelyEqualRel(double a, double b, double relEpsilon)
//{
//	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
//}
//
//// Return true if the difference between a and b is less than or equal to absEpsilon, or within relEpsilon percent of the larger of a and b
//bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
//{
//	// Check if the numbers are really close -- needed when comparing numbers near zero.
//	if (std::abs(a - b) <= absEpsilon)
//		return true;
//
//	// Otherwise fall back to Knuth's algorithm
//	return approximatelyEqualRel(a, b, relEpsilon);
//}
//
//void ignoreLine()
//{
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
//}
//
//// returns true if std::cin has unextracted input on the current line, false otherwise
//bool hasUnextractedInput()
//{
//	return !std::cin.eof() && std::cin.peek() != '\n';
//}
//
//// returns true if extraction failed, false otherwise
//bool clearFailedExtraction()
//{
//	// Check for failed extraction
//	if (!std::cin) // If the previous extraction failed
//	{
//		if (std::cin.eof()) // If the stream was closed
//		{
//			std::exit(0); // Shut down the program now
//		}
//
//		// Let's handle the failure
//		std::cin.clear(); // Put us back in 'normal' operation mode
//		ignoreLine();     // And remove the bad input
//
//		return true;
//	}
//
//	return false;
//}

// T& is an lvalue reference, so this overload will be preferred for lvalues
template <typename T>
constexpr bool is_lvalue(T&)
{
	return true;
}

// T&& is an rvalue reference, so this overload will be preferred for rvalues
template <typename T>
constexpr bool is_lvalue(T&&)
{
	return false;
}

int getint() { return 5; }

// A helper macro (#expr prints whatever is passed in for expr as text)
#define PRINTVCAT(expr) { std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n"); }

int doMath(int first, int second, int third, int fourth); //actual func bellow main()

enum class Animal
{
	pig, chicken, goat, cat, dog, duck,
};

namespace CppLearningTest 
{

	int userInput()
	{
		std::cout << "Enter an integer: ";
		int num{};
		std::cin >> num;

		return num;
	}

	std::string inputName()
	{
		std::cout << "Enter your full name; ";
		std::string name{};
		std::getline(std::cin >> std::ws, name);

		return name;
	}

	int doubleNumber(int number)
	{
		return number * 2;
	}

	constexpr bool isEven(int num)
	{
		return(num % 2) == 0;
	}

	static int accumulate(int x)
	{
		static int s_output{};

		s_output += x;

		return s_output;
	}

	int calculate(int x, int y, char op)
	{
		switch (op)
		{
		case '+':
			return x + y;
		case '-':
			return x - y;
		case '*':
			return x * y;
		case '/':
			return x / y;
		case '%':
			return x % y;
		default:
			std::cout << "calculate(): Unhandled case\n";
			return 0;

		}
	}

	void aToZ()
	{
		char myChar{ 'a'};
		while (myChar <= 'z')
		{
			std::cout << myChar << ' ' << static_cast<int>(myChar) << '\n';
			++myChar;
		}
	}

	int sumTo(int num)
	{
		int output{0};
		for (int x{ 1 }; x <= num; ++x)
		{
			output += x;
		}

		return output;
	}

	void fizzbuzz(int num)
	{
		for (int i{ 1 }; i <= num; ++i)
		{
			bool printed{ false };
			if (i % 3 == 0)
			{
				std::cout << "fizz";
				printed = true;
			}
			if (i % 5 == 0)
			{
				std::cout << "buzz";
				printed = true;
			}
			if (i % 7 == 0)
			{
				std::cout << "pop";
				printed = true;
			}

			if (!printed)
				std::cout << i;

			std::cout << '\n';		
		}
	}

	auto max(auto x, double y)
	{
		return (x > y) ? x : y;
	}

	template<typename T, typename U>
	auto add(T x, U y)
	{
		return x + y;
	}

	template <typename T>
	T mult(T x, int y)
	{
		return x * y;
	}

	template<typename T, typename U>
	auto sub(T x, U y) // auto sub(auto x, auto y)...
	{
		return x + y;
	}

	template <auto N>
	constexpr int factorial()
	{
		static_assert(N >= 0);

		int product{ 1 };
		for (int i{ 2 }; i <= N; ++i)
		{
			product *= i;
		}
		return product;
	}

	void sort2(int& x,int& y)
	{
		if (x > y)
		{
			std::swap(x, y);
		}
	}
	
	static constexpr std::string_view getAnimalName(Animal animal)
	{
		using enum Animal;
		switch (animal)
		{
		case pig: return "pig";
		case chicken: return "chicken";
		case goat: return "goat";
		case cat: return "cat";
		case dog: return "dog";
		case duck: return "duck";
		default: return "unknown animal!";
		}
	}

	static void printNumberOfLegs(Animal animal)
	{
		std::cout << "A " << getAnimalName(animal) << " has ";

		// If C++20 capable, could use `using enum Animal` here to reduce Animal prefix redundancy
		switch (animal)
		{
		case Animal::chicken:
		case Animal::duck:
			std::cout << 2;
			break;

		case Animal::pig:
		case Animal::goat:
		case Animal::cat:
		case Animal::dog:
			std::cout << 4;
			break;

		default:
			std::cout << "???";
			break;
		}

		std::cout << " legs.\n";
	}

}
//namespace Monster
//{
//	enum MonsterType
//	{
//		unknownType, orc, goblin, troll, ogre, skeleton
//	};
//}


const struct Revenue
{
	int adsWatched{0};
	double percentageClicked{0.0};
	double avrgEarnings{0.0};
};

static void printEarnings(const Revenue& revenue)
{
	std::cout << "Ads watched: " << revenue.adsWatched << '\n';
	std::cout << "Percentage clicked: " << revenue.percentageClicked << '\n';
	std::cout << "Avarage earnings: " << revenue.avrgEarnings << '\n';
	std::cout << "Earnings of the day: " << revenue.adsWatched * revenue.avrgEarnings * revenue.percentageClicked << '\n';
}

	
struct Fraction
{
	int numerator{ 0 };
	int denominator{ 1 };
};

Fraction getFraction()
{
	Fraction temp{};
	std::cout << "Enter a value for numerator: ";
	std::cin >> temp.numerator;
	std::cout << "Enter a value for denominator: ";
	std::cin >> temp.denominator;
	std::cout << '\n';

	return temp;
}

constexpr Fraction multiply(const Fraction& f1, const Fraction& f2)
{
	return { f1.numerator * f2.numerator, f1.denominator * f2.denominator };
}

void printFraction(const Fraction& f)
{
	std::cout << f.numerator << '/' << f.denominator << '\n';
}


const struct Monsters
{
	const enum Monstertype
	{
		unknown, ogre, dragon, orc, giant_spider, slime
	};
	Monstertype type{};
	std::string name{" "};
	int health{ 1 };
};

constexpr std::string_view returnNameOfMonsterType(Monsters::Monstertype type)
{

	switch (type)
	{
	case Monsters::ogre: return "Ogre";
	case Monsters::dragon: return "Dragon";
	case Monsters::orc: return "Orc";
	case Monsters::giant_spider: return "Giant Spider";
	case Monsters::slime: return "Slime";
	}

	return "Unknown";
}

void printMonster(const Monsters& monster)
{
	std::cout << "This " << returnNameOfMonsterType(monster.type) <<
		" is named " << monster.name << 
		" and has " << monster.health << " health.\n";
}


template <typename T>
struct Triad
{
	T first{};
	T second{};
	T third{};
};

// If using C++17, we need to provide a deduction guide (not required in C++20)
// A Triad with three arguments of the same type should deduce to a Triad<T>
//template <typename T>
//Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(const Triad<T>& t)
{
	std::cout << '[' << t.first << ", " << t.second << ", " << t.third << ']';
}


const struct IntPair
{
	int num1{};
	int num2{};

	void print()
	{
		std::cout << "Pair(" << num1 << ", " << num2 << ")\n";
	}

	const bool isEqual(const IntPair& equal)
	{
		if (num1 == equal.num1 || num2 == equal.num2)
			return true;

		return false;
	}
};


//const class Point3d
//{
//	int m_x{};
//	int m_y{};
//	int m_z{};
//
//public:
//	void setValues(int x, int y, int z)
//	{
//		m_x = x;
//		m_y = y;
//		m_z = z;
//	}
//
//	void print()
//	{
//		std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">\n";
//	}
//
//	constexpr bool isEqual(const Point3d& point)
//	{
//		if (point.m_x == m_x || point.m_y == m_y || point.m_z == m_z)
//			return true;
//
//		return false;
//	}
//};


const class Ball
{
private:
	std::string m_color{"black"};
	double m_radius{10.0};

public:
	//Ball() = default;
	/*Ball(std::string_view color)
		: m_color {color}
	{}*/
	explicit Ball(double radius)
		:Ball{"black", radius}
		//: m_radius{ radius }
	{}
	 Ball(std::string_view color, double radius = 10.0) 
		: m_color{ color }
		, m_radius{ radius }
	{
	}

	const std::string& getColor()const{return m_color;}

	double getRadius()const { return m_radius; }
};

const void print(const Ball& ball)
{
	std::cout << "Ball (" << ball.getColor() << ", " << ball.getRadius() << ")\n";
}


class Point2d
{
private:
	double m_x {0.0};
	double m_y{ 0.0 };

public:
	Point2d() = default;

	explicit Point2d(double y)
		:m_y{y}
	{}

	explicit Point2d(double x, double y)
		:m_x {x}
		,m_y {y}
	{}

	void print()
	{
		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
	}

	const double distanceTo(const Point2d point) const
	{
		return std::sqrt((m_x - point.m_x) * (m_x - point.m_x) + (m_y - point.m_y) * (m_y - point.m_y));
	}
};


class Calc
{
private:
	int m_value{};
	[[maybe_unused]]static inline int s_test{ 1 }; // basically global member variable

public:
	static int getValueTest() { return s_test; } // for the static member variable, if no object has been created -> std::cout << Calc::getValueTest()...;

	Calc& add(int value) { m_value += value; return *this; } // method chaining // calc.add(5).sub(3).mult(4);
	Calc& sub(int value) { m_value -= value; return *this; }
	Calc& mult(int value) { m_value *= value; return *this; }

	int getValue() const { return m_value; }
};


template <typename T, typename U, typename V>
class Triaded
{
private:
	T m_first{};
	U m_second{};
	V m_third{};

public:
	Triaded(const T& first, const U& second, const V& third)
		: m_first{ first }
		, m_second{ second }
		, m_third{ third }
	{
	}

	const T& first() const { return m_first; }
	const U& second() const { return m_second; }
	const V& third() const { return m_third; }

	void print() const;
};

template <typename T, typename U, typename V>
void Triaded<T, U, V>::print() const
{
	std::cout << '[' << m_first << ", " << m_second << ", " << m_third << ']';
}


class Random
{
private: // could be public if we want these to be accessible
	static std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with high-res clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	static inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

public:
	// Generate a random int between [min, max] (inclusive)
	static int get(int min, int max)
	{
		return std::uniform_int_distribution{ min, max }(mt);
	}
};



class Vector3d; // first, we need to tell the compiler that a class named Vector3d exists

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x, double y, double z)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{

	}

	void print() const
	{
		std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}

	void moveByVector(const Vector3d& v); // so we can use Vector3d here
	// note: we can't define this function here, because Vector3d hasn't been defined yet (just forward declared)
};

class Vector3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Vector3d(double x, double y, double z)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{

	}

	void print() const
	{
		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}

	friend void Point3d::moveByVector(const Vector3d& v); // Point3d::moveByVector() is now a friend of class Vector3d
};

// Now that Vector3d has been defined, we can define the function Point3d::moveByVector()
void Point3d::moveByVector(const Vector3d& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
}

template <typename T>
void printElement(const std::vector<T>& arr, int index)
{
	if (index >= static_cast<int>(arr.size()) || index < 0)
	{
		std::cout << "Error\n";
	}
	else
	{
		std::cout << arr[static_cast<std::size_t>(index)];
	}

	
}

template <typename T>
void printArray(const std::vector<T>& arr)
{
	for (std::size_t index{ 0 }; index < std::ssize(arr); ++index)
	{
		std::cout << arr[index] << ' ';
	}

	if (arr.size() > 0)
		std::cout << '\n';
}


namespace ExVec
{
	template <typename T>
	void printArray(const std::vector<T>& arr)
	{
		for (std::size_t index{ 0 }; index < arr.size(); ++index)
		{
			std::cout << arr[index] << ' ';
		}

		if (arr.size() > 0)
			std::cout << '\n';
	}

	template <typename T>
	int findIndex(const std::vector<T>& arr, T val)
	{
		for (std::size_t index{ 0 }; index < arr.size(); ++index)
		{
			if (arr[index] == val)
				return static_cast<int>(index);
		}

		return -1; // -1 is not a valid index, so we can use it as an error return value
	}

	// Passing in low and high allows the compiler to infer the type of the input we want
	template <typename T>
	T getValidNumber(std::string_view prompt, T low, T high)
	{
		// First, read in valid input from user
		T val{};
		do
		{
			std::cout << prompt;
			std::cin >> val;

			// if the user entered an invalid character
			if (!std::cin)
				std::cin.clear(); // reset any error flags

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any extra characters in the input buffer (regardless of whether we had an error or not)

		}
		while (val < low || val > high);

		return val;
	}

	template <typename T>
	T findMax(const std::vector<T>& arr)
	{
		if (std::ssize(arr) == 0)
		{
			return T{};
		}

		T highestNum{arr[0]};
		for (std::size_t index{1}; index < arr.size(); ++index)
		{
			if (arr[index] > highestNum)
			{
				highestNum = arr[index];
			}
		}
		return highestNum;
	}

	void fizzbuzz(int count)
	{
		// We'll make these static so we only have to do initialization once
		static const std::vector divisors{ 3, 5, 7, 11, 13, 17, 19 };
		static const std::vector<std::string_view> words{ "fizz", "buzz", "pop", "bang", "jazz", "pow", "boom" };
		assert(std::size(divisors) == std::size(words) && "fizzbuzz: array sizes don't match");

		// Loop through each number between 1 and count (inclusive)
		for (int i{ 1 }; i <= count; ++i)
		{
			bool printed{ false };

			// Check the current number against each possible divisor
			for (std::size_t j{ 0 }; j < divisors.size(); ++j)
			{
				if (i % divisors[j] == 0)
				{
					std::cout << words[j];
					printed = true;
				}
			}

			// If there were no divisors
			if (!printed)
				std::cout << i;

			std::cout << '\n';
		}
	}

	template <typename T>
	bool isValueInArray(const std::vector<T>& arr, const T& value)
	{
		for (const auto& a : arr)
		{
			if (a == value)
				return true;
		}

		return false;
	}

	void printStackValues(const std::vector<int>& v)
	{
		std::cout << "\t(Stack:";

		for (auto e : v)
			std::cout << ' ' << e;

		if (v.empty()) // if v.size == 0
			std::cout << " empty";

		std::cout << ")\n";
	}

	void pushAndPrint(std::vector<int>& v, int val)
	{
		v.push_back(val);
		std::cout << "Push " << val;
		printStackValues(v);
	}

	void popAndPrint(std::vector<int>& v)
	{
		v.pop_back();
		std::cout << "Pop ";
		printStackValues(v);
	}
}


namespace ExArr
{
	//Due to a language defect, the above functions will return a non - constexpr value when called on a std::array function parameter passed by(const) reference:
	void printLength(const std::array<int, 5>& arr)
	{
		//constexpr int length{ std::size(arr) }; // compile error!
		//std::cout << "length: " << length << '\n';
	}
	//This defect has been addressed in C++23 by P2280.At the time of writing, few compilers currently support this feature.
	//A workaround is to make printLength() a function template where the array length is a non - type template parameter.This non - type template parameter can then be used inside the function.
	template <auto Length>
	void printLength(const std::array<int, Length>& arr)
	{
		std::cout << "length: " << Length << '\n';
	}

	template <typename T, auto/*std::size_t*/ N> // note that this template parameter declaration matches the one for std::array
	void passByRef(const std::array<T, N>& arr)
	{
		static_assert(N != 0); // fail if this is a zero-length std::array

		std::cout << std::get<0>(arr) << '\n';
	}

	template <typename T, auto N>
	void printArray(const std::array<T, N>& arr)
	{
		static_assert(N != 0);

		std::cout << "The array (";
		for (int index{ 0 }; index <= std::ssize(arr) - 2; ++index)
		{
			std::cout << arr[index] << ", ";
		}

		std::cout << arr[std::ssize(arr) - 1] << ") has length " << std::ssize(arr) << '\n';
	}

	struct Item
	{
		std::string_view name{};
		int gold{};
	};

	template <auto N>
	void printStore(const std::array<Item, N>& arr)
	{
		for (const auto& item : arr)
		{
			std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
		}
	}


	namespace Color
	{
		enum Type
		{
			black,
			red,
			blue,
			max_colors
		};

		// use sv suffix so std::array will infer type as std::string_view
		using namespace std::string_view_literals; // for sv suffix
		constexpr std::array colorName{ "black"sv, "red"sv, "blue"sv };

		// Make sure we've defined strings for all our colors
		static_assert(std::size(colorName) == max_colors);
	};

	constexpr std::string_view getColorName(Color::Type color)
	{
		// We can index the array using the enumerator to get the name of the enumerator
		return Color::colorName[static_cast<std::size_t>(color)];
	}

	// Teach operator<< how to print a Color
	// std::ostream is the type of std::cout
	// The return type and parameter type are references (to prevent copies from being made)!
	std::ostream& operator<<(std::ostream& out, Color::Type color)
	{
		return out << getColorName(color);
	}

	// Teach operator>> how to input a Color by name
	// We pass color by non-const reference so we can have the function modify its value
	std::istream& operator>> (std::istream& in, Color::Type& color)
	{
		std::string input{};
		std::getline(in >> std::ws, input);

		// Iterate through the list of names to see if we can find a matching name
		for (std::size_t index = 0; index < Color::colorName.size(); ++index)
		{
			if (input == Color::colorName[index])
			{
				// If we found a matching name, we can get the enumerator value based on its index
				color = static_cast<Color::Type>(index);
				return in;
			}
		}

		// We didn't find a match, so input must have been invalid
		// so we will set input stream to fail state
		in.setstate(std::ios_base::failbit);

		// On an extraction failure, operator>> zero-initializes fundamental types
		// Uncomment the following line to make this operator do the same thing
		// color = {};
		return in;
	}


	namespace Animal
	{
		enum Type
		{
			chicken,
			dog,
			cat,
			elephant,
			duck,
			snake,
			max_animals
		};

		struct Data
		{
			std::string_view name{};
			int numLegs{};
			std::string_view sound{};
		};

		constexpr std::array types{ chicken, dog, cat, elephant, duck, snake };
		constexpr std::array data{ 
			Data{ "chicken",    2, "cluck" },
			Data{ "dog",        4, "woof" },
			Data{ "cat",        4, "meow" },
			Data{ "elephant",   4, "pawoo" },
			Data{ "duck",       2, "quack" },
			Data{ "snake",      0, "hissss" }, };

		static_assert(std::size(types) == max_animals);
		static_assert(std::size(data) == max_animals);
	}

	std::istream& operator>> (std::istream& in, Animal::Type& animal)
	{
		std::string input{};
		std::getline(in >> std::ws, input);

		for (int index{ 0 }; index < std::ssize(Animal::data); ++index)
		{
			if (input == Animal::data[index].name)
			{
				animal = static_cast<Animal::Type>(index);
				return in;
			}
		}

		in.setstate(std::ios_base::failbit);
		return in;
	}

	void printAnimalData(Animal::Type type)
	{
		const Animal::Data& animal{ Animal::data[type] };
		std::cout << "A " << animal.name << " has " << animal.numLegs << " legs and says " << animal.sound << ".\n";
	}

	void printCStyle(const char arr[])
	{
		while (*arr != '\0')
		{
			std::cout << *arr;

			++arr;
		}
	}

	void printCStyleReverse(const char str[])
	{
		const char* ptr{ str };

		while (*ptr != '\0')
		{
			++ptr;
		}

		while (ptr-- != str)
		{
			std::cout << *ptr;
		}
	}

	void exampleMultiCArray()
	{
		int arr[3][4]{
			   { 1, 2, 3, 4 },
			   { 5, 6, 7, 8 },
			   { 9, 10, 11, 12 } };

		// double for-loop with indices
		for (std::size_t row{ 0 }; row < std::size(arr); ++row) // std::size(arr) returns the number of rows
		{
			for (std::size_t col{ 0 }; col < std::size(arr[0]); ++col) // std::size(arr[0]) returns the number of columns
				std::cout << arr[row][col] << ' ';

			std::cout << '\n';
		}

		// double range-based for-loop
		for (const auto& arow : arr)   // get each array row
		{
			for (const auto& e : arow) // get each element of the row
				std::cout << e << ' ';

			std::cout << '\n';
		}
	}

	// An alias template for a two-dimensional std::array
	template <typename T, std::size_t Row, std::size_t Col>
	using Array2d = std::array<std::array<T, Col>, Row>;

	// When using Array2d as a function parameter, we need to respecify the template parameters
	template <typename T, std::size_t Row, std::size_t Col>
	void printArray(const Array2d<T, Row, Col>& arr)
	{
		for (const auto& arow : arr)   // get each array row
		{
			for (const auto& e : arow) // get each element of the row
				std::cout << e << ' ';

			std::cout << '\n';
		}
	}

	// Fetch the number of rows from the Row non-type template parameter
	template <typename T, std::size_t Row, std::size_t Col>
	constexpr int rowLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
	{
		return Row;
	}

	// Fetch the number of cols from the Col non-type template parameter
	template <typename T, std::size_t Row, std::size_t Col>
	constexpr int colLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
	{
		return Col;
	}

	// An alias template for a three-dimensional std::array
	template <typename T, std::size_t Row, std::size_t Col, std::size_t Depth>
	using Array3d = std::array<std::array<std::array<T, Depth>, Col>, Row>;

	//More on turning a Multidimensional Array into a one-dia array can be found here (https://www.learncpp.com/cpp-tutorial/multidimensional-stdarray/)
	
}


namespace DynamicAlloc
{
	std::size_t getNameCount()
	{
		std::cout << "How many names would you like to enter? ";
		std::size_t length{};
		std::cin >> length;

		return length;
	}

	// Asks user to enter all the names
	void getNames(std::string* names, std::size_t length)
	{
		for (std::size_t i{ 0 }; i < length; ++i)
		{
			std::cout << "Enter name #" << i + 1 << ": ";
			std::getline(std::cin >> std::ws, names[i]);
		}
	}

	// Prints the sorted names
	void printNames(std::string* names, std::size_t length)
	{
		std::cout << "\nHere is your sorted list:\n";

		for (std::size_t i{ 0 }; i < length; ++i)
			std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
	}

	//std::size_t length{ getNameCount() };
	//
	//// Allocate an array to hold the names
	//auto* names{ new std::string[length]{} };
	//
	//getNames(names, length);
	//
	//// Sort the array
	//std::sort(names, names + length);
	//
	//printNames(names, length);
	//
	//// don't forget to use array delete
	//delete[] names;
	//// we don't need to set names to nullptr/0 here because it's going to go out
	//// of scope immediately after this anyway.

}

namespace FunctionPointer
{
	// Note our user-defined comparison is the third parameter
	void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
	{
		if (!array || !comparisonFcn)
			return;

		// Step through each element of the array
		for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
		{
			// bestIndex is the index of the smallest/largest element we've encountered so far.
			int bestIndex{ startIndex };

			// Look for smallest/largest element remaining in the array (starting at startIndex+1)
			for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
			{
				// If the current element is smaller/larger than our previously found smallest
				if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
				{
					// This is the new smallest/largest number for this iteration
					bestIndex = currentIndex;
				}
			}

			// Swap our start element with our smallest/largest element
			std::swap(array[startIndex], array[bestIndex]);
		}
	}

	// Here is a comparison function that sorts in ascending order
	// (Note: it's exactly the same as the previous ascending() function)
	bool ascending(int x, int y)
	{
		return x > y; // swap if the first element is greater than the second
	}

	// Here is a comparison function that sorts in descending order
	bool descending(int x, int y)
	{
		return x < y; // swap if the second element is greater than the first
	}

	// This function prints out the values in the array
	void printArray(int* array, int size)
	{
		if (!array)
			return;

		for (int index{ 0 }; index < size; ++index)
		{
			std::cout << array[index] << ' ';
		}

		std::cout << '\n';
	}

	//int main()
	//{
	//	int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };

	//	// Sort the array in descending order using the descending() function
	//	selectionSort(array, 9, descending);
	//	printArray(array, 9);

	//	// Sort the array in ascending order using the ascending() function
	//	selectionSort(array, 9, ascending);
	//	printArray(array, 9);

	//	return 0;
	//}

	// Default the sort to ascending sort
//	void selectionSort_t(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);
//
//	using ValidateFunction = bool(*)(int, int);
//	bool validate(int x, int y, bool (*fcnPtr)(int, int)); // ugly
//	bool validate(int x, int y, ValidateFunction pfcn); // clean
//
//	//#include <functional>
//	bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and takes two int parameters
}

namespace Calculator
{
	using ArithmeticFunction = std::function<int(int, int)>;

	int getNumber()
	{
		static int count{ 1 };
		std::cout << "Number " << count << ": ";
		int num{};
		std::cin >> num;
		std::cout << '\n';
		return num;
	}

	char getOperator()
	{
		while (true)
		{
			std::cout << "Operator (+|-|/|*): ";
			char op{};
			std::cin >> op;
			std::cout << '\n';

			if (op == '+')
			{
				return op;
			}
			if (op == '-')
			{
				return op;
			}
			if (op == '*')
			{
				return op;
			}
			if (op == '/')
			{
				return op;
			}
			std::cout << "Wrong input, try again: ";

		}
	}

	int add(int num1, int num2)
	{
		return num1 + num2;
	}

	int subtract(int num1, int num2)
	{
		return num1 - num2;
	}

	int multiply(int num1, int num2)
	{
		return num1 * num2;
	}

	int divide(int num1, int num2)
	{
		return num1 / num2;
	}

	ArithmeticFunction getArithmeticFunction(char op)
	{
		switch (op)
		{
		case '+':
			return &add;
		case '-':
			return &subtract;
		case '*':
			return &multiply;
		case '/':
			return &divide;
		}

		return nullptr;
	}

	/*int num1{ Calculator::getNumber() };
	int num2{ Calculator::getNumber() };
	char op{ Calculator::getOperator() };

	Calculator::ArithmeticFunction fcn{ Calculator::getArithmeticFunction(op) };
	if (fcn)
	{
		std::cout << num1 << ' ' << op << ' ' << num2 << " = " << fcn(num1, num2) << '\n';
	}*/
}


namespace Lambda
{
	//Function literal or Lambda used in function call.
	/*
	constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  // Define the function right where we use it.
  auto found{ std::find_if(arr.begin(), arr.end(),
                           [](std::string_view str) // here's our lambda, no capture clause
                           {
                             return str.find("nut") != std::string_view::npos;
                           }) };

  if (found == arr.end())
  {
    std::cout << "No nuts\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }
	*/

	// Bad: We have to read the lambda to understand what's happening.
	/*return std::all_of(array.begin(), array.end(), [](int i) { return ((i % 2) == 0); });*/

	// Good: Instead, we can store the lambda in a named variable and pass it to the function.
	/*auto isEven{
	  [](int i)
	  {
		return (i % 2) == 0;
	  }
	};

	return std::all_of(array.begin(), array.end(), isEven);*/

	/*
	#include <functional>
#include <iostream>

// Case 1: use a `std::function` parameter
void repeat1(int repetitions, const std::function<void(int)>& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 2: use a function template with a type template parameter
template <typename T>
void repeat2(int repetitions, const T& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 3: use the abbreviated function template syntax (C++20)
void repeat3(int repetitions, const auto& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 4: use function pointer (only for lambda with no captures)
void repeat4(int repetitions, void (*fn)(int))
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

int main()
{
    auto lambda = [](int i)
    {
        std::cout << i << '\n';
    };

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    return 0;
}
	*/

	/*
	 int ammo{ 10 };

  auto shoot{
    [ammo]() mutable { // now mutable
      // We're allowed to modify ammo now
      --ammo;

      std::cout << "Pew! " << ammo << " shot(s) left.\n";
    }
  };

  shoot();
  shoot();

  std::cout << ammo << " shot(s) left\n";

  return 0;
	*/
	/*
	 int ammo{ 10 };

	  auto shoot{
		// We don't need mutable anymore
		[&ammo]() { // &ammo means ammo is captured by reference
		  // Changes to ammo will affect main's ammo
		  --ammo;

		  std::cout << "Pew! " << ammo << " shot(s) left.\n";
		}
	  };

	  shoot();

	  std::cout << ammo << " shot(s) left\n";
	  */

	/*
	int health{ 33 };
	int armor{ 100 };
	std::vector<CEnemy> enemies{};

	// Capture health and armor by value, and enemies by reference.
	[health, armor, &enemies](){};
	*/

/*
 std::array areas{ 100, 25, 121, 40, 56 };

  int width{};
  int height{};

  std::cout << "Enter width and height: ";
  std::cin >> width >> height;

  auto found{ std::find_if(areas.begin(), areas.end(),
						   [=](int knownArea) { // will default capture width and height by value
							 return width * height == knownArea; // because they're mentioned here
						   }) };

  if (found == areas.end())
  {
	std::cout << "I don't know this area :(\n";
  }
  else
  {
	std::cout << "Area found :)\n";
  }
*/

/*
int health{ 33 };
int armor{ 100 };
std::vector<CEnemy> enemies{};

// Capture health and armor by value, and enemies by reference.
[health, armor, &enemies](){};

// Capture enemies by reference and everything else by value.
[=, &enemies](){};

// Capture armor by value and everything else by reference.
[&, armor](){};

// Illegal, we already said we want to capture everything by reference.
[&, &armor](){};

// Illegal, we already said we want to capture everything by value.
[=, armor](){};

// Illegal, armor appears twice.
[armor, &health, &armor](){};

// Illegal, the default capture has to be the first element in the capture group.
[armor, &](){};
*/
}


namespace SmartPointers
{

	template <typename T>
	class Auto_ptr2
	{
		T* m_ptr{};
	public:
		Auto_ptr2(T* ptr = nullptr)
			:m_ptr(ptr)
		{
		}

		~Auto_ptr2()
		{
			delete m_ptr;
		}

		// A copy constructor that implements move semantics
		Auto_ptr2(Auto_ptr2& a) // note: not const
		{
			// We don't need to delete m_ptr here.  This constructor is only called when we're creating a new object, and m_ptr can't be set prior to this.
			m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
			a.m_ptr = nullptr; // make sure the source no longer owns the pointer
		}

		// An assignment operator that implements move semantics
		Auto_ptr2& operator=(Auto_ptr2& a) // note: not const
		{
			if (&a == this)
				return *this;

			delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
			m_ptr = a.m_ptr; // then transfer our dumb pointer from the source to the local object
			a.m_ptr = nullptr; // make sure the source no longer owns the pointer
			return *this;
		}

		T& operator*() const { return *m_ptr; }
		T* operator->() const { return m_ptr; }
		bool isNull() const { return m_ptr == nullptr; }
	};

	class Resource
	{
	public:
		Resource() { std::cout << "Resource acquired\n"; }
		~Resource() { std::cout << "Resource destroyed\n"; }
	};

	//int main()
	//{
	//	Auto_ptr2<Resource> res1(new Resource());
	//	Auto_ptr2<Resource> res2; // Start as nullptr

	//	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	//	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	//	res2 = res1; // res2 assumes ownership, res1 is set to null

	//	std::cout << "Ownership transferred\n";

	//	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	//	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	//	return 0;
	//}

	struct Student
	{
		std::string_view name{};
		int points{};
	};

//	int main()
//	{
//		constexpr std::array<Student, 8> arr{
//		  { { "Albert", 3 },
//			{ "Ben", 5 },
//			{ "Christine", 2 },
//			{ "Dan", 8 },
//			{ "Enchilada", 4 },
//			{ "Francis", 1 },
//			{ "Greg", 3 },
//			{ "Hagrid", 5 } }
//		};
//
//		const auto best{ // returns an iterator
//		  std::max_element(arr.begin(), arr.end(), [](const auto& a, const auto& b)
//	   {
//	return a.points < b.points;
//	})
//		};
//
//		std::cout << best->name << " is the best student\n"; // must dereference iterator to get element
//
//		return 0;
//	}

	struct Season
	{
		std::string_view name{};
		double averageTemperature{};
	};

	//int main()
	//{
	//	std::array<Season, 4> seasons{
	//	  { { "Spring", 285.0 },
	//		{ "Summer", 296.0 },
	//		{ "Fall", 288.0 },
	//		{ "Winter", 263.0 } }
	//	};

	//	// We can compare averageTemperature of the two arguments to
	//	// sort the array.
	//	std::sort(seasons.begin(), seasons.end(),
	//		[](const auto& a, const auto& b)
	//		{
	//			return a.averageTemperature < b.averageTemperature;
	//		});

	//	for (const auto& season : seasons)
	//	{
	//		std::cout << season.name << '\n';
	//	}

	//	return 0;
	//}
}

int factorial(int n)
{
	if (n <= 0)
		return 1;

	return factorial(n - 1) * n;
}

int sumDigits(int x)
{
	if (x < 10)
		return x;

	return sumDigits(x / 10) + x % 10;
}

void printBinary(unsigned int n)
{
	if (n > 1) // we only recurse if n > 1, so this is our termination case for n == 0
	{
		printBinary(n / 2);
	}

	std::cout << n % 2;
}

namespace RValueReference
{
	void fun(const int& lref) // l-value arguments will select this function
	{
		std::cout << "l-value reference to const: " << lref << '\n';
	}

	void fun(int&& rref) // r-value arguments will select this function
	{
		std::cout << "r-value reference: " << rref << '\n';
	}

	//int main()
	//{
	//	int x{ 5 };
	//	fun(x); // l-value argument calls l-value version of function
	//	fun(5); // r-value argument calls r-value version of function

	//	return 0;
	//}

	//__________________std::unique_ptr______________________________
	class Resource
	{
	public:
		Resource() { std::cout << "Resource acquired\n"; }
		~Resource() { std::cout << "Resource destroyed\n"; }
	};

	//int main()
	//{
	//	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
	//	std::unique_ptr<Resource> res2{}; // Start as nullptr

	//	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	//	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

	//	// res2 = res1; // Won't compile: copy assignment is disabled
	//	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

	//	std::cout << "Ownership transferred\n";

	//	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	//	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

	//	return 0;
	//} // Resource destroyed here when res2 goes out of scope

	class Fraction
	{
	private:
		int m_numerator{ 0 };
		int m_denominator{ 1 };

	public:
		Fraction(int numerator = 0, int denominator = 1) :
			m_numerator{ numerator }, m_denominator{ denominator }
		{
		}

		friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
		{
			out << f1.m_numerator << '/' << f1.m_denominator;
			return out;
		}
	};


	//int main()
	//{
	//	// Create a single dynamically allocated Fraction with numerator 3 and denominator 5
	//	// We can also use automatic type deduction to good effect here
	//	auto f1{ std::make_unique<Fraction>(3, 5) };
	//	std::cout << *f1 << '\n';

	//	// Create a dynamically allocated array of Fractions of length 4
	//	auto f2{ std::make_unique<Fraction[]>(4) };
	//	std::cout << f2[0] << '\n';

	//	return 0;
	//}
	//Use std::make_unique() instead of creating std::unique_ptr and using new yourself. --> exception safe issue fixed in c++17

	//class Resource
	//{
	//public:
	//	Resource() { std::cout << "Resource acquired\n"; }
	//	~Resource() { std::cout << "Resource destroyed\n"; }
	//};

	//std::ostream& operator<<(std::ostream& out, const Resource&)
	//{
	//	out << "I am a resource";
	//	return out;
	//}

	//// This function takes ownership of the Resource, which isn't what we want
	//void takeOwnership(std::unique_ptr<Resource> res)
	//{
	//	if (res)
	//		std::cout << *res << '\n';
	//} // the Resource is destroyed here

	//int main()
	//{
	//	auto ptr{ std::make_unique<Resource>() };

	//	//    takeOwnership(ptr); // This doesn't work, need to use move semantics
	//	takeOwnership(std::move(ptr)); // ok: use move semantics

	//	std::cout << "Ending program\n";

	//	return 0;
	//}

	//class Resource
	//{
	//public:
	//	Resource() { std::cout << "Resource acquired\n"; }
	//	~Resource() { std::cout << "Resource destroyed\n"; }
	//};

	//std::ostream& operator<<(std::ostream& out, const Resource&)
	//{
	//	out << "I am a resource";
	//	return out;
	//}

	//// The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
	//void useResource(const Resource* res)
	//{
	//	if (res)
	//		std::cout << *res << '\n';
	//	else
	//		std::cout << "No resource\n";
	//}

	//int main()
	//{
	//	auto ptr{ std::make_unique<Resource>() };

	//	useResource(ptr.get()); // note: get() used here to get a pointer to the Resource

	//	std::cout << "Ending program\n";

	//	return 0;
	//} // The Resource is destroyed here

	//_________________________std::shared_ptr_____________________________________________________________
	/*class Resource
	{
	public:
		Resource() { std::cout << "Resource acquired\n"; }
		~Resource() { std::cout << "Resource destroyed\n"; }
	};*/

	//int main()
	//{
	//	// allocate a Resource object and have it owned by std::shared_ptr
	//	Resource* res{ new Resource };
	//	std::shared_ptr<Resource> ptr1{ res };
	//	{
	//		std::shared_ptr<Resource> ptr2{ ptr1 }; // make another std::shared_ptr pointing to the same thing

	//		std::cout << "Killing one shared pointer\n";
	//	} // ptr2 goes out of scope here, but nothing happens

	//	std::cout << "Killing another shared pointer\n";

	//	return 0;
	//} // ptr1 goes out of scope here, and the allocated Resource is destroyed

	/*class Resource
	{
	public:
		Resource() { std::cout << "Resource acquired\n"; }
		~Resource() { std::cout << "Resource destroyed\n"; }
	};*/

	//int main()
	//{
	//	// allocate a Resource object and have it owned by std::shared_ptr
	//	auto ptr1{ std::make_shared<Resource>() };
	//	{
	//		auto ptr2{ ptr1 }; // create ptr2 using copy of ptr1

	//		std::cout << "Killing one shared pointer\n";
	//	} // ptr2 goes out of scope here, but nothing happens

	//	std::cout << "Killing another shared pointer\n";

	//	return 0;
	//} // ptr1 goes out of scope here, and the allocated Resource is destroyed
	//Use std::make_shared() over std::shared_ptr_______________________________________

	//_________________________std::weak_ptr_________________________________________________
	class Person
	{
		std::string m_name;
		std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

	public:

		Person(const std::string& name) : m_name(name)
		{
			std::cout << m_name << " created\n";
		}
		~Person()
		{
			std::cout << m_name << " destroyed\n";
		}

		friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
		{
			if (!p1 || !p2)
				return false;

			p1->m_partner = p2;
			p2->m_partner = p1;

			std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

			return true;
		}
	};

	/*int main()
	{
		auto lucy{ std::make_shared<Person>("Lucy") };
		auto ricky{ std::make_shared<Person>("Ricky") };

		partnerUp(lucy, ricky);

		return 0;
	}*/
	// has no -> operator, need to be converted to std::unique_ptr
	//class Person
	//{
	//	std::string m_name;
	//	std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr

	//public:

	//	Person(const std::string& name) : m_name(name)
	//	{
	//		std::cout << m_name << " created\n";
	//	}
	//	~Person()
	//	{
	//		std::cout << m_name << " destroyed\n";
	//	}

	//	friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
	//	{
	//		if (!p1 || !p2)
	//			return false;

	//		p1->m_partner = p2;
	//		p2->m_partner = p1;

	//		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

	//		return true;
	//	}

	//	std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // use lock() to convert weak_ptr to shared_ptr
	//	const std::string& getName() const { return m_name; }
	//};

	//int main()
	//{
	//	auto lucy{ std::make_shared<Person>("Lucy") };
	//	auto ricky{ std::make_shared<Person>("Ricky") };

	//	partnerUp(lucy, ricky);

	//	auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
	//	std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';

	//	return 0;
	//}

	//class Resource
	//{
	//public:
	//	Resource() { std::cerr << "Resource acquired\n"; }
	//	~Resource() { std::cerr << "Resource destroyed\n"; }
	//};

	//// Returns a std::weak_ptr to an invalid object
	//std::weak_ptr<Resource> getWeakPtr()
	//{
	//	auto ptr{ std::make_shared<Resource>() };
	//	return std::weak_ptr<Resource>{ ptr };
	//} // ptr goes out of scope, Resource destroyed

	//// Returns a dumb pointer to an invalid object
	//Resource* getDumbPtr()
	//{
	//	auto ptr{ std::make_unique<Resource>() };
	//	return ptr.get();
	//} // ptr goes out of scope, Resource destroyed

	/*int main()
	{
		auto dumb{ getDumbPtr() };
		std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

		auto weak{ getWeakPtr() };
		std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

		return 0;
	}*/
}

namespace MoveConstructor
{

	template<typename T>
	class Auto_ptr4
	{
		T* m_ptr{};
	public:
		Auto_ptr4(T* ptr = nullptr)
			: m_ptr{ ptr }
		{
		}

		~Auto_ptr4()
		{
			delete m_ptr;
		}

		// Copy constructor
		// Do deep copy of a.m_ptr to m_ptr
		Auto_ptr4(const Auto_ptr4& a)
		{
			m_ptr = new T;
			*m_ptr = *a.m_ptr;
		}

		// Move constructor
		// Transfer ownership of a.m_ptr to m_ptr
		Auto_ptr4(Auto_ptr4&& a) noexcept
			: m_ptr{ a.m_ptr }
		{
			a.m_ptr = nullptr; // we'll talk more about this line below
		}

		// Copy assignment
		// Do deep copy of a.m_ptr to m_ptr
		Auto_ptr4& operator=(const Auto_ptr4& a)
		{
			// Self-assignment detection
			if (&a == this)
				return *this;

			// Release any resource we're holding
			delete m_ptr;

			// Copy the resource
			m_ptr = new T;
			*m_ptr = *a.m_ptr;

			return *this;
		}

		// Move assignment
		// Transfer ownership of a.m_ptr to m_ptr
		Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
		{
			// Self-assignment detection
			if (&a == this)
				return *this;

			// Release any resource we're holding
			delete m_ptr;

			// Transfer ownership of a.m_ptr to m_ptr
			m_ptr = a.m_ptr;
			a.m_ptr = nullptr; // we'll talk more about this line below

			return *this;
		}

		T& operator*() const { return *m_ptr; }
		T* operator->() const { return m_ptr; }
		bool isNull() const { return m_ptr == nullptr; }
	};

	class Resource
	{
	public:
		Resource() { std::cout << "Resource acquired\n"; }
		~Resource() { std::cout << "Resource destroyed\n"; }
	};

	Auto_ptr4<Resource> generateResource()
	{
		Auto_ptr4<Resource> res{ new Resource };
		return res; // this return value will invoke the move constructor
	}

	//int main()
	//{
	//	Auto_ptr4<Resource> mainres;
	//	mainres = generateResource(); // this assignment will invoke the move assignment

	//	return 0;
	//}

	//____________________________________ No copy semantics support_________________________________
	template<typename T>
	class Auto_ptr5
	{
		T* m_ptr{};
	public:
		Auto_ptr5(T* ptr = nullptr)
			: m_ptr{ ptr }
		{
		}

		~Auto_ptr5()
		{
			delete m_ptr;
		}

		// Copy constructor -- no copying allowed!
		Auto_ptr5(const Auto_ptr5& a) = delete;

		// Move constructor
		// Transfer ownership of a.m_ptr to m_ptr
		Auto_ptr5(Auto_ptr5&& a) noexcept
			: m_ptr{ a.m_ptr }
		{
			a.m_ptr = nullptr;
		}

		// Copy assignment -- no copying allowed!
		Auto_ptr5& operator=(const Auto_ptr5& a) = delete;

		// Move assignment
		// Transfer ownership of a.m_ptr to m_ptr
		Auto_ptr5& operator=(Auto_ptr5&& a) noexcept
		{
			// Self-assignment detection
			if (&a == this)
				return *this;

			// Release any resource we're holding
			delete m_ptr;

			// Transfer ownership of a.m_ptr to m_ptr
			m_ptr = a.m_ptr;
			a.m_ptr = nullptr;

			return *this;
		}

		T& operator*() const { return *m_ptr; }
		T* operator->() const { return m_ptr; }
		bool isNull() const { return m_ptr == nullptr; }
	};
	//Use std::unique_ptr instead of example above(only dealt as example)

	//______std::swap_____________________
	template <typename T>
	void mySwapCopy(T& a, T& b)
	{
		T tmp{ a }; // invokes copy constructor
		a = b; // invokes copy assignment
		b = tmp; // invokes copy assignment
	}

	/*int main()
	{
		std::string x{ "abc" };
		std::string y{ "de" };

		std::cout << "x: " << x << '\n';
		std::cout << "y: " << y << '\n';

		mySwapCopy(x, y);

		std::cout << "x: " << x << '\n';
		std::cout << "y: " << y << '\n';

		return 0;
	}*/

	//!!!The implicit move constructor and move assignment will copy pointers, not move them. If you want to move a pointer member, you will need to define the move constructor and move assignment yourself.!!
}

namespace ObjectCompositions
{
	//_________________Aggregation_______________________________________
	class Teacher
	{
	private:
		std::string m_name{};

	public:
		Teacher(std::string_view name)
			: m_name{ name }
		{
		}

		const std::string& getName() const { return m_name; }
	};

	class Department
	{
	private:
		const Teacher& m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers

	public:
		Department(const Teacher& teacher)
			: m_teacher{ teacher }
		{
		}
	};

	//int main()
	//{
	//	// Create a teacher outside the scope of the Department
	//	Teacher bob{ "Bob" }; // create a teacher

	//	{
	//		// Create a department and use the constructor parameter to pass
	//		// the teacher to it.
	//		Department department{ bob };

	//	} // department goes out of scope here and is destroyed

	//	// bob still exists here, but the department doesn't

	//	std::cout << bob.getName() << " still exists!\n";

	//	return 0;
	//}

	//___________________________________Association_____________________________________________
	// Since Doctor and Patient have a circular dependency, we're going to forward declare Patient
	class Patient;

	class Doctor
	{
	private:
		std::string m_name{};
		std::vector<std::reference_wrapper<const Patient>> m_patient{};

	public:
		Doctor(std::string_view name) :
			m_name{ name }
		{
		}

		void addPatient(Patient& patient);

		// We'll implement this function below Patient since we need Patient to be defined at that point
		friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);

		const std::string& getName() const { return m_name; }
	};

	class Patient
	{
	private:
		std::string m_name{};
		std::vector<std::reference_wrapper<const Doctor>> m_doctor{}; // so that we can use it here

		// We're going to make addDoctor private because we don't want the public to use it.
		// They should use Doctor::addPatient() instead, which is publicly exposed
		void addDoctor(const Doctor& doctor)
		{
			m_doctor.push_back(doctor);
		}

	public:
		Patient(std::string_view name)
			: m_name{ name }
		{
		}

		// We'll implement this function below to parallel operator<<(std::ostream&, const Doctor&)
		friend std::ostream& operator<<(std::ostream& out, const Patient& patient);

		const std::string& getName() const { return m_name; }

		// We'll friend Doctor::addPatient() so it can access the private function Patient::addDoctor()
		friend void Doctor::addPatient(Patient& patient);
	};

	void Doctor::addPatient(Patient& patient)
	{
		// Our doctor will add this patient
		m_patient.push_back(patient);

		// and the patient will also add this doctor
		patient.addDoctor(*this);
	}

	std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
	{
		if (doctor.m_patient.empty())
		{
			out << doctor.m_name << " has no patients right now";
			return out;
		}

		out << doctor.m_name << " is seeing patients: ";
		for (const auto& patient : doctor.m_patient)
			out << patient.get().getName() << ' ';

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Patient& patient)
	{
		if (patient.m_doctor.empty())
		{
			out << patient.getName() << " has no doctors right now";
			return out;
		}

		out << patient.m_name << " is seeing doctors: ";
		for (const auto& doctor : patient.m_doctor)
			out << doctor.get().getName() << ' ';

		return out;
	}

	//int main()
	//{
	//	// Create a Patient outside the scope of the Doctor
	//	Patient dave{ "Dave" };
	//	Patient frank{ "Frank" };
	//	Patient betsy{ "Betsy" };

	//	Doctor james{ "James" };
	//	Doctor scott{ "Scott" };

	//	james.addPatient(dave);

	//	scott.addPatient(dave);
	//	scott.addPatient(betsy);

	//	std::cout << james << '\n';
	//	std::cout << scott << '\n';
	//	std::cout << dave << '\n';
	//	std::cout << frank << '\n';
	//	std::cout << betsy << '\n';

	//	return 0;
	//}

	//Use only if needed (space or speed)
	class Car
	{
	private:
		std::string m_name{};
		int m_id{};

	public:
		Car(std::string_view name, int id)
			: m_name{ name }, m_id{ id }
		{
		}

		const std::string& getName() const { return m_name; }
		int getId() const { return m_id; }
	};

	// Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
	// Because it's static, we don't need to allocate an object of type CarLot to use it
	namespace CarLot
	{
		Car carLot[4]{ { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 } };

		Car* getCar(int id)
		{
			for (auto& car : carLot)
			{
				if (car.getId() == id)
				{
					return &car;
				}
			}

			return nullptr;
		}
	};

	class Driver
	{
	private:
		std::string m_name{};
		int m_carId{}; // we're associated with the Car by ID rather than pointer

	public:
		Driver(std::string_view name, int carId)
			: m_name{ name }, m_carId{ carId }
		{
		}

		const std::string& getName() const { return m_name; }
		int getCarId() const { return m_carId; }
	};

	//int main()
	//{
	//	Driver d{ "Franz", 17 }; // Franz is driving the car with ID 17

	//	Car* car{ CarLot::getCar(d.getCarId()) }; // Get that car from the car lot

	//	if (car)
	//		std::cout << d.getName() << " is driving a " << car->getName() << '\n';
	//	else
	//		std::cout << d.getName() << " couldn't find his car\n";

	//	return 0;
	//}
}

namespace ContainerClass
{
//#include "IntArray.h"

	//int main()
	//{
	//	// Declare an array with 10 elements
	//	IntArray array(10);

	//	// Fill the array with numbers 1 through 10
	//	for (int i{ 0 }; i < 10; ++i)
	//		array[i] = i + 1;

	//	// Resize the array to 8 elements
	//	array.resize(8);

	//	// Insert the number 20 before element with index 5
	//	array.insertBefore(20, 5);

	//	// Remove the element with index 3
	//	array.remove(3);

	//	// Add 30 and 40 to the end and beginning
	//	array.insertAtEnd(30);
	//	array.insertAtBeginning(40);

	//	// A few more tests to ensure copy constructing / assigning arrays
	//	// doesn't break things
	//	{
	//		IntArray b{ array };
	//		b = array;
	//		b = b;
	//		array = array;
	//	}

	//	// Print out all the numbers
	//	for (int i{ 0 }; i < array.getLength(); ++i)
	//		std::cout << array[i] << ' ';

	//	std::cout << '\n';

	//	return 0;
	//}
}


namespace Inheritance
{
	class Person
	{
	private:
		std::string m_name;
		int m_age{};

	public:
		Person(std::string_view name = "", int age = 0)
			: m_name{ name }, m_age{ age }
		{
		}

		const std::string& getName() const { return m_name; }
		int getAge() const { return m_age; }

	};
	// BaseballPlayer publicly inheriting Person
	class BaseballPlayer : public Person
	{
	private:
		double m_battingAverage{};
		int m_homeRuns{};

	public:
		BaseballPlayer(std::string_view name = "", int age = 0,
			double battingAverage = 0.0, int homeRuns = 0)
			: Person{ name, age } // call Person(std::string_view, int) to initialize these fields
			, m_battingAverage{ battingAverage }, m_homeRuns{ homeRuns }
		{
		}

		double getBattingAverage() const { return m_battingAverage; }
		int getHomeRuns() const { return m_homeRuns; }
	};

	//// Employee publicly inherits from Person
	//class Employee : public Person
	//{
	//public:
	//	double m_hourlySalary{};
	//	long m_employeeID{};

	//	Employee(double hourlySalary = 0.0, long employeeID = 0)
	//		: m_hourlySalary{ hourlySalary }, m_employeeID{ employeeID }
	//	{
	//	}

	//	void printNameAndSalary() const
	//	{
	//		std::cout << m_name << ": " << m_hourlySalary << '\n';
	//	}
	//};

	//class Supervisor : public Employee
	//{
	//public:
	//	// This Supervisor can oversee a max of 5 employees
	//	long m_overseesIDs[5]{};
	//};


	class Base
	{
	private: // our member is now private
		int m_id{};

	public:
		Base(int id = 0)
			: m_id{ id }
		{
		}

		int getId() const { return m_id; }
	};

	class Derived : public Base
	{
	private: // our member is now private
		double m_cost;

	public:
		Derived(double cost = 0.0, int id = 0)
			: Base{ id } // Call Base(int) constructor with value id!
			, m_cost{ cost }
		{
		}

		double getCost() const { return m_cost; }
	};

	//int main()
	//{
	//	Derived derived{ 1.3, 5 }; // use Derived(double, int) constructor
	//	std::cout << "Id: " << derived.getId() << '\n';
	//	std::cout << "Cost: " << derived.getCost() << '\n';

	//	return 0;
	//}

	class A
	{
	public:
		A(int a)
		{
			std::cout << "A: " << a << '\n';
		}
	};

	class B : public A
	{
	public:
		B(int a, double b)
			: A{ a }
		{
			std::cout << "B: " << b << '\n';
		}
	};

	class C : public B
	{
	public:
		C(int a, double b, char c)
			: B{ a, b }
		{
			std::cout << "C: " << c << '\n';
		}
	};

	/*int main()
	{
		C c{ 5, 4.3, 'R' };

		return 0;
	}*/

	class Base1
	{
	public:
		Base1() {}

		void identify() const { std::cout << "Base::identify()\n"; }
	};

	class Derived1 : public Base1
	{
	public:
		Derived1() {}

		void identify() const { std::cout << "Derived::identify()\n"; }
	};

	/*int main()
	{
		Base1 base{};
		base.identify();

		Derived1 derived{};
		derived.identify();

		return 0;
	}*/

	class Base2
	{
	public:
		Base2() {}

		void identify() const { std::cout << "Base::identify()\n"; }
	};

	class Derived2 : public Base2
	{
	public:
		Derived2() {}

		void identify() const
		{
			std::cout << "Derived::identify()\n";
			Base2::identify(); // note call to Base::identify() here
		}
	};

	/*int main()
	{
		Base2 base{};
		base.identify();

		Derived2 derived{};
		derived.identify();

		return 0;
	}*/

	class Base3
	{
	public:
		Base3() {}

		friend std::ostream& operator<< (std::ostream& out, const Base3&)
		{
			out << "In Base\n";
			return out;
		}
	};

	class Derived3 : public Base3
	{
	public:
		Derived3() {}

		friend std::ostream& operator<< (std::ostream& out, const Derived3& d)
		{
			out << "In Derived\n";
			// static_cast Derived to a Base object, so we call the right version of operator<<
			out << static_cast<const Base3&>(d);
			return out;
		}
	};

	/*int main()
	{
		Derived3 derived{};

		std::cout << derived << '\n';

		return 0;
	}*/

	//class Base
	//{
	//public:
	//	void print(int) { std::cout << "Base::print(int)\n"; }
	//	void print(double) { std::cout << "Base::print(double)\n"; }
	//};

	//class Derived : public Base
	//{
	//public:
	//	using Base::print; // make all Base::print() functions eligible for overload resolution
	//	void print(double) { std::cout << "Derived::print(double)"; }
	//};


	//int main()
	//{
	//	Derived d{};
	//	d.print(5); // calls Base::print(int), which is the best matching function visible in Derived

	//	return 0;
	//}


	//class Person
	//{
	//private:
	//	std::string m_name{};
	//	int m_age{};

	//public:
	//	Person(std::string_view name, int age)
	//		: m_name{ name }, m_age{ age }
	//	{
	//	}

	//	const std::string& getName() const { return m_name; }
	//	int getAge() const { return m_age; }
	//};

	//class Employee
	//{
	//private:
	//	std::string m_employer{};
	//	double m_wage{};

	//public:
	//	Employee(std::string_view employer, double wage)
	//		: m_employer{ employer }, m_wage{ wage }
	//	{
	//	}

	//	const std::string& getEmployer() const { return m_employer; }
	//	double getWage() const { return m_wage; }
	//};

	//// Teacher publicly inherits Person and Employee
	//class Teacher : public Person, public Employee
	//{
	//private:
	//	int m_teachesGrade{};

	//public:
	//	Teacher(std::string_view name, int age, std::string_view employer, double wage, int teachesGrade)
	//		: Person{ name, age }, Employee{ employer, wage }, m_teachesGrade{ teachesGrade }
	//	{
	//	}
	//};

	//int main()
	//{
	//	Teacher t{ "Mary", 45, "Boo", 14.3, 8 };

	//	return 0;
	//}

	//struct Point2D
	//{
	//	int x{};
	//	int y{};
	//};

	//class Box // mixin Box class
	//{
	//public:
	//	void setTopLeft(Point2D point) { m_topLeft = point; }
	//	void setBottomRight(Point2D point) { m_bottomRight = point; }
	//private:
	//	Point2D m_topLeft{};
	//	Point2D m_bottomRight{};
	//};

	//class Label // mixin Label class
	//{
	//public:
	//	void setText(const std::string_view str) { m_text = str; }
	//	void setFontSize(int fontSize) { m_fontSize = fontSize; }
	//private:
	//	std::string m_text{};
	//	int m_fontSize{};
	//};

	//class Tooltip // mixin Tooltip class
	//{
	//public:
	//	void setText(const std::string_view str) { m_text = str; }
	//private:
	//	std::string m_text{};
	//};

	//class Button : public Box, public Label, public Tooltip {}; // Button using three mixins

	//int main()
	//{
	//	Button button{};
	//	button.Box::setTopLeft({ 1, 1 });
	//	button.Box::setBottomRight({ 10, 10 });
	//	button.Label::setText("Submit");
	//	button.Label::setFontSize(6);
	//	button.Tooltip::setText("Submit the form to the server");
	//}

	//_____________________________________________________
	// The Curiously Recurring Template Pattern (CRTP)

	//template <class T>
	//class Mixin
	//{
	//	// Mixin<T> can use template type parameter T to access members of Derived
	//	// via (static_cast<T*>(this))
	//};

	//class Derived : public Mixin<Derived>
	//{
	//};
	//_________________________________________________________

	
}

namespace VirtualFunctions
{
	class Base
	{
	public:
		virtual std::string_view getName() const { return "Base"; } // note addition of virtual keyword
	};

	class Derived : public Base
	{
	public:
		virtual std::string_view getName() const { return "Derived"; }
	};

	/*int main()
	{
		Derived derived{};
		Base& rBase{ derived };
		std::cout << "rBase is a " << rBase.getName() << '\n';

		return 0;
	}*/

	class A
	{
	public:
		virtual std::string_view getName() const { return "A"; }
	};

	class B : public A
	{
	public:
		virtual std::string_view getName() const { return "B"; }
	};

	class C : public B
	{
	public:
		virtual std::string_view getName() const { return "C"; }
	};

	class D : public C
	{
	public:
		virtual std::string_view getName() const { return "D"; }
	};

	/*int main()
	{
		C c{};
		A& rBase{ c };
		std::cout << "rBase is a " << rBase.getName() << '\n';

		return 0;
	}*/

	class Animal
	{
	protected:
		std::string m_name{};

		// We're making this constructor protected because
		// we don't want people creating Animal objects directly,
		// but we still want derived classes to be able to use it.
		Animal(std::string_view name)
			: m_name{ name }
		{
		}

	public:
		const std::string& getName() const { return m_name; }
		virtual std::string_view speak() const { return "???"; }
	};

	class Cat : public Animal
	{
	public:
		Cat(std::string_view name)
			: Animal{ name }
		{
		}

		virtual std::string_view speak() const { return "Meow"; }
	};

	class Dog : public Animal
	{
	public:
		Dog(std::string_view name)
			: Animal{ name }
		{
		}

		virtual std::string_view speak() const { return "Woof"; }
	};

	void report(const Animal& animal)
	{
		std::cout << animal.getName() << " says " << animal.speak() << '\n';
	}

	/*int main()
	{
		Cat cat{ "Fred" };
		Dog dog{ "Garbo" };

		report(cat);
		report(dog);

		return 0;
	}*/

	//class A
	//{
	//public:
	//	virtual std::string_view getName1(int x) { return "A"; }
	//	virtual std::string_view getName2(int x) { return "A"; }
	//	virtual std::string_view getName3(int x) { return "A"; }
	//};

	//class B : public A
	//{
	//public:
	//	std::string_view getName1(short int x) override { return "B"; } // compile error, function is not an override
	//	std::string_view getName2(int x) const override { return "B"; } // compile error, function is not an override
	//	std::string_view getName3(int x) override { return "B"; } // okay, function is an override of A::getName3(int)

	//};

	/*int main()
	{
		return 0;
	}*/

	//Use the virtual keyword on virtual functions in a base class.
	//Use the override specifier (but not the virtual keyword) on override functions in derived classes. This includes virtual destructors.______________________

	//class A
	//{
	//public:
	//	virtual std::string_view getName() const { return "A"; }
	//};

	//class B : public A
	//{
	//public:
	//	// note use of final specifier on following line -- that makes this function not able to be overridden in derived classes
	//	std::string_view getName() const override final { return "B"; } // okay, overrides A::getName()
	//};

	//class C : public B
	//{
	//public:
	//	std::string_view getName() const override { return "C"; } // compile error: overrides B::getName(), which is final
	//};

	//class A
	//{
	//public:
	//	virtual std::string_view getName() const { return "A"; }
	//};

	//class B final : public A // note use of final specifier here
	//{
	//public:
	//	std::string_view getName() const override { return "B"; }
	//};

	//class C : public B // compile error: cannot inherit from final class
	//{
	//public:
	//	std::string_view getName() const override { return "C"; }
	//};

	//If you intend your class to be inherited from, make sure your destructor is virtual and public.
	//If you do not intend your class to be inherited from, mark your class as final.
	// This will prevent other classes from inheriting from it in the first place, without imposing any other use restrictions on the class itself.

	//class Base
	//{
	//public:
	//	std::string_view sayHi() const { return "Hi"; } // a normal non-virtual function

	//	virtual std::string_view getName() const { return "Base"; } // a normal virtual function

	//	virtual int getValue() const = 0; // a pure virtual function

	//	int doSomething() = 0; // Compile error: can not set non-virtual functions to 0
	//};

	class Animal // This Animal is an abstract base class
	{
	protected:
		std::string m_name{};

	public:
		Animal(std::string_view name)
			: m_name{ name }
		{
		}

		const std::string& getName() const { return m_name; }
		virtual std::string_view speak() const = 0; // note that speak is now a pure virtual function

		virtual ~Animal() = default;
	};

	std::string_view Animal::speak() const
	{
		return "buzz"; // some default implementation
	}

	class Cow : public Animal
	{
	public:
		Cow(std::string_view name)
			: Animal(name)
		{
		}

		std::string_view speak() const override { return "Moo"; }
	};

	class Dragonfly : public Animal
	{

	public:
		Dragonfly(std::string_view name)
			: Animal{ name }
		{
		}

		std::string_view speak() const override// this class is no longer abstract because we defined this function
		{
			return Animal::speak(); // use Animal's default implementation
		}
	};

	/*int main()
	{
		Cow cow{ "Betsy" };
		std::cout << cow.getName() << " says " << cow.speak() << '\n';

		Dragonfly dfly{ "Sally" };
		std::cout << dfly.getName() << " says " << dfly.speak() << '\n';

		return 0;
	}*/

	//Interface Class________________
	class IErrorLog
	{
	public:
		virtual bool openLog(std::string_view filename) = 0;
		virtual bool closeLog() = 0;

		virtual bool writeError(std::string_view errorMessage) = 0;

		virtual ~IErrorLog() {} // make a virtual destructor in case we delete an IErrorLog pointer, so the proper derived destructor is called
	};

	//Diamond Problem____________________
	/*class PoweredDevice
	{
	};

	class Scanner : virtual public PoweredDevice
	{
	};

	class Printer : virtual public PoweredDevice
	{
	};

	class Copier : public Scanner, public Printer
	{
	};*/

	class PoweredDevice
	{
	public:
		PoweredDevice(int power)
		{
			std::cout << "PoweredDevice: " << power << '\n';
		}
	};

	class Scanner : virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
	{
	public:
		Scanner(int scanner, int power)
			: PoweredDevice{ power } // this line is required to create Scanner objects, but ignored in this case
		{
			std::cout << "Scanner: " << scanner << '\n';
		}
	};

	class Printer : virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
	{
	public:
		Printer(int printer, int power)
			: PoweredDevice{ power } // this line is required to create Printer objects, but ignored in this case
		{
			std::cout << "Printer: " << printer << '\n';
		}
	};

	class Copier : public Scanner, public Printer
	{
	public:
		Copier(int scanner, int printer, int power)
			: PoweredDevice{ power }, // PoweredDevice is constructed here
			Scanner{ scanner, power }, Printer{ printer, power }
		{
		}
	};

	//Dynamic Casting_________________
	 
	// class Base
	//{
	//protected:
	//	int m_value{};

	//public:
	//	Base(int value)
	//		: m_value{ value }
	//	{
	//	}

	//	virtual ~Base() = default;
	//};

	//class Derived : public Base
	//{
	//protected:
	//	std::string m_name{};

	//public:
	//	Derived(int value, std::string_view name)
	//		: Base{ value }, m_name{ name }
	//	{
	//	}

	//	const std::string& getName() const { return m_name; }
	//};

	//Base* getObject(bool returnDerived)
	//{
	//	if (returnDerived)
	//		return new Derived{ 1, "Apple" };
	//	else
	//		return new Base{ 2 };
	//}
	
	//int main()
	//{
	//	Base* b{ getObject(true) };

	//	Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer

	//	if (d) // make sure d is non-null
	//		std::cout << "The name of the Derived is: " << d->getName() << '\n';

	//	delete b;

	//	return 0;
	//}

	//class Base
	//{
	//protected:
	//	int m_value;

	//public:
	//	Base(int value)
	//		: m_value{ value }
	//	{
	//	}

	//	virtual ~Base() = default;
	//};

	//class Derived : public Base
	//{
	//protected:
	//	std::string m_name;

	//public:
	//	Derived(int value, std::string_view name)
	//		: Base{ value }, m_name{ name }
	//	{
	//	}

	//	const std::string& getName() const { return m_name; }
	//};

	//int main()
	//{
	//	Derived apple{ 1, "Apple" }; // create an apple
	//	Base& b{ apple }; // set base reference to object
	//	Derived& d{ dynamic_cast<Derived&>(b) }; // dynamic cast using a reference instead of a pointer

	//	std::cout << "The name of the Derived is: " << d.getName() << '\n'; // we can access Derived::getName through d

	//	return 0;
	//}

	//Operator<<´_________________
	//class Base
	//{
	//public:
	//	// Here's our overloaded operator<<
	//	friend std::ostream& operator<<(std::ostream& out, const Base& b)
	//	{
	//		// Call virtual function identify() to get the string to be printed
	//		out << b.identify();
	//		return out;
	//	}

	//	// We'll rely on member function identify() to return the string to be printed
	//	// Because identify() is a normal member function, it can be virtualized
	//	virtual std::string identify() const
	//	{
	//		return "Base";
	//	}
	//};

	//class Derived : public Base
	//{
	//public:
	//	// Here's our override identify() function to handle the Derived case
	//	std::string identify() const override
	//	{
	//		return "Derived";
	//	}
	//};

	//int main()
	//{
	//	Base b{};
	//	std::cout << b << '\n';

	//	Derived d{};
	//	std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects

	//	Base& bref{ d };
	//	std::cout << bref << '\n';

	//	return 0;
	//}

	//class Base
	//{
	//public:
	//	// Here's our overloaded operator<<
	//	friend std::ostream& operator<<(std::ostream& out, const Base& b)
	//	{
	//		// Delegate printing responsibility for printing to virtual member function print()
	//		return b.print(out);
	//	}

	//	// We'll rely on member function print() to do the actual printing
	//	// Because print() is a normal member function, it can be virtualized
	//	virtual std::ostream& print(std::ostream& out) const
	//	{
	//		out << "Base";
	//		return out;
	//	}
	//};

	//// Some class or struct with an overloaded operator<<
	//struct Employee
	//{
	//	std::string name{};
	//	int id{};

	//	friend std::ostream& operator<<(std::ostream& out, const Employee& e)
	//	{
	//		out << "Employee(" << e.name << ", " << e.id << ")";
	//		return out;
	//	}
	//};

	//class Derived : public Base
	//{
	//private:
	//	Employee m_e{}; // Derived now has an Employee member

	//public:
	//	Derived(const Employee& e)
	//		: m_e{ e }
	//	{
	//	}

	//	// Here's our override print() function to handle the Derived case
	//	std::ostream& print(std::ostream& out) const override
	//	{
	//		out << "Derived: ";

	//		// Print the Employee member using the stream object
	//		out << m_e;

	//		return out;
	//	}
	//};

	//int main()
	//{
	//	Base b{};
	//	std::cout << b << '\n';

	//	Derived d{ Employee{"Jim", 4} };
	//	std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects

	//	Base& bref{ d };
	//	std::cout << bref << '\n';

	//	return 0;
	//}

	
}

namespace Exceptions
{
//	throw - 1; // throw a literal integer value
//	throw ENUM_INVALID_INDEX; // throw an enum value
//	throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
//	throw dX; // throw a double variable that was previously defined
//	throw MyException("Fatal Error"); // Throw an object of class MyException

	//try
	//{
	//	// Statements that may throw exceptions you want to handle go here
	//	throw - 1; // here's a trivial throw statement
	//}
	//catch (int x)
	//{
	//	// Handle an exception of type int here
	//	std::cerr << "We caught an int exception with value" << x << '\n';
	//}

	//int main()
	//{
	//	try
	//	{
	//		// Statements that may throw exceptions you want to handle go here
	//		throw - 1; // here's a trivial example
	//	}
	//	catch (double) // no variable name since we don't use the exception itself in the catch block below
	//	{
	//		// Any exceptions of type double thrown within the above try block get sent here
	//		std::cerr << "We caught an exception of type double\n";
	//	}
	//	catch (int x)
	//	{
	//		// Any exceptions of type int thrown within the above try block get sent here
	//		std::cerr << "We caught an int exception with value: " << x << '\n';
	//	}
	//	catch (const std::string&) // catch classes by const reference
	//	{
	//		// Any exceptions of type std::string thrown within the above try block get sent here
	//		std::cerr << "We caught an exception of type std::string\n";
	//	}

	//	// Execution continues here after the exception has been handled by any of the above catch blocks
	//	std::cout << "Continuing on our merry way\n";

	//	return 0;
	//}


	//int main()
	//{
	//	std::cout << "Enter a number: ";
	//	double x{};
	//	std::cin >> x;

	//	try // Look for exceptions that occur within try block and route to attached catch block(s)
	//	{
	//		// If the user entered a negative number, this is an error condition
	//		if (x < 0.0)
	//			throw "Can not take sqrt of negative number"; // throw exception of type const char*

	//		// Otherwise, print the answer
	//		std::cout << "The sqrt of " << x << " is " << std::sqrt(x) << '\n';
	//	}
	//	catch (const char* exception) // catch exceptions of type const char*
	//	{
	//		std::cerr << "Error: " << exception << '\n';
	//	}
	//}

	//double mySqrt(double x)
	//{
	//	// If the user entered a negative number, this is an error condition
	//	if (x < 0.0)
	//		throw "Can not take sqrt of negative number"; // throw exception of type const char*

	//	return std::sqrt(x);
	//}

	//int main()
	//{
	//	std::cout << "Enter a number: ";
	//	double x{};
	//	std::cin >> x;

	//	try // Look for exceptions that occur within try block and route to attached catch block(s)
	//	{
	//		double d = mySqrt(x);
	//		std::cout << "The sqrt of " << x << " is " << d << '\n';
	//	}
	//	catch (const char* exception) // catch exceptions of type const char*
	//	{
	//		std::cerr << "Error: " << exception << std::endl;
	//	}

	//	return 0;
	//}

	void D() // called by C()
	{
		std::cout << "Start D\n";
		std::cout << "D throwing int exception\n";

		throw - 1;

		std::cout << "End D\n"; // skipped over
	}

	void C() // called by B()
	{
		std::cout << "Start C\n";
		D();
		std::cout << "End C\n";
	}

	void B() // called by A()
	{
		std::cout << "Start B\n";

		try
		{
			C();
		}
		catch (double) // not caught: exception type mismatch
		{
			std::cerr << "B caught double exception\n";
		}

		try
		{
		}
		catch (int) // not caught: exception not thrown within try
		{
			std::cerr << "B caught int exception\n";
		}

		std::cout << "End B\n";
	}

	void A() // called by main()
	{
		std::cout << "Start A\n";

		try
		{
			B();
		}
		catch (int) // exception caught here and handled
		{
			std::cerr << "A caught int exception\n";
		}
		catch (double) // not called because exception was handled by prior catch block
		{
			std::cerr << "A caught double exception\n";
		}

		// execution continues here after the exception is handled
		std::cout << "End A\n";
	}

	//int main()
	//{
	//	std::cout << "Start main\n";

	//	try
	//	{
	//		A();
	//	}
	//	catch (int) // not called because exception was handled by A
	//	{
	//		std::cerr << "main caught int exception\n";
	//	}
	//	std::cout << "End main\n";

	//	return 0;
	//}

	//int main()
	//{
	//	try
	//	{
	//		throw 5; // throw an int exception
	//	}
	//	catch (double x)
	//	{
	//		std::cout << "We caught an exception of type double: " << x << '\n';
	//	}
	//	catch (...) // catch-all handler
	//	{
	//		std::cout << "We caught an exception of an undetermined type\n";
	//	}
	//}

	//struct GameSession
	//{
	//	// Game session data here
	//};

	//void runGame(GameSession&)
	//{
	//	throw 1;
	//}

	//void saveGame(GameSession&)
	//{
	//	// Save user's game here
	//}

	//int main()
	//{
	//	GameSession session{};

	//	try
	//	{
	//		runGame(session);
	//	}
	//	catch (...)
	//	{
	//		std::cerr << "Abnormal termination\n";
	//	}

	//	saveGame(session); // save the user's game (even if catch-all handler was hit)

	//	return 0;
	//}

	//struct GameSession
	//{
	//	// Game session data here
	//};

	//void runGame(GameSession&)
	//{
	//	throw 1;
	//}

	//void saveGame(GameSession&)
	//{
	//	// Save user's game here
	//}

	//class DummyException // a dummy class that can't be instantiated
	//{
	//	DummyException() = delete;
	//};

	//int main()
	//{
	//	GameSession session{};

	//	try
	//	{
	//		runGame(session);
	//	}
	//#ifndef NDEBUG // if we're in release node
	//	catch (...) // compile in the catch-all handler
	//	{
	//		std::cerr << "Abnormal termination\n";
	//	}
	//#else // in debug mode, compile in a catch that will never be hit (for syntactic reasons)
	//	catch (DummyException)
	//	{
	//	}
	//#endif

	//	saveGame(session); // save the user's game (even if catch-all handler was hit)

	//	return 0;
	//}
	
	//class Member
	//{
	//public:
	//	Member()
	//	{
	//		std::cerr << "Member allocated some resources\n";
	//	}

	//	~Member()
	//	{
	//		std::cerr << "Member cleaned up\n";
	//	}
	//};

	//class A
	//{
	//private:
	//	int m_x{};
	//	Member m_member;

	//public:
	//	A(int x) : m_x{ x }
	//	{
	//		if (x <= 0)
	//			throw 1;
	//	}

	//	~A()
	//	{
	//		std::cerr << "~A\n"; // should not be called
	//	}
	//};


	//int main()
	//{
	//	try
	//	{
	//		A a{ 0 };
	//	}
	//	catch (int)
	//	{
	//		std::cerr << "Oops\n";
	//	}

	//	return 0;
	//}

	//class ArrayException
	//{
	//private:
	//	std::string m_error;

	//public:
	//	ArrayException(std::string_view error)
	//		: m_error{ error }
	//	{
	//	}

	//	const std::string& getError() const { return m_error; }
	//};

	//class IntArray
	//{
	//private:
	//	int m_data[3]{}; // assume array is length 3 for simplicity

	//public:
	//	IntArray() {}

	//	int getLength() const { return 3; }

	//	int& operator[](const int index)
	//	{
	//		if (index < 0 || index >= getLength())
	//			throw ArrayException{ "Invalid index" };

	//		return m_data[index];
	//	}

	//};

	//int main()
	//{
	//	IntArray array;

	//	try
	//	{
	//		int value{ array[5] }; // out of range subscript
	//	}
	//	catch (const ArrayException& exception)
	//	{
	//		std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
	//	}
	//}

	//int main()
	//{
	//	try
	//	{
	//		// Your code using standard library goes here
	//		// We'll trigger one of these exceptions intentionally for the sake of the example
	//		std::string s;
	//		s.resize(std::numeric_limits<std::size_t>::max()); // will trigger a std::length_error or allocation exception
	//	}
	//	// This handler will catch std::exception and all the derived exceptions too
	//	catch (const std::exception& exception)
	//	{
	//		std::cerr << "Standard exception: " << exception.what() << '\n';
	//	}

	//	return 0;
	//}

	//class ArrayException : public std::exception
	//{
	//private:
	//	std::string m_error{}; // handle our own string

	//public:
	//	ArrayException(std::string_view error)
	//		: m_error{ error }
	//	{
	//	}

	//	// std::exception::what() returns a const char*, so we must as well
	//	const char* what() const noexcept override { return m_error.c_str(); }
	//};

	//class IntArray
	//{
	//private:
	//	int m_data[3]{}; // assume array is length 3 for simplicity

	//public:
	//	IntArray() {}

	//	int getLength() const { return 3; }

	//	int& operator[](const int index)
	//	{
	//		if (index < 0 || index >= getLength())
	//			throw ArrayException("Invalid index");

	//		return m_data[index];
	//	}

	//};

	//int main()
	//{
	//	IntArray array;

	//	try
	//	{
	//		int value{ array[5] };
	//	}
	//	catch (const ArrayException& exception) // derived catch blocks go first
	//	{
	//		std::cerr << "An array exception occurred (" << exception.what() << ")\n";
	//	}
	//	catch (const std::exception& exception)
	//	{
	//		std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
	//	}
	//}

	//class A
	//{
	//private:
	//	int m_x;
	//public:
	//	A(int x) : m_x{ x }
	//	{
	//		if (x <= 0)
	//			throw 1; // Exception thrown here
	//	}
	//};

	//class B : public A
	//{
	//public:
	//	B(int x) try : A{ x } // note addition of try keyword here
	//	{
	//	}
	//	catch (...) // note this is at same level of indentation as the function itself
	//	{
	//		// Exceptions from member initializer list or
	//		// from constructor body are caught here

	//		std::cerr << "Exception caught\n";

	//		throw; // rethrow the existing exception
	//	}
	//};

	//int main()
	//{
	//	try
	//	{
	//		B b{ 0 };
	//	}
	//	catch (int)
	//	{
	//		std::cout << "Oops\n";
	//	}
	//}

	//class Doomed
	//{
	//public:
	//	~Doomed()
	//	{
	//		std::cout << "Doomed destructed\n";
	//	}
	//};

	//void thrower()
	//{
	//	std::cout << "Throwing exception\n";
	//	throw 1;
	//}

	//void pt()
	//{
	//	std::cout << "pt (potentally throwing) called\n";
	//	//This object will be destroyed during stack unwinding (if it occurs)
	//	Doomed doomed{};
	//	thrower();
	//	std::cout << "This never prints\n";
	//}

	//void nt() noexcept
	//{
	//	std::cout << "nt (noexcept) called\n";
	//	//This object will be destroyed during stack unwinding (if it occurs)
	//	Doomed doomed{};
	//	thrower();
	//	std::cout << "this never prints\n";
	//}

	//void tester(int c) noexcept
	//{
	//	std::cout << "tester (noexcept) case " << c << " called\n";
	//	try
	//	{
	//		(c == 1) ? pt() : nt();
	//	}
	//	catch (...)
	//	{
	//		std::cout << "tester caught exception\n";
	//	}
	//}

	//int main()
	//{
	//	std::cout << std::unitbuf; // flush buffer after each insertion
	//	std::cout << std::boolalpha; // print boolean as true/false
	//	tester(1);
	//	std::cout << "Test successful\n\n";
	//	tester(2);
	//	std::cout << "Test successful\n";

	//	return 0;
	//}

	//class MoveClass
	//{
	//private:
	//	int* m_resource{};

	//public:
	//	MoveClass() = default;

	//	MoveClass(int resource)
	//		: m_resource{ new int{ resource } }
	//	{
	//	}

	//	// Copy constructor
	//	MoveClass(const MoveClass& that)
	//	{
	//		// deep copy
	//		if (that.m_resource != nullptr)
	//		{
	//			m_resource = new int{ *that.m_resource };
	//		}
	//	}

	//	// Move constructor
	//	MoveClass(MoveClass&& that) noexcept
	//		: m_resource{ that.m_resource }
	//	{
	//		that.m_resource = nullptr;
	//	}

	//	~MoveClass()
	//	{
	//		std::cout << "destroying " << *this << '\n';

	//		delete m_resource;
	//	}

	//	friend std::ostream& operator<<(std::ostream& out, const MoveClass& moveClass)
	//	{
	//		out << "MoveClass(";

	//		if (moveClass.m_resource == nullptr)
	//		{
	//			out << "empty";
	//		}
	//		else
	//		{
	//			out << *moveClass.m_resource;
	//		}

	//		out << ')';

	//		return out;
	//	}
	//};


	//class CopyClass
	//{
	//public:
	//	bool m_throw{};

	//	CopyClass() = default;

	//	// Copy constructor throws an exception when copying from
	//	// a CopyClass object where its m_throw is 'true'
	//	CopyClass(const CopyClass& that)
	//		: m_throw{ that.m_throw }
	//	{
	//		if (m_throw)
	//		{
	//			throw std::runtime_error{ "abort!" };
	//		}
	//	}
	//};

	//int main()
	//{
	//	// We can make a std::pair without any problems:
	//	std::pair my_pair{ MoveClass{ 13 }, CopyClass{} };

	//	std::cout << "my_pair.first: " << my_pair.first << '\n';

	//	// But the problem arises when we try to move that pair into another pair.
	//	try
	//	{
	//		my_pair.second.m_throw = true; // To trigger copy constructor exception

	//		// The following line will throw an exception
	//		//std::pair moved_pair{ std::move(my_pair) };
	//		std::pair moved_pair{ std::move_if_noexcept(my_pair) };  

	//		std::cout << "moved pair exists\n"; // Never prints
	//	}
	//	catch (const std::exception& ex)
	//	{
	//		std::cerr << "Error found: " << ex.what() << '\n';
	//	}

	//	std::cout << "my_pair.first: " << my_pair.first << '\n';

	//	return 0;
	//}

//Exception handling is best used when all of the following are true:
//
//The error being handled is likely to occur only infrequently.
//The error is serious and execution could not continue otherwise.
//The error cannot be handled at the place where it occurs.
//There isn’t a good alternative way to return an error code back to the caller.
}



//---------------------MAIN------------------------------------------------
//-------------------------------------------------------------------------
int main()
{
	namespace CTL = CppLearningTest;
	
 

	return 0;

	if (!std::cin) // handle bad input
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//continue;
	}

	int(*fncpt)(int, int) = nullptr;//FunctionPointer

	//int array[]{ 1, 2, 3, 9, 7, 6, 5, 4, 8 };
	//constexpr int length{ static_cast<int>(std::size(array)) }; // C++17
	////  constexpr int length{ sizeof(array) / sizeof(array[0]) }; // use instead if not C++17 capable

	//	// Step through each element of the array except the last
	//for (int iteration{ 0 }; iteration < length - 1; ++iteration)
	//{
	//	// Account for the fact that the last element is already sorted with each subsequent iteration
	//	// so our array "ends" one element sooner
	//	int endOfArrayIndex{ length - iteration };

	//	bool swapped{ false }; // Keep track of whether any elements were swapped this iteration

	//	// Search through all elements up to the end of the array - 1
	//	// The last element has no pair to compare against
	//	for (int currentIndex{ 0 }; currentIndex < endOfArrayIndex - 1; ++currentIndex)
	//	{
	//		// If the current element is larger than the element after it
	//		if (array[currentIndex] > array[currentIndex + 1])
	//		{
	//			// Swap them
	//			std::swap(array[currentIndex], array[currentIndex + 1]);
	//			swapped = true;
	//		}
	//	}

	//	// If we haven't swapped any elements this iteration, we're done early
	//	if (!swapped)
	//	{
	//		// iteration is 0 based, but counting iterations is 1-based.  So add 1 here to adjust.
	//		std::cout << "Early termination on iteration: " << iteration + 1 << '\n';
	//		break;
	//	}
	//}

	//// Now print our sorted array as proof it works
	//for (int index{ 0 }; index < length; ++index)
	//	std::cout << array[index] << ' ';

	//std::cout << '\n';


	/*std::array hello{ 'H','e', 'l', 'l', 'o' };
	std::cout << "Length: " << hello.size();
	std::cout << "\n" << hello[1] << hello.at(1) << std::get<1>(hello);*/

	//constexpr std::array prime{ 2, 3, 5, 7, 11 };

	//std::cout << std::get<3>(prime); // print the value of element with index 3
	//std::cout << std::get<9>(prime); // invalid index (compile error)

	//std::vector arr{ 9, 7, 5, 3, 1 };

	//auto length{ static_cast<std::size_t>(arr.size()) };  // in C++20, prefer std::ssize()
	//for (auto index{ length - 1 }; index >= 0; --index)
	//	std::cout << arr.data()[index] << ' ';       // use data() to avoid sign conversion warning

	//std::vector fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; // note use of std::array here

	//for (const auto& number : fibonacci)
	//{
	//	std::cout << number << ' ';
	//}

	//namespace Students
	//{
	//	enum Names : unsigned int
	//	{
	//		kenny, // 0
	//		kyle, // 1
	//		stan, // 2
	//		butters, // 3
	//		cartman, // 4
	//		max_students // 5
	//	};
	//}

	//int main()
	//{
	//	std::vector testScores{ 78, 94, 66, 77, 14 };

	//	testScores[Students::stan] = 76; // we are now updating the test score belonging to stan

	//std::cout << '\n';

	//std::vector<std::string_view> words{ "Alex", "Bobby", "Chad", "Dave" }; // sorted in alphabetical order

	//for (const auto& word : std::views::reverse(words)) // create a reverse view
	//	std::cout << word << ' ';

	//std::cout << '\n';


	//assert(!isPrime(0)); // terminate program if isPrime(0) is true
	//assert(!isPrime(1));
	//assert(isPrime(2));  // terminate program if isPrime(2) is false
	//assert(isPrime(3));
	//assert(!isPrime(4));
	//assert(isPrime(5));
	//assert(isPrime(7));
	//assert(!isPrime(9));
	//assert(isPrime(11));
	//assert(isPrime(13));
	//assert(!isPrime(15));
	//assert(!isPrime(16));
	//assert(isPrime(17));
	//assert(isPrime(19));
	//assert(isPrime(97));
	//assert(!isPrime(99));
	//assert(isPrime(13417));
	//std::cout << "Success!\n";

	int x{ 5 };
	int& ref{ x };  // get a reference to x
	int* ptr{ &x }; // get a pointer to x

	std::cout << x;
	std::cout << ref;  // use the reference to print x's value (5)
	std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

	ref = 6; // use the reference to change the value of x
	std::cout << x;
	std::cout << ref;  // use the reference to print x's value (6)
	std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

	*ptr = 7; // use the pointer to change the value of x
	std::cout << x;
	std::cout << ref;  // use the reference to print x's value (7)
	std::cout << *ptr << '\n'; // use the pointer to print x's value (7)

	int v{ 5 };

	int* ptr0{ &v };             // points to an "int" but is not const itself.  We can modify the value or the address.
	const int* ptr1{ &v };       // points to a "const int" but is not const itself.  We can only modify the address.
	int* const ptr2{ &v };       // points to an "int" and is const itself.   We can only modify the value.
	const int* const ptr3{ &v }; // points to a "const int" and is const itself.  We can't modify the value nor the address.

	//As a neat bit of trivia, because the compiler converts ptr[n] into* ((ptr)+(n)) when subscripting a pointer, 
	//this means we can also subscript a pointer as n[ptr]!The compiler converts this into* ((n)+(ptr)), 
	//which is behaviorally identical to* ((ptr)+(n)).Don’t actually do this though, as it’s confusing.

	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	for (; begin != end; ++begin)           // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' ';     // dereference our loop variable to get the current element
	}

	//void printArray(const int* begin, const int* end)
	//{
	//	for (; begin != end; ++begin)   // iterate from begin up to (but excluding) end
	//	{
	//		std::cout << *begin << ' '; // dereference our loop variable to get the current element
	//	}

	//	std::cout << '\n';
	//}

	//int main()
	//{
	//	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	//	const int* begin{ arr };                // begin points to start element
	//	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	//	printArray(begin, end);


	PRINTVCAT(5);        // rvalue
	PRINTVCAT(getint()); // rvalue
	int y{ 5 };
	PRINTVCAT(y);        // lvalue
	PRINTVCAT(std::string{ "Hello" }); // rvalue
	PRINTVCAT("Hello");  // lvalue
	PRINTVCAT(++y);      // lvalue
	PRINTVCAT(y++);      // rvalue
	
	std::cout << " " << '\n';
	std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

	std::cout << std::left; // left justify output

	std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
	std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
	std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
	std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
	std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
	std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
	std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
	std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
	std::cout << std::setw(16) << "long double:" << sizeof(long double) << " bytes\n";

	std::cout << std::boolalpha; // print bool as true or false rather than 1 or 0
	std::cout << "float: " << std::numeric_limits<float>::is_iec559 << '\n';
	std::cout << "double: " << std::numeric_limits<double>::is_iec559 << '\n';
	std::cout << "long double: " << std::numeric_limits<long double>::is_iec559 << '\n';

	//double zero{ 0.0 };

	//double posinf{ 5.0 / zero }; // positive infinity
	//std::cout << posinf << '\n';

	//double neginf{ -5.0 / zero }; // negative infinity
	//std::cout << neginf << '\n';

	//double z1{ 0.0 / posinf }; // positive zero
	//std::cout << z1 << '\n';

	//double z2{ -0.0 / posinf }; // negative zero
	//std::cout << z2 << '\n';

	//double nan{ zero / zero }; // not a number (mathematically invalid)
	//std::cout << nan << '\n';

	/*int bin{ 0b0010'0000 };
	int hex{ 0x20 };
	std::cout << std::format("{:b}\n", bin);
	std::cout << bin << '\n';
	std::cout << std::hex << hex << '\n';
	std::cout << std::dec << hex << '\n';*/
	
}

int doMath(int first, int second, int third, int fourth)
{
	return first + second * third / fourth;
}

