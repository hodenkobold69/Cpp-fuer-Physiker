#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const int STEPDELAY = 150; //step delay in ms
int n; //size of system
int pivot = 1;	// 0/1 --> disable/enable pivotizing
int stepCount =0;

struct System{
	double** A;
	double* B;
};

System loadArraysFromFile(double** A, double* B, char* filePath);
void printSystem(double** A, double* B);
System solve(double** A, double* B);
void deallocateMemory(double** A, double* B);

int main(int argc, char** argv)	{

	if(argc < 2)
	{
		std::cout << "Wrong syntax." << std::endl << "usage: " << argv[0] << " FILENAME.dat [pivot/nopivot]" << std::endl;
		return 1;
	}

	if(argc == 3 && !strcmp(argv[2], "nopivot"))
	{
		pivot = 0;
		std::cout << "pivot disabled" << std::endl;
	}
	else
		std::cout << "pivot enabled" << std::endl;

	System system;
	system = loadArraysFromFile(system.A, system.B, argv[1]);

	std::cout << "input matrix:" << std::endl;
	printSystem(system.A, system.B);

	std::cout << "solving..." << std::endl;

	system = solve(system.A, system.B);

	std::cout << std::endl << "total stepcount: " << stepCount << std::endl;
	deallocateMemory(system.A, system.B);
}

System loadArraysFromFile(double** A, double* B, char* filePath)	{

	std::ifstream file(filePath);
	file >> n;

	/* MEMORY ALLOCATIONS */
	A = (double**)malloc(n*sizeof(double*));

	for(unsigned i=0; i<n; i++)
	 	A[i] = (double*)malloc(n*sizeof(double));

	B = (double*)malloc(n*sizeof(double));
	/* END OF MEMORY ALLOCATIONS */

	/* READ ARRAYS FROM FILE */
	for(unsigned row = 0; row < n; row++)
		for(unsigned col = 0; col < n; col++)
			file >> A[row][col];
	for(unsigned i = 0; i < n; i++)
		file >> B[i];

	file.close();
	/* END OF READ ARRAYS FROM FILE */
	System system = {A, B};
	return system;

}

void printSystem(double** A, double* B)	{

	for(unsigned row=0; row<n; row++)	{

		for(unsigned col=0; col<n; col++)
			std::cout << std::setw(8) << A[row][col];

		std::cout << " |" << std::setw(8) << B[row] <<std::endl;
	}
	usleep(STEPDELAY*1000);
}

System solve(double** A, double* B)	{

	System system = {A, B};

	for(int i = 0; i < n; i++)
	{

		/*	PIVOTIZING	*/
		if(pivot)
		{
			double max = 0.;
			int rowMax = i;

			for(int row = i; row < n; row++)
			{
				if(std::abs(A[row][i]) > max)
				{
					rowMax = row;
					max = std::abs(A[row][i]);
				}
			}

			if(max == 0.)
				continue;

			/*	SWAP ROWS	*/
			double* exA = A[i];
			A[i] = A[rowMax];
			A[rowMax] = exA;

			double exB = B[i];
			B[i] = B[rowMax];
			B[rowMax] = exB;

			stepCount++;
			printSystem(A, B);
		}

		/*	NORMALIZE ROW	*/
		{
			double normFactor = 1./A[i][i];
			for(int j = i; j < n; j++)
				A[i][j] *= normFactor;
			B[i] *= normFactor;

			stepCount++;
			printSystem(A, B);
		}

		/*	GENERATE ZEROES IN ROWS BELOW	*/
		for(int row = (i + 1); row < n; row++)
		{
			double factor = A[row][i];

			A[row][i] = 0;

			for(int j = (i + 1); j < n; j++)
			{
				A[row][j] -= A[i][j] * factor;
			}

			B[row] -= B[i] * factor;

			stepCount++;
			printSystem(A, B);
		}

	}

	/*	GENERATE DIAGONAL FORM	*/
	for(int row = (n - 1); row > 0; row--)
	{
		for(int j = row - 1; j >= 0; j--)
		{
			double factor = A[j][row];

			for(int i = row; i < n; i++)
			{
				A[j][row] = 0;
			}

			B[j] -= factor * B[row];

			stepCount++;
			printSystem(A, B);
		}
	}

	return system;
}

void deallocateMemory(double** A, double* B)	{

	for(int i = 0; i < n; i++)
		free(A[i]);
	free(A);
	free(B);
}
