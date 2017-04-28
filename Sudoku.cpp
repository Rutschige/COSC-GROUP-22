#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <windows.h>
using namespace std;

const int col = 9;
const int row = 9;

//Solving portion done by Grant Williams
//This method searches for any empty spots in the puzzle
bool foundEmpty(int mat[9][9], int &row, int &col)
{
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++) {
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

// This part was done be Amanda Foster
void printSudoku(int mat[9][9], int check[9][9])
{
	system("color F0");
	int black = 0; int white = 15; int green = 2;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD dColor = ((white & 0x0F) << 4) + (black & 0x0F);
	WORD gColor = ((white & 0x0F) << 4) + (green & 0x0F);
	SetConsoleTextAttribute(h, dColor);
	cout << " _______________________________________" << endl;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (j % 3 == 0) {
				cout << "||   ";
			}
			else {
				cout << "|   ";
			}

		}

		cout << "||" << endl;

		for (int j = 0; j <= 8; j++)
		{
			if (mat[i][j] != check[i][j]) 
			{
				if (j % 3 == 0) {
					if (mat[i][j] == 0)
					{
						cout << "||   ";
					}
					else
					{
						cout << "|| ";
						SetConsoleTextAttribute(h, gColor);
						cout << mat[i][j] << " ";
						SetConsoleTextAttribute(h, dColor);
					}
				}
				else {
					if (mat[i][j] == 0)
					{
						cout << "|   ";
					}
					else
					{
						cout << "| ";
						SetConsoleTextAttribute(h, gColor);
						cout << mat[i][j] << " ";
						SetConsoleTextAttribute(h, dColor);
					}
				}

			}
			else
			{
				if (j % 3 == 0) {
					if (mat[i][j] == 0)
					{
						cout << "||   ";
					}
					else
					{
						cout << "|| ";
						SetConsoleTextAttribute(h, dColor);
						cout << mat[i][j] << " ";
					}
				}
				else {
					if (mat[i][j] == 0)
					{
						cout << "|   ";
					}
					else
					{
						cout << "| ";
						SetConsoleTextAttribute(h, dColor);
						cout << mat[i][j] << " ";
					}
				}
			}
		}
		cout << "||" << endl;

		for (int x = 0; x <= 8; x++)
		{

			if (x % 3 == 0) {
				if (i == 2 || i == 5) {
					cout << "||===";

				}
				else {
					cout << "||___";
				}
			}

			else {
				if (i == 2 || i == 5) {
					cout << "|===";

				}
				else {
					cout << "|___";
				}
			}


		}
		cout << "||" << endl;

	}
}

void main()
{
	//Reading from text portion by Edgar Garza
	ifstream inFile;
	int a;

	inFile.open("samplesudoku1.txt");

	//Check for error
	if (inFile.fail())
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}

	int puzzTxt[row][col];
	int temp[row][col];

	//Loop through the file
	while (!inFile.eof())
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				inFile >> puzzTxt[i][j];
				temp[i][j] = puzzTxt[i][j];
			}

		}
	}
	cout << "Unsolved Puzzle: " << endl;
	printSudoku(puzzTxt, temp);
	cout << endl;

	if (isSolved(puzzTxt) == true)
	{
		cout << "Solved Puzzle: " << endl;;
		printSudoku(puzzTxt, temp);
	}
	else
	{
		cout << "No Solution" << endl;
	}
	cin >> a;
}
