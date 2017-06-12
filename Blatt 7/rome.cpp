#include <iostream>
#include <string.h>

int parseRomanChar(char input);
char toUpper(char c);

int main(int argc, char **argv)
{
	char input[10];

	std::cout << "Welcome. Please enter a roman number: ";
	std::cin >> input;

	char *ptr = input;
	int result = 0;
	int lastVal = 0;

	for(;*ptr;ptr++)	{

		*ptr = toUpper(*ptr);
		int val = parseRomanChar(*ptr);

		if(val > lastVal)
			result -= lastVal;
		else
			result += lastVal;

		lastVal = val;
	}

	result += lastVal;

	std::cout << input << " is " << result << std::endl;
}

int parseRomanChar(char input)	{

	char roman[] = "IVXLCDM";
	int arab[] = {1, 5, 10, 50, 100, 500, 1000};

	char* ptr = strchr(roman, input);

	if(ptr)
		return arab[ptr - roman];
	else return 0;
}

char toUpper(char c)	{	//since you demanded...

	return (char)toupper(c);
}
