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




int main()
{
	namespace CTL = CppLearningTest;

	std::vector data1{ 84, 92, 76, 81, 56 };
	std::cout << ExVec::findMax(data1) << '\n';

	std::vector data2{ -13.0, -26.7, -105.5, -14.8 };
	std::cout << ExVec::findMax(data2) << '\n';

	std::vector<int> data3{ };
	std::cout << ExVec::findMax(data3) << '\n';

	return 0;

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

