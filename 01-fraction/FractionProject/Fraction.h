#pragma once
#include <string>

class Fraction
{
public:
	Fraction() = default;
	Fraction(const int num, const int denom);
	Fraction(const int num);
	Fraction(const double value);
	Fraction(const Fraction& fraction);

	int GetNumerator() const;
	int GetDenominator() const;

	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	//toInt, toDouble, toBool, toString
	explicit operator int() const;
	explicit operator double() const;
	explicit operator bool() const;
	explicit operator std::string() const;


private:
	int numerator;
	int denominator;

	void Normalize();
	int GCDivisor(int num, int den);
};
	Fraction operator+(Fraction a, const Fraction& b);
	Fraction operator-(Fraction a, const Fraction& b);
	Fraction operator*(Fraction a, const Fraction& b);
	Fraction operator/(Fraction a, const Fraction& b);

	bool operator==(const Fraction& a, const Fraction& b);
	bool operator!=(const Fraction& a, const Fraction& b);

	bool operator<(const Fraction& a, const Fraction& b);
	bool operator>(const Fraction& a, const Fraction& b);
	bool operator<=(const Fraction& a, const Fraction& b);
	bool operator>=(const Fraction& a, const Fraction& b);

	void PrintToConsole(Fraction fraction);
	Fraction StringToFraction(std::string input);

	std::ostream& operator<<(std::ostream& os, const Fraction& f);
	std::istream& operator>>(std::istream& is, Fraction& f);