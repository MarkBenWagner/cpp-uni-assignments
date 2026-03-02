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

private:
	int numerator;
	int denominator;

	void Normalize();
	int GCDivisor(int num, int den);
};