#include "constants.h"
#include "io.h"
#include "add.h"
#include "4xex.h"
#include "5xe.h"
#include "6xe.h"
#include "8xe.h"
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
	void selectionSort_t(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);

	using ValidateFunction = bool(*)(int, int);
	bool validate(int x, int y, bool (*fcnPtr)(int, int)); // ugly
	bool validate(int x, int y, ValidateFunction pfcn); // clean

	//#include <functional>
	bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and takes two int parameters
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

