#include <iostream>
#include <cmath>
#include <iomanip>

#define F1	//trigger for function

/**	Constants **/
const double e_x = 1e-4;
const double e_f = 1e-3;

/**	Variables	**/
double x0 = -6, x1 = 10;
double newX = (x0 + x1)/2;

/**	Function declarations	**/
int sgn(double value);
double f1(double x);
double f2(double x);
double calcZero(double (*f)(double));

/**	Main program	**/
int main(int argc, char** argv)
{

	double (*f)(double) = &f1;
	double zero = calcZero(f);

	std::cout << "f(" << newX << ") = " << zero << std::endl;

}

int sgn(double value) {

	if(value < 0)
		return -1;
	else return 1;
}

double f1(double x)	{

	return cos(x) - x;
}

double f2(double x)	{

	return exp(x) - x*x*x;
}

double calcZero(double (*f)(double))	{

	if(sgn(f(x0)) == sgn(f(x1)))	{

		std::cout << "no zero in interval";
		return 1;
	}

	unsigned count = 0;
	while(std::abs(x0 - x1) > e_x && std::abs(f(newX)) > e_f)	{

		count++;
		if(sgn(f(newX)) == sgn(f(x0)))
			x0 = newX;
		else
			x1 = newX;

		std::cout << "Interval: [" << x0 << "," << x1 << "], step: " << count << ", f(" << newX << ")= " << f(newX) << std::endl;
		newX = (x0 + x1)/2;
	}

}
