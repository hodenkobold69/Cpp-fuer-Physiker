#include <iostream>
#include <cstdlib>

const int size = 8;
int solutions=0;

bool isTakeable(int testRow, int testCol, int queen[])	{

    for(unsigned row=1; row<testRow; ++row)	{

      //test vertically
  		if(testCol==queen[row])
  			return true;

      //test diagonally
  		int dRow=testRow-row;
  		int dCol=testCol-queen[row];

  		if(abs(dRow)==abs(dCol))
  			return true;
    }

	return false;
}

void print(int fullRows, int queen[])
{
    char boardChar;

    for(unsigned row=1; row<=size; ++row)	{

		for(int col=1; col<=size; ++col)	{

		    if((row+col)%2 == 0)
				boardChar=' ';
			else
				boardChar='O';

		    if( row<=fullRows && col==queen[row])
				boardChar='X';

			std::cout << boardChar << boardChar;
		}

	std::cout << std::endl;
}
}

void placeQueen(int row, int queen[])	{

    for(int col=1; col<=size; ++col)	{

  		if(!isTakeable(row, col, queen))	{

  		    queen[row] = col;

  		    if(row==size)	{

    				std::cout << std::endl << "Found solution!" << std::endl;
            solutions++;
    				print(size, queen);
  		    }
  		    else placeQueen(row+1, queen);
  		}
    }
}

int main( void)
{
    int queen[size+1];
    placeQueen(1, queen);
    std::cout << "Solutions: " << solutions << std::endl;
}
