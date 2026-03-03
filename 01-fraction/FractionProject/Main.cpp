#include <iostream>
#include "Fraction.h"


int main() {
	Fraction test1{ 10000, -10 };
	std::cout << test1.GetNumerator() << std::endl;
	std::cout << test1.GetDenominator() << std::endl;
	
	Fraction test2(42312);
	std::cout << test2.GetNumerator() << std::endl;
	std::cout << test2.GetDenominator() << std::endl;

	Fraction test3(0.75);
	std::cout << test3.GetNumerator() << std::endl;
	std::cout << test3.GetDenominator() << std::endl;

	Fraction test4(test1);
	std::cout << test4.GetNumerator() << std::endl;
	std::cout << test4.GetDenominator() << std::endl;

	test3 /= 3;
	std::cout << test3.GetNumerator() << std::endl;
	std::cout << test3.GetDenominator() << std::endl;

	test3 = test3 + 21;
	std::cout << test3.GetNumerator() << std::endl;
	std::cout << test3.GetDenominator() << std::endl;

	test3 = test3 * 21;
	std::cout << test3.GetNumerator() << std::endl;
	std::cout << test3.GetDenominator() << std::endl;

	test3 = test3 / 21;
	std::cout << test3.GetNumerator() << std::endl;
	std::cout << test3.GetDenominator() << std::endl;

	Fraction test5(21.25);

	//bool equal = test3 == test5;
	bool equal = 21.25 != test3;
	std::cout << equal << std::endl;
	bool greater = test3 < 21.25;
	std::cout << greater << std::endl;

	std::cout << "Fraction to Integer: " << test3.GetNumerator() << "/" << test3.GetDenominator() << " --> " << static_cast<int>(test3) << std::endl;

	Fraction test6(0, 5);
	std::cout << "Fraction to Boolean: " << test6.GetNumerator() << "/" << test6.GetDenominator() << " --> " << static_cast<bool>(test6) << std::endl;
	std::cout << "Fraction to String: " << test5.GetNumerator() << "/" << test5.GetDenominator() << " --> " << static_cast<std::string>(test5) << std::endl;
	
	PrintToConsole(test6);
	Fraction test8 = StringToFraction("0.5");
	std::cout << test8.GetNumerator() << std::endl;

	Fraction test10(0);
	std::cin >> test10;
	std::cout << test10;
}