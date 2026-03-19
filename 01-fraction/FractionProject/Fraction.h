#pragma once
#include <string>

class Fraction
{
public:
	Fraction() = default;
	Fraction(const int num, const int denom);
	Fraction(const int num);
	Fraction(const double value);

	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	Fraction operator+(const Fraction& other) const;
	Fraction operator-(const Fraction& other) const;
	Fraction operator*(const Fraction& other) const;
	Fraction operator/(const Fraction& other) const;

	Fraction operator-() const;

	bool operator==(const Fraction& b) const;
	bool operator!=(const Fraction& b) const;

	bool operator<(const Fraction& b) const;
	bool operator>(const Fraction& b) const;
	bool operator<=(const Fraction& b) const;
	bool operator>=(const Fraction& b) const;

	//toInt, toDouble, toBool, toString
	explicit operator int() const;
	explicit operator double() const;
	explicit operator bool() const;
	explicit operator std::string() const;

	static Fraction Parse(const std::string& input);

	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::istream& operator>>(std::istream& is, Fraction& f);


private:
	int numerator = 0;
	int denominator = 1;

	void Normalize();
};


Fraction operator+(const Fraction& a, const Fraction& b);
Fraction operator-(const Fraction& a, const Fraction& b);
Fraction operator*(const Fraction& a, const Fraction& b);
Fraction operator/(const Fraction& a, const Fraction& b);