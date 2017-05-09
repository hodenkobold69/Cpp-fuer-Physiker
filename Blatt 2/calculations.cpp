#include<cmath>
#include<iostream>
#include<limits>

enum t_mode{prod, sum};

int validInput();
double calculateProd(int);
double calculateSum(int);
t_mode chooseMode(int);

int main()	{

	int N;
	double result;
	t_mode mode;

	std::cout << "\nWelcome. Please select your mode (0=product, 1=double sum): ";

	N = validInput();
	mode = chooseMode(N);

	std::cout << "\nPlease enter N: ";
	N = validInput();

	if(mode==prod)	{

		result = calculateProd(N);

	} else if(mode==sum)	{

		result = calculateSum(N);
	}

	std::cout << "\nThe result was " << result << std::endl;
}

int validInput()	{

    int x;
    std::cin >> x;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad input. Please enter a *number*: ";
        std::cin >> x;
    }
    return x;
}

t_mode chooseMode(int n)	{

	switch(n)	{

		case 0: return prod;

		case 1: return sum;

		default:
			{
				std::cout << "Bad choice, dimwit. Try again! ";
				n = validInput();
				chooseMode(n);
			}
	}
}

double calculateProd(int N)	{

	int tempProd=1;

	for(int i=1; i<=N; i++)	{

		tempProd *= (3*i - 1);
	}

	return tempProd;
}

double calculateSum(int N)	{

	double tempSum = 0;

	for(int i=1; i<=N; i++)	{

		for(int j=1; j<=i; j++)	{

			tempSum += 1/(double(i)*double(j));
			std::cout << i << ", " << j << ", temp: " << 1/(double(i)*double(j)) << std::endl;
		}
	}

	return tempSum;
}
