#include<cmath>
#include<iostream>
#include<limits>

int validInput();

int main()	{

	float input;
	std::cout << "\nWelcome. Please enter a number: ";
	input = validInput();
	std::cout << "\nexp(" << input << ") is " << exp(input)<<std::endl;
}

int validInput()
{
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
