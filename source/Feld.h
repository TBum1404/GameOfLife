#pragma once
#include <iostream>
using namespace std;
class Feld
{
private:
	int column = 7;
	int row = 6;
	char** feld= NULL;

public:
	void initFeld();
	Feld();
	Feld(int, int);
	~Feld();
	bool isFieldFull();
	bool inBorderRow(int);
	bool inBorderColumn(int);
	int elementsColumn(int col);
	bool checkRows(char stone);
	bool checkColumns(char stone);
	bool checkDiagonal(char stone);
	bool isWin(char Playstone);
	int dropPlaystonePC(char stone); //Playstone NPC
	bool dropPlaystone(int col, char stone);
	int getColumn();
	int getRow();
	char** getPointer();
	void wipeField();
	void printField();
	void copyField(char (&src)[6][7]);
};

