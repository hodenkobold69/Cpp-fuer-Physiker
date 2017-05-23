#include <iostream>
#include <cmath>
#include <limits>

struct Progression{

	uint16_t start, steps, max;
};

uint16_t validInput();
Progression calcCollatz(Progression prog);

int main()	{

	Progression prog;

	std::cout << "Welcome. Please enter a starting point (integer): ";
	prog.start = validInput();
	prog = calcCollatz(prog);
	std::cout << "--------------END OF PROGRESSION--------------" << std::endl;
	std::cout << "Starting number: " << prog.start << ", Steps: " << prog.steps << ", Max: " << prog.max << std::endl;
}

uint16_t validInput()	{

    uint16_t x;
    std::cin >> x;
    while(std::cin.fail())	{

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad input. Please enter a *number*: ";
        std::cin >> x;
    }
    return x;
}

void announceProgress(uint16_t number, uint16_t step)	{

	std::cout << "Step " << step << ", current number: " << number << std::endl;
}

Progression calcCollatz(Progression prog)	{

	uint16_t currNumb = prog.start;

	while(currNumb != 1)	{

		uint8_t condition = currNumb%2;

		switch(condition)	{

			case 0:
				currNumb /= 2;
				break;
			case 1:
				currNumb = 3*currNumb+1;
				break;
		}

		if(prog.max < currNumb)
			prog.max = currNumb;

		prog.steps++;
		announceProgress(currNumb, prog.steps);
	}

	return prog;
}
