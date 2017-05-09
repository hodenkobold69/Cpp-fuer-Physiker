#include<cmath>
#include<iostream>
#include<limits>

int validInput();

int main()	{

	double e=1;
	unsigned int i=1;

	while(((1+e)-1) > 0)	{

		e = e/2.0;
		std::cout << i << " 2*Epsilon= " << 2.0*e << std::endl;
		i++;
	}
}
