#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std; 

//Shouldn't these constant global variables be here? - Edgar
const int col = 9;
const int row = 9;

//Solving portion done by Grant Williams
//This method searches for any empty spots in the puzzle
bool foundEmpty(int mat[9][9], int &row, int &col)
{
	for ( row = 0; row < 9; row++) {
		for ( col = 0; col < 9; col++) {
			if (mat[row][col] == 0) {
				return true;
			}
		}
	}
	return false;
}

//This method check if a certain int is anywhere in the given row
bool inRow(int mat[9][9], int r, int check)
{
	for (int c = 0; c < 9; c++) {
		if (mat[r][c] == check) {
			return true;
		}
	}
	return false;
}

//This method checks if a certain int is anywhere in the given column
bool inCol(int mat[9][9], int c, int check)
{
	for (int r = 0; r < 9; r++) {
		if (mat[r][c] == check) {
			return true;
		}
	}
	return false;
}

//This method checks if a certain int is anywhere within a 3x3 block in the puzzle, given a starting column and row
bool inBox(int mat[9][9], int rstart, int cstart, int check)
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (mat[rstart + r][cstart + c] == check) {
				return true;
			}
		}
	}
	return false;
}

//This method uses the 3 checking methods to ensure a given int is in a legal spot in the puzzle
bool isLegal(int mat[9][9], int row, int col, int check)
{
	if (inRow(mat, row, check) || inCol(mat, col, check)
		|| inBox(mat, row - row % 3, col - col % 3, check))
	{
		return false;
	}
	else 
	{
		return true;
	}
}

//This method uses all above methods to solve the sudoku puzzle
bool isSolved(int mat[9][9])
{
	int row, col;
	if (!foundEmpty(mat, row, col))
	{
		return true;
	}
	for (int i = 1; i <= 9; i++)
	{
		if (isLegal(mat, row, col, i))
		{
			mat[row][col] = i;
			if (isSolved(mat))
			{
				return true;
			}
			else
			{
				mat[row][col] = 0;
			}
		}
	}
	return false;
}

//Needs tp print out sudoku grid instead of "solved" // This part was done be Amanda Foster
void printSudoku(int mat[9][9])
{
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			
			cout << "|   " ;
			
		}
		cout << "|" << endl;
		
		for (int j = 0; j <= 8; j++)
		{
			
			cout << "| " << mat[i][j] << " ";

		}
	
		
		cout<< "|" << endl;

		for (int j = 0; j <= 8; j++)
		{
			system("color F0");
			cout << "|___";

		}
		
		cout << "|" << endl;

	}
}

//Needs to read in text files as input instead of hardcoded puzzles
void main()
{
	//Reading from text portion by Edgar Garza
	ifstream inFile;

	inFile.open("samplesudoku1.txt");

	//Check for error
	if (inFile.fail())
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}

	int puzzTxt[row][col];

	//Loop through the file
	while (!inFile.eof())
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				inFile >> puzzTxt[i][j];
			}
				
		}
	}
	
	//Prints the text file 9x9
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << puzzTxt[i][j] << " ";
		}
		cout << endl;
	}

	/*int puzz[9][9] = 
	{ { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
	{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
	{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
	{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
	{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
	{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
	{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
	*/
	
	if (isSolved(puzzTxt) == true)
	{
		printSudoku(puzzTxt);
	}
	else
	{
		cout << "No Solution" << endl;
	}
	system("pause");	
}
