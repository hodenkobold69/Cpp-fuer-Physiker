#include <iostream>
#include <iomanip>
#include <fstream>

double X[15], Y[15];
int length = 0;

double f(double x);
double L(int i, double x);

int main(int argc, char **argv)
{

	std::ifstream file("a16-interpol.dat");

	while(file >> X[length] >> Y[length])
	{
		length++;
	}

	file.close();

	std::ofstream output("output.dat");

	for(double x = X[0]; x <= X[length - 1]; x += 0.05)
	{
		output << x << "\t" << f(x) << std::endl;
	}

	output.close();
}

double L(int i, double x)
{
	double prod = 1;

	for(int k = 0; k < length; k++)
	{
		if(k == i)
			continue;

		prod *= (x - X[k]) / (X[i] - X[k]);
	}

	return prod;
}

double f(double x)
{
	double sum = 0;

	for(int i = 0; i < length; i++)
	{
		sum += Y[i] * L(i, x);
	}

	return sum;
}
