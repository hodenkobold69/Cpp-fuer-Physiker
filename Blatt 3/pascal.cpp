#include<cmath>
#include<iostream>
#include<limits>
#include<iomanip>

void calculatePascal(int, int*);

int main()	{

	int n = 10;

	int curr_line[n]={};
	curr_line[0]=1;

	for (int i = 1; i <= n; i++) {

		calculatePascal(i, curr_line);

		for(int j = i; j < n; j++)
			std::cout << "   ";

		for(int j = 0; j < i; j++)
			std::cout << std::setw(6) << curr_line[j];

		std::cout << std::endl;
	}

}

void calculatePascal(int line, int* temp)	{

	for(int i=line-1; i>0; i--)
			temp[i]=temp[i]+temp[i-1];
}
