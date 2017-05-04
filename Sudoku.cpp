#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <windows.h>
#include<time.h>
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
//This method by Grant Williams
int getColor()
{
	string txtColor;
	cout << "Pick a text color for the solved numbers, any color: " << endl;
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
		cout << "Light Gray huh? Okay well if you say so... \n";
		return 7;
	}
	else if (txtColor == "8") {
		cout << "Dark Gray huh? Okay well if you say so... \n";
		return 8;
	}
	else if (txtColor == "9") {
		cout << "Light Blue huh? Okay well if you say so... \n";
		return 9;
	}
	else if (txtColor == "10") {
		cout << "Light Green huh? Okay well if you say so... \n";
		return 10;
	}
	else if (txtColor == "11") {
		cout << "Light Cyan huh? Okay well if you say so... \n";
		return 11;
	}
	else if (txtColor == "12") {
		cout << "Light Red huh? Okay well if you say so... \n";
		return 12;
	}
	else if (txtColor == "13") {
		cout << "Light Magenta huh? Okay well if you say so... \n";
		return 13;
	}
	else {
		cout << "That is not an option so I will pick for you... \n";
		srand(time(0));
		return (rand() % 14 + 1);
	}
}

//This method has the user pick a background setting
//By Grant Williams
int setBackColor()
{
	string backMode;
	int backColor = 15;
	cout << "Would you like to switch to a dark background?...\n";
	cout << "CAUTION: Certain color combinations are better than others \n";
	cout << "Y/N \n";
	getline(cin, backMode);
	if (backMode == "Y" || backMode == "y")
	{
		system("color 0F");
		backColor = 0;
		cout << "Dark it is then...\n";
	}
	else if (backMode == "N" || backMode == "n")
	{
		system("color F0");
		backColor = 15;
		cout << "Light it is then...\n";
	}
	else
	{
		system("color F0");
		backColor = 15;
		cout << "That's not an option...so light it will stay.\n";
	}
	return backColor;
}

// Printing the gamebord and reading numbers into the board by Amanda Foster
//Adding color by Grant Williams
void printSudoku(int mat[9][9], int check[9][9], int color, int backColor, int frontColor)
{
	int foreG = frontColor; int backG = backColor; int alt = color;
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

//Reading from text portion by Edgar Garza
void readInPuzz(string file, int puzz[9][9], int puzzTemp[9][9])
{
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

//Prints before anything else
void printASCII()
{
	cout << endl;
	string z = "    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  "; cout << z << endl;
	string a = "   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "; cout << a << endl;
	string b = "  *                                                                        *"; cout << b << endl;
	string c = " * *                                                                      * *"; cout << c << endl;
	string d = " * *                                                                      * *"; cout << d << endl;
	string e = " * *    _____                     _____       _    ___    ___  ___  ___   * *"; cout << e << endl;
	string f = " * *   |     | ___  _____  ___   |   __| ___ |_|  |_  |  | | ||_  ||   |  * *"; cout << f << endl;
	string g = " * *   |   --|| . ||     || . |  |__   ||  _|| |   _| |_ |_  ||_  || | |  * *"; cout << g << endl;
	string h = " * *   |_____||___||_|_|_||  _|  |_____||___||_|  |_____|  |_||___||___|  * *"; cout << h << endl;
	string i = " * *                                                                      * *"; cout << i << endl;
	string j = " * *                _____                        ___  ___                 * *"; cout << j << endl;
	string k = " * *               |   __| ___  ___  _ _  ___   |_  ||_  |                * *"; cout << k << endl;
	string l = " * *               |  |  ||  _|| . || | || . |  |  _||  _|                * *"; cout << l << endl;
	string m = " * *               |_____||_|  |___||___||  _|  |___||___|                * *"; cout << m << endl;
	string n = " * *                                     |_|                              * *"; cout << n << endl;
	string o = " * *                                                                      * *"; cout << o << endl;
	string p = " * *                    _____         _       _                           * *"; cout << p << endl;
	string q = " * *                   |   __| _ _  _| | ___ | |_  _ _                    * *"; cout << q << endl;
	string r = " * *                   |__   || | || . || . || '_|| | |                   * *"; cout << r << endl;
	string s = " * *                   |_____||___||___||___||_,_||___|                   * *"; cout << s << endl;
	string t = " * *                                                                      * *"; cout << t << endl;
	string u = " * *                                                                      * *"; cout << u << endl;
	string v = "  * *                                                                    * *"; cout << v << endl;
	string w = "   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "; cout << w << endl;
	string x = "    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  "; cout << x << endl;
}

void main()
{
	int a;
	system("color F0");

	printASCII();

	int backColor;
	int frontColor;

	if (setBackColor() == 0)
	{
		backColor = 0;
		frontColor = 15;
	}
	else
	{
		backColor = 15;
		frontColor = 0;
	}

	int puzz[row][col];
	int temp[row][col];
	int textColor;
	for (int fileNum = 1; fileNum <= 4; fileNum++)
	{
		textColor = getColor();
		string fileName = "samplesudoku" + to_string(fileNum) + ".txt";
		readInPuzz(fileName, puzz, temp);
		cout << "Unsolved Puzzle " + to_string(fileNum) + ": " << endl;
		printSudoku(puzz, temp, textColor, backColor, frontColor);
		cout << endl;

		if (isSolved(puzz) == true)
		{
			cout << "Solved Puzzle " + to_string(fileNum) + ": " << endl;
			printSudoku(puzz, temp, textColor, backColor, frontColor);
		}
		else
		{
			cout << "No Solution" << endl;
		}
	}

	cin >> a;
}
