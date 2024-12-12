#include "Feld.h"
#include <cstdlib> 
#include <ctime>
#include <Windows.h>



Feld::Feld() { //Standartkonstruktor
	feld= new char* [row];
	
	for (int i = 0; i < row; i++) {

	}

	for (int i = 0; i < row; ++i)
		feld[i] = new char[column];

	// Verwenden Sie den Array
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < column; ++j)
			feld[i][j] = i * j;
}

Feld::Feld(int input1, int input2 ) {
	row		= input1;
	column  = input2;
	
	
	feld = new char* [row];

	for (int i = 0; i < row; i++) {

	}

	for (int i = 0; i < row; ++i)
		feld[i] = new char[column];


}



Feld::~Feld() {

	
	for (int j = 0; j < row; j++) {
			delete [] feld[j];
		}

		delete [] feld;
	
}
void Feld::initFeld() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			feld[i][j]= '-';
		}
	}
}

int Feld::dropPlaystonePC(char stone) {
	
	

	srand(time(0));
	

	Sleep(1000);
	int randColumn = rand() % (column + 1);

	cout<<endl<<"Computer ist am Zug und entscheidet sich fuer Spalte>>>> "<<randColumn;

	if (randColumn == 0) {
		randColumn = 1;
	}

	if (elementsColumn(randColumn - 1) >= 6) {

		while ((elementsColumn(randColumn - 1) >= 6)) {
			randColumn = rand() % (column + 1);
		}

	}


	for (int i = row - 1; i >= 0; i--) {
		if ((feld[i][randColumn - 1] != 'X') && (feld[i][randColumn - 1] != 'O')) { //wenn frei dann setzen
			feld[i][randColumn - 1] = stone;
			return randColumn; //Erfolgreich
		}
		else {
			continue;
		}
	}
	
	
}

bool Feld::dropPlaystone(int col, char stone) { //TODO MUSS SAFE ÜBERARBEITET WERDEN
	if (col < 1 || col > column) {
		cout << "Spalte existiert nicht!" << endl;
		return 0;
	}
	
	if (elementsColumn(col - 1) >= 6) {
		cout<<endl
			<<"*****************************" 
			<< endl 
			<< "Spalte ist voll! ID: " << col
			<< endl
			<< "*****************************"
			<< endl;

		while ((elementsColumn(col - 1) >= 6)) {
			cout << "Neue Spalte waehlen!>>>> ";
			cin >> col;
		}

		cout << "Spalte ist frei! ID: " << col << endl;
	}
	
	for (int i = row-1; i >= 0; i--) {
		if ((feld[i][col-1] != 'X') && (feld[i][col-1] != 'O')) { //wenn frei dann setzen
			feld[i][col-1] = stone;
			return 1; //Erfolgreich
		}
		else {
			continue;
		}
	}
	return 0; //Feld ist voll
	
}

bool Feld::isFieldFull() {
	int maxElements = row * column;
	int counterElements = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if ((feld[i][j] == 'X') || (feld[i][j] == 'O')) {
				counterElements++;
			}
		}
	}
	if (counterElements == maxElements) {
		cout << "Feld ist voll!, Unentschieden!";
		return true;
	}
	else {
		return false;
	}
}

bool Feld::checkRows(char stone) {
	int tmp = 0;
	int colNumber = 0;
	
	for (int i = 0; i < row; i++) { //Schleife für Jede Reihe
		

		
		
		while (colNumber < column) { //Schleife für Jedes Element in der Reihe

			if (feld[i][colNumber] == stone) {
				tmp++;
				if (tmp >= 4) return true;
			}
			else {
				tmp = 0; 
			}

			colNumber++;
			
		}
		colNumber = 0;
	}
	
	

	return false;
}

bool Feld::checkColumns(char stone) {
	int tmp = 0;
	int rowNumber = 0;

	for (int i = 0; i < row; i++) { //Schleife für Jede Spalte
		
		while (rowNumber < row) { //Schleife für Jedes Element in der Spalte

			if (feld[rowNumber][i] == stone) {
				tmp++;
				if (tmp >= 4) return true;
			}
			else {
				tmp = 0;
			}
			
			rowNumber++;
		}
		rowNumber = 0;
	}

	return false;
}


bool Feld::checkDiagonal(char stone) { //elemente welche nicht existieren werden überprüft,unbedingt anpassen!
	int tmp = 0;
	int tmpRow = 0;
	int tmpCol = 0;






	
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
		

			for (int iIndex = 0; iIndex < 4; iIndex++) { //Diagonale nach rechts oben

				tmpRow = i - iIndex;
				tmpCol = j + iIndex;

				if (inBorderRow(tmpRow) == true && inBorderColumn(tmpCol) == true) {
					if (feld[tmpRow][tmpCol] == stone) {
						tmp++;
						if (tmp >= 4) return true;
					}
				}	
				
			}
			tmp = 0;
			


			for (int iIndex = 0; iIndex < 4; iIndex++) { //Diagonale nach rechts oben

				tmpRow = i + iIndex;
				tmpCol = j + iIndex;

				if (inBorderRow(tmpRow) == true && inBorderColumn(tmpCol) == true) {
					if (feld[tmpRow][tmpCol] == stone) {
						tmp++;
						if (tmp >= 4) return true;
					}
				}

			}
			tmp = 0;

		}

		
	}
	

	return false;
}




bool Feld::isWin(char Playstone) {

	if ((checkColumns(Playstone) == true) || (checkRows(Playstone) == true) || (checkDiagonal(Playstone) == true) ) {
		cout << endl << endl <<"___________________________________________________________" << endl << endl;
		

		cout<<endl <<"Spieler "<<Playstone<<" hat gewonnen :D !"<<endl;


		std::cout << R"(

                                                                                                               
                .........              .........              .........               ........                 
               .         .            .         .            .         .            .         .                
                           .                      .         .            .         .            .              
            :   .:     ::   :      :   .-     ::   ..     :   .-.    ::   ..     :    :.    ::   ..            
                 .     .     .          .     ..    .     .    .     ..    .     .    .      .    .            
          :                   :  :                   :  :                   :  ..                  :           
          .                   .  .                   .  .                   .  ..                  .           
          :    :         :    :  :    :         :    :  :    :         :.   :  ..   ..        ..   :           
          .     .        .    .  .     .        .    .  .     .        .    .  .     .        .    .           
            :    .... ..    ..     :    .... ...   ..     :    . .. . .   ..     :    . .. . .    :            
            .               .      .               .                      .                      .             
              .            .         .            .         .            .         .            .              
               ...........            ...........            ...........            ...........                
                                                                                                               
                .........              .........              .........               ........                 
               .         .            .         .            .         .            .         .                
                           .         .            .         .            .         .            .              
            :   .:     ::   :      :   .:     ::   .      :   .:.    ::   ..     :    :.    .:   ..            
                 .     ..    .     .    :     ..    .     .    :     ..    .     .    :     ..    .            
          :                   :  :                   :  :                   :  ..                  :           
          .                   .  .                   .  .                   .  ..                  .           
          :    :         :    :  :    :         :    :  :    :         ..   :  ..   .         ..   :           
          .     .        .    .  .     .        .    .  .     .        .    .  .     .        .    .           
            :    .... ..    ..     :    .... ...   ..     :    . .. . .    .     :    . .. . .    :            
            .               .      .               .      .               .                      .             
              .            .         .            .         .            .         .            .              
               ...........            ...........            ...........            ...........                
                                                                                                               
                .........              .........              .........               ........                 
               .         .            .         .            .         .            .         .                
                           .         .            .         .            .         .            .              
            :   .:     :.   :      :   .:     ..   .      :   .:     .:   ..     :    :.    .:   ..            
            .   .:     ..    .     .    :     ..    .     .    :     ..    .     .    :     ..    .            
          :                   :  :                   :  :                   :  ..                  :           
          .                   .  .                   .  .                   .  ..                  .           
          :    :         :    :  :    :         .    :  :    :         ..   :  ..   .         ..   :           
          .     .        .    .  .     .        .    .  .     .        .    .  .     .        .    .           
            :    .... ..    ..     :    .... ...   ..     :    . .. . .    .     :    . .. . .    :            
            .               .      .               .      .               .      .               .             
              .            .         .            .         .            .         .            .              
               ...........            ...........            ...........            ...........                
                                                                                                               
                .........              .........              .........               ........                 
               .         .            .         .            .         .            .         .                
                           .         .            .         .            .         .            .              
            :   .:     ..   :      :   .:     ..   .      .    :     ..   .      .    :.    .:   ..            
            .   .:     ..    .     .   .:     ..    .     .    :     ..    .     .    :.    .:    .            
          :                   :  :                   :  :                   :  ..                  :           
          .                   .  .                   .  .                   .  ..                  .           
          :    :         .    :  :    :         .    :  :    :         ..   :  ..   .         ..   :           
          .    ..        .    .  .     .        .    .  .     .        .    .  ..    .        .    .           
            .    .... ..    ..     .    .... ...    .     :    . .. . .    .     :    . .. . .    :            
            .               .      .               .      .               .      .               .             
              .            .         .            .         .            .         .            .              
               ...........            ...........            ...........            ...........                
                                                                                                               
                .........              .........              .........               ........                 
               .         .            .         .            .         .            .         .                
                           .         .            .         .            .         .            .              
            .   .:     ..   .      .    :     ..   .      .    :     ..   .      .    :     ..   .             
            .   .:     :.    .     .   .:     :.    .     .   .:     .:    .     .    :.    .:    .            
          :                   :  :                   :  :                   :  ..                  :           
          :                   :  :                   :  .                   :  ..                  :           
          :    .         .    :  :    .         .    :  :    .         ..   :  ..   .         ..   :           
          :    ..        .    :  :    ..        .    :  .     .        .    :  ..    .        .    :           
            .    .  . ..    ..     .    .  . ...    .     .    .    . .    .     .    . .  . .    .            
            .       . .     .      .       . .     .      .         .     .      .      .  .     .             
              .            .         .            .         .            .         .            .              
               ...........            ...........            ...........            ...........                
                                                                                                               
                                                                                                               





)";

		cout << endl << endl << "___________________________________________________________" << endl << endl;
		return true;
	}
	else {
		//cout<<"kein Gewinner"<<endl;
		return false;
	}
		

	
}


int Feld::getColumn() {
	return column;
}

int Feld::getRow() {
	return row;
}

char** Feld::getPointer() {
	return feld;
}


bool Feld::inBorderRow(int row) {
	if (row < 0 || row >= this->row) {
		return false;
	}
	else {
		return true;
	}
}

bool Feld::inBorderColumn(int column) {
	if (column < 0 || column >= this->column) {
		return false;
	}
	else {
		return true;
	}
}


void Feld::wipeField() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			feld[i][j] = '-';
		}
	}
}

int Feld::elementsColumn(int col) {
	int counter = 0;

	if (col < 0 || col >= column) {
		return -1;
	}

	for (int i = 0; i < row; i++) {
		
		if ((feld[i][col] == 'X') || (feld[i][col] == 'O')) {
			counter++;
		}
	}
	return counter;
}

void Feld::printField() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << feld[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl<<endl;
}

void Feld::copyField(char (&src)[6][7]) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			
			src[i][j] = ' ';
			

		}

	}
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if ((feld[i][j] == 'X') || (feld[i][j] == 'O')) {
				src[i][j] = feld[i][j];
			}
			
		}
		
	}

	cout<<"Feld wurde kopiert!"<<endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout<<src[i][j]<<" ";
		}
		cout << endl;
	}
}



