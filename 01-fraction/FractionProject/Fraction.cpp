#include <iostream>
#include <stdexcept>
#include <numeric>
#include <string>
#include <sstream>
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
	
	Normalize();
}

Fraction::Fraction(const int num)
	: numerator{ num }
	, denominator{ 1 }
{
}

Fraction::Fraction(const double value)
{
	numerator = static_cast<int>(value * 1000000.0);
	denominator = 1000000;
	Normalize();
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
	numerator *= other.numerator;
	denominator *= other.denominator;

	Normalize();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& other)
{
	if (other.numerator == 0) 
		throw std::invalid_argument("Cannot divide by zero!");
	numerator *= other.denominator;
	denominator *= other.numerator;

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


Fraction operator+(const Fraction& a, const Fraction& b)
{
	Fraction result = a;
	result += b;
	return result;
}

Fraction operator-(const Fraction& a, const Fraction& b)
{
	Fraction result = a;
	result -= b;
	return result;
}

Fraction operator*(const Fraction& a, const Fraction& b)
{
	Fraction result = a;
	result *= b;
	return result;
}

Fraction operator/(const Fraction& a, const Fraction& b)
{
	Fraction result = a;
	result /= b;
	return result;
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
	return static_cast<double>(*this) < static_cast<double>(other);
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


std::ostream& operator<<(std::ostream& os, const Fraction& fraction)
{
	os << fraction.numerator << "/" << fraction.denominator;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& fraction)
{
	std::string input;
	is >> input;

	size_t slashPosition = input.find('/');
	size_t dotPosition = input.find('.');

	if (slashPosition != std::string::npos && dotPosition == std::string::npos)
	{
		fraction.numerator = std::stoi(input.substr(0, slashPosition));
		fraction.denominator = std::stoi(input.substr(slashPosition + 1));
	}
	else if (dotPosition != std::string::npos)
	{
		double value = std::stod(input);
		fraction.numerator = static_cast<int>(value * 10000000.0);
		fraction.denominator = 10000000;
	}
	else
	{
		fraction.numerator = std::stoi(input);
		fraction.denominator = 1;
	}
	fraction.Normalize();
	return is;
}

Fraction Fraction::Parse(const std::string& input)
{
	Fraction result;
	std::stringstream ss(input);
	ss >> result;
	return result;
}