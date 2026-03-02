#include <iostream>
#include "Fraction.h"
#include <stdexcept>
#include <numeric>


int Fraction::GCDivisor(int num, int den) {
	int res = std::min(std::abs(num), std::abs(den));
	while (res > 1) {
		if (numerator % res == 0 && denominator % res == 0)
			break;
		res--;
	}
	return res;
}

void Fraction::Normalize() {
	if (denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}

	int common = GCDivisor(numerator, denominator);
	numerator /= common;
	denominator /= common;
}

Fraction::Fraction(const int num, const int denom) 
	: numerator{ num }
	, denominator{ denom }
{
	if (denom == 0) {
		throw std::invalid_argument("Denominator cannot be zero!");
	}
	else {
		Normalize();
	}
}

Fraction::Fraction(const int num)
	: numerator{ num }
	, denominator{ 1 }
{
	Normalize();
}

Fraction::Fraction(const double value)
{
	numerator = static_cast<int>(value * 1000000.0);
	denominator = 1000000;
	Normalize();
}

Fraction::Fraction(Fraction& fraction)
	: numerator{ fraction.GetNumerator() }
	, denominator{ fraction.GetDenominator() }
{
}

int Fraction::GetNumerator() const
{
	return numerator;
}

int Fraction::GetDenominator() const
{
	return denominator;
}
