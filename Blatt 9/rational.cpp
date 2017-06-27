#include <iostream>
#include <stdlib.h>
#include <numeric>

class Ratio	{

	long numerator, denominator;
	void cancel();
public:
	Ratio(long numerator, long denominator);
	void set(long numerator, long denominator);
	Ratio operator+(const Ratio& b) const;
	Ratio operator-() const;
	Ratio operator-(const Ratio& b) const;
	Ratio operator*(const Ratio& b) const;
	Ratio operator/(const Ratio& b) const;
	operator double() const;
	void print();
};

Ratio::Ratio(long numerator, long denominator)	{

	set(numerator, denominator);
}

void Ratio::set(long numerator, long denominator)	{

	this->numerator = numerator;
	this-> denominator = denominator;
	this->cancel();
}

void Ratio::cancel()	{

	long gcd = std::gcd(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;

	if(denominator < 0)	{

		denominator = -denominator;
		numerator = -numerator;
	}
}

Ratio Ratio::operator+(const Ratio& b) const	{

	long lcm = std::lcm(this->denominator, b.denominator);
	long one = lcm/this->denominator, two = lcm/b.denominator;

	Ratio result(one*this->numerator + two*b.numerator, lcm);
	result.cancel();
	return result;
}

Ratio Ratio::operator-() const	{

	return Ratio(-this->numerator, this->denominator);
}

Ratio Ratio::operator-(const Ratio& b) const	{

 	return *this + (-b);
}

Ratio Ratio::operator*(const Ratio& b) const	{

	Ratio result(this->numerator * b.numerator, this-> denominator * b.denominator);
	result.cancel();
	return result;
}

Ratio Ratio::operator/(const Ratio& b) const	{

	Ratio result(this->numerator * b.denominator, this-> denominator * b.numerator);
	result.cancel();
	return result;
}

Ratio::operator double() const	{

	return (double)(this->numerator)/(this->denominator);
}

void Ratio::print()	{

	std::cout << "(" << this->numerator << " / " << this->denominator << ")" << std::endl;
}

int main(int argc, char** argv)	{
	
	Ratio a(2, 25), b(7, 5), c(2, 5), d(1,4), e(1,3);
	Ratio result = (a / b) - c*(-d + e);
	result.print();
}
