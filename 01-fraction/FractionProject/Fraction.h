#pragma once

class Fraction
{
public:
	Fraction(const int num, const int denom);
	Fraction(const int num);
	Fraction(const double value);
	Fraction(Fraction& fraction);

	int GetNumerator() const;
	int GetDenominator() const;

	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);


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