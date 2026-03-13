#include <iostream>
#include <stdexcept>
#include <numeric>
#include <string>
#include "Fraction.h"


void Fraction::Normalize() {
	if (denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}
	int common = std::gcd(numerator, denominator);
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

Fraction Fraction::operator-() const
{
	Fraction result = *this;
	result.numerator = -result.numerator;
	return result;
}

Fraction& Fraction::operator-=(const Fraction& other)
{
	return *this += -other;
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
	if (other.denominator == 0) 
		throw std::invalid_argument("Denominator cannot be zero!");
	numerator = numerator * other.denominator;
	denominator = denominator * other.numerator;

	Normalize();
	return *this;
}

Fraction Fraction::operator+(const Fraction& other) const
{
	Fraction res{ *this };
	return res += other;
}

Fraction Fraction::operator-(const Fraction& other) const
{

	Fraction result{ *this };
	return result -= other;
}

Fraction Fraction::operator*(const Fraction& other) const
{
	Fraction res{ *this };
	return res *= other;
}

Fraction Fraction::operator/(const Fraction& other) const
{
	Fraction res{ *this };
	return res /= other;
}

bool Fraction::operator==(const Fraction& other) const
{
	return (numerator == other.numerator && denominator == other.denominator);
}

bool Fraction::operator!=(const Fraction& other) const
{
	return !(*this == other);
}


bool Fraction::operator<(const Fraction& other) const
{
	return (numerator * other.denominator < other.numerator * denominator);
}
	
bool Fraction::operator>(const Fraction& other) const
{
	return other < *this;
}

bool Fraction::operator<=(const Fraction& other) const
{
	return !(other < *this);
}

bool Fraction::operator>=(const Fraction& other) const
{
	return !(*this < other);
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
	return std::to_string(numerator) + "/" + std::to_string(denominator);
}

Fraction Fraction::Parse(const std::string& input)
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
	fraction = Fraction::Parse(input);
	return is;
}