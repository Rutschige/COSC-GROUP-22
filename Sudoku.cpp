#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
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

//Allows user to pick the color of the solved portion of the puzzle
int getColor()
{
	string txtColor;
	cout << "Pick a color for the solved numbers, any color: " << endl;
	cout << "1 for Blue \n" << "2 for Green \n" << "3 for Cyan \n" << "4 for Red \n" << "5 for Magenta \n" << "6 for Brown \n" 
		 << "7 for Light Gray \n" << "8 for Dark Gray \n" << "9 for Light Blue \n" << "10 for Light Green \n" << "11 for Light Cyan \n" 
		 << "12 for Light Red \n" << "13 for Light Magenta \n" << endl;
	getline(cin, txtColor);
	if (txtColor == "1") {
		cout << "Blue huh? Okay well if you say so... \n";
		return 1;
	}
	else if (txtColor == "2") {
		cout << "Green huh? Okay well if you say so... \n";
		return 2;
	}
	else if (txtColor == "3") {
		cout << "Cyan huh? Okay well if you say so... \n";
		return 3;
	}
	else if (txtColor == "4") {
		cout << "Red huh? Okay well if you say so... \n";
		return 4;
	}
	else if (txtColor == "5") {
		cout << "Magenta huh? Okay well if you say so... \n";
		return 5;
	}
	else if (txtColor == "6") {
		cout << "Brown huh? Okay well if you say so... \n";
		return 6;
	}
	else if (txtColor == "7") {
		cout << "Light gray huh? Okay well if you say so... \n";
		return 7;
	}
	else if (txtColor == "8") {
		cout << "Dark gray huh? Okay well if you say so... \n";
		return 8;
	}
	else if (txtColor == "9") {
		cout << "Light blue huh? Okay well if you say so... \n";
		return 9;
	}
	else if (txtColor == "10") {
		cout << "Light green huh? Okay well if you say so... \n";
		return 10;
	}
	else if (txtColor == "11") {
		cout << "Light cyan huh? Okay well if you say so... \n";
		return 11;
	}
	else if (txtColor == "12") {
		cout << "Light red huh? Okay well if you say so... \n";
		return 12;
	}
	else if (txtColor == "13") {
		cout << "Light Magenta huh? Okay well if you say so... \n";
		return 13;
	}
	else {
		cout << "That's not an option sorry... " << endl;
		return 0;
	}
}

// Printing the gamebord and reading numbers into the board by Amanda Foster
//Adding color by Grant Williams
void printSudoku(int mat[9][9], int check[9][9], int color)
{
	int foreG = 0; int backG = 15; int alt = color;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD dColor = ((backG & 0x0F) << 4) + (foreG & 0x0F);
	WORD aColor = ((backG & 0x0F) << 4) + (alt & 0x0F);
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
						SetConsoleTextAttribute(h, aColor);
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
						SetConsoleTextAttribute(h, aColor);
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
	cout << endl;
}

void readInPuzz(string file, int puzz[9][9], int puzzTemp[9][9])
{
	//Reading from text portion by Edgar Garza
	//Puzzle in
	ifstream inFile;
	inFile.open(file);

	//Check for error
	if (inFile.fail())
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}

	//Loop through the file
	while (!inFile.eof())
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				inFile >> puzz[i][j];
				puzzTemp[i][j] = puzz[i][j];
			}

		}
	}
}

void main()
{
	int a;
	system("color F0");
	
	//Puzzle 1
	int puzz1[row][col];
	int temp[row][col];
	int color = getColor();
	readInPuzz("samplesudoku1.txt", puzz1, temp);
	cout << "Unsolved Puzzle 1: " << endl;
	printSudoku(puzz1, temp, color);
	cout << endl;

	if (isSolved(puzz1) == true)
	{
		cout << "Solved Puzzle 1: " << endl;
		printSudoku(puzz1, temp, color);
	}
	else
	{
		cout << "No Solution" << endl;
	}
	
	//Puzzle 2
	int puzz2[row][col];
	int temp2[row][col];
	color = getColor();
	readInPuzz("samplesudoku2.txt", puzz2, temp2);
	cout << "Unsolved Puzzle 2: " << endl;
	printSudoku(puzz2, temp2, color);
	cout << endl;

	if (isSolved(puzz2) == true)
	{
		cout << "Solved Puzzle 2: " << endl;
		printSudoku(puzz2, temp2, color);
	}
	else
	{
		cout << "No Solution" << endl;
	}

	//Puzzle 3
	int puzz3[row][col];
	int temp3[row][col];
	color = getColor();
	readInPuzz("samplesudoku3.txt", puzz3, temp3);
	cout << "Unsolved Puzzle 3: " << endl;
	printSudoku(puzz3, temp3, color);
	cout << endl;

	if (isSolved(puzz3) == true)
	{
		cout << "Solved Puzzle 3: " << endl;
		printSudoku(puzz3, temp3, color);
	}
	else
	{
		cout << "No Solution" << endl;
	}

	//Puzzle 4
	int puzz4[row][col];
	int temp4[row][col];
	color = getColor();
	readInPuzz("samplesudoku4.txt", puzz4, temp4);
	cout << "Unsolved Puzzle 4: " << endl;
	printSudoku(puzz4, temp4, color);
	cout << endl;

	if (isSolved(puzz4) == true)
	{
		cout << "Solved Puzzle 4: " << endl;
		printSudoku(puzz4, temp4, color);
	}
	else
	{
		cout << "No Solution" << endl;
	}

	cin >> a;
}
