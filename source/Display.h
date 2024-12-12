#pragma once
#include "Feld.h"
#include <iostream>
#include <stdexcept>
using namespace std;
class Display
{
private:
	
	int xDimension; //Reihen
	int yDimension; //Spalten
	int players;
	char** anker;
	Feld playerField;

	int chronik[42];
	int sizeChronik = 0;
	char chronikPlayStone[42];
	bool gameSaved = false;


public:

	Display();
	//Display(Feld& source);
	~Display();
	void initChronik();
	bool checkIfWon();
	void startDiaglogue();
	void displayField();
	int countX();
	int countO(); 
	void add(int column, char playStone);
	void undo(int moves);
	int launchGame();
	void saveGame();
	void loadGame();
	
};

