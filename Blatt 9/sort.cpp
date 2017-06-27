#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>

void quicksort(double* a, int left, int right);
void swap(double* ptr, int a, int b);

int main(int argc, char** argv)
{
	srand((unsigned int)time(0));

	int N = 1000;
	double A[N];

	for(int i = 0; i < N; i++)
		A[i] = double(rand())/RAND_MAX;

	std::cout << std::setw(6) << "Before:" << std::endl;
	for(int i = 0; i < N; i++)
		std::cout << A[i] << std::endl;

	std::clock_t start;
    double duration;

    start = std::clock();

	quicksort(A, 0, N - 1);

	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

	std::cout << std::setw(6) << std::endl << "After:" << std::endl;
	for(int i = 0; i < N; i++)
		std::cout << A[i] << std::endl;

	std::cout << "___________________________________" << std::endl;
	std::cout<<"time: "<< duration << std::endl;
}

void quicksort(double* a, int left, int right)	{

	int i = left;
	int j = right;
	double pivot = a[right];

	while(i<=j)	{

		while(a[i] < pivot)
			i++;

		while(a[j] > pivot)
			j--;

		if(i<=j)
			swap(a, i, j);
			i++;j--;
	}

	if(left < j)
		quicksort(a, left, j);
	if(i < right)
		quicksort(a, i, right);
}

void swap(double* ptr, int a, int b)	{

	double tmp = ptr[a];
	ptr[a] = ptr[b];
	ptr[b] = tmp;
}
