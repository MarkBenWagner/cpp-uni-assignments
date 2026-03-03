#include <iostream>
#include "Fraction.h"
#include <stdexcept>
#include <numeric>
#include <string>


int Fraction::GCDivisor(int num, int den) {
	int res = std::min(std::abs(num), std::abs(den));
	while (res > 1) {
		if (num % res == 0 && den % res == 0)
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
	if (common != 0) {
		numerator /= common;
		denominator /= common;
	}
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

Fraction::Fraction(const Fraction& fraction)
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

Fraction& Fraction::operator+=(const Fraction& other) 
{
	numerator = numerator * other.denominator + other.numerator * denominator;
	denominator = denominator * other.denominator;

	Normalize();
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& other)
{
	numerator = numerator * other.denominator - other.numerator * denominator;
	denominator = denominator * other.denominator;

	Normalize();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
	numerator = numerator * other.numerator;
	denominator = denominator * other.denominator;

	Normalize();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& other)
{
	numerator = numerator * other.denominator;
	denominator = denominator * other.numerator;

	Normalize();
	return *this;
}

Fraction operator+(Fraction a, const Fraction& b)
{
	a += b;
	return a;
}

Fraction operator-(Fraction a, const Fraction& b)
{
	a -= b;
	return a;
}

Fraction operator*(Fraction a, const Fraction& b)
{
	a *= b;
	return a;
}

Fraction operator/(Fraction a, const Fraction& b)
{
	a /= b;
	return a;
}

bool operator==(const Fraction& a, const Fraction& b)
{
	if (a.GetNumerator() == b.GetNumerator() && a.GetDenominator() == b.GetDenominator())
		return true;
	else
		return false;
}

bool operator!=(const Fraction& a, const Fraction& b)
{
	if (a.GetNumerator() != b.GetNumerator() || a.GetDenominator() != b.GetDenominator())
		return true;
	else
		return false;
}


bool operator<(const Fraction& a, const Fraction& b)
{
	if (a.GetNumerator() * b.GetDenominator() < b.GetNumerator() * a.GetDenominator())
		return true;
	else
		return false;
}

bool operator>(const Fraction& a, const Fraction& b)
{
	if (b.GetNumerator() * a.GetDenominator() < a.GetNumerator() * b.GetDenominator())
		return true;
	else
		return false;
}

bool operator<=(const Fraction& a, const Fraction& b)
{
	if (a.GetNumerator() * b.GetDenominator() <= b.GetNumerator() * a.GetDenominator())
		return true;
	else
		return false;
}

bool operator>=(const Fraction& a, const Fraction& b)
{
	if (b.GetNumerator() * a.GetDenominator() <= a.GetNumerator() * b.GetDenominator())
		return true;
	else
		return false;
}

Fraction::operator int() const
{
	return numerator / denominator;
}

Fraction::operator double() const
{
	return static_cast<double>(numerator) / static_cast<double>(denominator);
}

Fraction::operator bool() const
{
	return numerator != 0;
}

Fraction::operator std::string() const
{
	std::string fraction = std::to_string(numerator) + "/" + std::to_string(denominator);
	return fraction;
}

void PrintToConsole(Fraction fraction)
{
	std::cout << static_cast<std::string>(fraction) << std::endl;
}

Fraction StringToFraction(std::string input)
{
	if (input.find('/') != std::string::npos && input.find('.') == std::string::npos)
		return Fraction(std::stoi(input.substr(0, input.find('/'))), std::stoi(input.substr(input.find('/') + 1)));
	else if (input.find('.') != std::string::npos)
		return Fraction(std::stod(input));
	else
		return Fraction(std::stoi(input.substr(0, input.length())));
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction)
{
	os << fraction.GetNumerator() << "/" << fraction.GetDenominator();
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& fraction)
{
	std::string input;
	is >> input;
	fraction = StringToFraction(input);
	return is;
}