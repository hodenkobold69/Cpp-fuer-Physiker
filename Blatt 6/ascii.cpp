#include <iostream>
#include <iomanip>
#include <fstream>

const char chars[] = ".,~=+:?$78DIMNOZ";
int width, height;

int main(int argc, char** argv)	{

	if(argc < 2)
	{
		std::cout << "Wrong syntax." << std::endl << "usage: " << argv[0] << " FILENAME.dat" << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	file >> width >> height;

	int x, y=0;

	while(y<height)	{

		int sym, num;

		if(!(file >> sym >> num))
			break;

		for(unsigned i=0; i<num;i++)	{

			std::cout << chars[sym];

			if(++x == width)	{

				std::cout << std::endl;
				x=0; y++;

			}
		}

	}
	file.close();
}
