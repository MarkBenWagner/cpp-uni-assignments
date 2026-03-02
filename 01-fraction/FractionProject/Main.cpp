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
}