#include<cmath>
#include<iostream>
#include<limits>

//members
double validInput();
double findMiddle(double*);

const unsigned int n = 3;

int main()	{

	double temp[n];
	double middleOne;

	std::cout << "Welcome. Please enter 3 numbers."<< std::endl;

	for(uint8_t i = 0; i <n; i++)
    {
        temp[i]=validInput();
    }

	middleOne = findMiddle(temp);

	std::cout << "The middle number is " << middleOne << std::endl;
}

double validInput()	{

    double x;
    std::cin >> x;
    while(std::cin.fail())	{

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad input. Please enter a *number*: ";
        std::cin >> x;
    }
    return x;
}

double findMiddle(double* array)	{

	double max = array[0];
	double min = array[0];


    for(uint8_t i = 0; i < n; i++)
    {
        if(array[i] > max)
            max = array[i];

		if(array[i]< min)
			min = array[i];
    }

	for (uint8_t i = 0; i < n; i++) {

		if(array[i]!=min && array[i]!=max)
			return array[i];
	}

}
