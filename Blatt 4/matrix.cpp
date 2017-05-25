#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

double neo[3][3];

void matrixIsAGoodMovie(double neo[3][3]);
void calculateStuff(double neo[3][3]);

int main() {

	matrixIsAGoodMovie(neo);
	calculateStuff(neo);
}

void matrixIsAGoodMovie(double neo[3][3])	{

	std::ifstream myfile;
	std::string file = "neo.txt";	//program can be edited to accept command-line arguments, (argv[1] etc...)
	myfile.open(file.c_str());

	if(!myfile)
	{
	     std::cout << "File does not exist." << std::endl;
	}

	std::cout << "The matrix is:"<<std::endl;
	for(unsigned i = 0; i < 3; i++)	{

		 for(unsigned j = 0; j < 3; j++ )	{

		        myfile >> neo[i][j];
			std::cout << neo[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << "-------------------------------"<<std::endl;
	myfile.close();
}

void calculateStuff(double neo[3][3])	{

	std::pair<double, double> values;

	values.first = neo[0][0]*((neo[1][1]*neo[2][2]) - (neo[2][1]*neo[1][2])) -neo[0][1]*(neo[1][0]*neo[2][2] - neo[2][0]*neo[1][2]) + neo[0][2]*(neo[1][0]*neo[2][1] - neo[2][0]*neo[1][1]);

	double temp = 0;

	for(unsigned i=0; i<3;i++)	{

		temp=std::abs(neo[0][i])+std::abs(neo[1][i])+std::abs(neo[2][i]);
		if(values.second<temp)
			values.second = temp;

	}
	std::cout<< "Determinant: " << values.first << ", norm: " << values.second << std::endl;

}
