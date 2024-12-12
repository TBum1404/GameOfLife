#include "Display.h"
#include <fstream>
#include <windows.h>
#include <limits>
Display::Display() {
	xDimension = 6;
	yDimension = 7;
	playerField.initFeld();
	anker = playerField.getPointer();
	initChronik();
	sizeChronik = 0;
}

//Display::Display(Feld &source) {
//	xDimension = source.getRow();
//	yDimension = source.getColumn();
//	anker = source.getPointer();
//	playerField = source;
//	
//}


Display::~Display() {

}

void Display::startDiaglogue() {


}

void Display::displayField() {
	cout<<endl;
	cout << endl;

	cout << "   1     2     3     4     5     6     7     " << endl;

	
	for (int i = 0; i < xDimension; i++) {
		cout << "+-----------------------------------------+" << endl;
		for (int j = 0; j < yDimension; j++) {
			if ((anker[i][j] != 'X') && (anker[i][j] != 'O')) {
				cout <<"|" << "     ";
				continue;
			}
			cout <<"|  " << anker[i][j]<<"  ";
		}
		cout << "|" ;
		cout << endl;
	}
	cout << "+-----------------------------------------+" << endl;

	cout<< endl;

}

int Display::launchGame() {
	
	int columnMove;
	cout << "Willkommen bei Vier Gewinnt!" << endl;
	cout << "Wie viele Spieler spielen? (1 oder 2)" << endl;
	cin >> players;

	int undomoves;
	char spielstandOpt;

	try {
		if (players != 1 && players != 2) {
			throw "Falsche Eingabe!";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
		exit(1);
	}

	if (players == 1) {
		cout << "Spieler 1: X" << endl;
		cout << "Computer: O" << endl;
		
		cout << "Spielstand laden? (j/n) >>>> ";
		cin >> spielstandOpt;

		if (spielstandOpt == 'j') {
			loadGame();
		}
		
		bool ergebnis = false;
		while(1){
			
			
			if (playerField.isFieldFull() == true) {
				break;
			}

			try {
				if (playerField.isFieldFull() == true) {
					throw "Feld ist voll";
				}
			}
			catch (const char* msg) {
				cerr << msg << endl;
				cout<< "Das Spiel wird beendet!" << endl;
				return 1;
			}


			cout << endl << "Spieler 1 ist dran, welche Spalte?(1 - 7 = Spalte; 0 = undo; 9 = Spiel speichern)>>>> ";
			//cin >> columnMove;
			
			
			
			
			try {
				if (!(cin >> columnMove) || (columnMove < 0) || (columnMove > 9)) {
					throw "Falsche Eingabe!";
				}
			}
			catch (const char* msg) {
				
				cout<<"Ungueltige Eingabe, neue Eingabe>>>>" << endl;
				while (!(cin >> columnMove) || columnMove < 0 || columnMove > 9) {
					cin.clear(); // löscht den Fehlerstatus
					cin.ignore(10000, '\n'); // ignoriert das falsche Eingabe
					cout << "Ungültige Eingabe. Bitte geben Sie eine Ganzzahl zwischen 0 und 9 ein: ";
				}
			}



			if (columnMove == 0) {
				cout << "Wie viele Zuege?: >>>> " ;
				cin >> undomoves;
				undo(undomoves);
				continue;
			}
			if (columnMove == 9) {
				saveGame();
				gameSaved = true;
				break;
			}
			

			playerField.dropPlaystone(columnMove, 'X');
			add(columnMove, 'X');
			displayField();
			ergebnis = playerField.isWin('X');
			if (ergebnis == true) {
				break;
			}
			

			if (playerField.isFieldFull() == true) {
				break;
			}
			
			
			add(playerField.dropPlaystonePC('O'), 'O');
			displayField();
			ergebnis = playerField.isWin('O');
			if (ergebnis == true) {
				break;
			}

		
		}
	}
	else {
		cout << "Spieler 1: X" << endl;
		cout << "Spieler 2: O" << endl;
		
		cout<< "Spielstand laden? (j/n) >>>> ";
		cin>> spielstandOpt;
		
		if (spielstandOpt == 'j') {
			loadGame();
		}	



		

		bool ergebnis = false;

		while (1) {


			if (playerField.isFieldFull() == true) { //VOll?
				break;
			}

			cout << endl << "Spieler 1 ist dran, welche Spalte? (1-7=Spalte; 0=undo ;9=Spiel speichern)>>>> ";
			

			try {
				if (!(cin >> columnMove) || (columnMove < 0) || (columnMove > 9)) {
					throw "Falsche Eingabe!";
				}
			}
			catch (const char* msg) {

				cout << "Ungueltige Eingabe, neue Eingabe>>>>" << endl;
				while (!(cin >> columnMove) || columnMove < 0 || columnMove > 9) {
					cin.clear(); // löscht den Fehlerstatus
					cin.ignore(10000, '\n'); // ignoriert das falsche Eingabe
					cout << "Ungültige Eingabe. Bitte geben Sie eine Ganzzahl zwischen 0 und 9 ein: ";
				}
			}

			if (columnMove == 0) {
				cout << "Wie viele Zuege?: >>>> ";
				cin >> undomoves;
				undo(undomoves);
				continue;
			}

			if (columnMove == 9) {
				saveGame();
				gameSaved = true;
				break;
			}




			playerField.dropPlaystone(columnMove, 'X'); //ZUG SPIELEN
			add(columnMove, 'X');
			displayField();
			ergebnis = playerField.isWin('X');
			if (ergebnis == true) {
				break;
			}

		
			if (playerField.isFieldFull() == true) { //VOll?
				break;
			}

			cout << endl << "Spieler 2 ist dran, welche Spalte?(1-7=Spalte; 0=undo ;9=Spiel speichern)>>>> ";
			

			try {
				if (!(cin >> columnMove) || (columnMove < 0) || (columnMove > 9)) {
					throw "Falsche Eingabe!";
				}
			}
			catch (const char* msg) {

				cout << "Ungueltige Eingabe, neue Eingabe>>>>" << endl;
				while (!(cin >> columnMove) || columnMove < 0 || columnMove > 9) {
					cin.clear(); // löscht den Fehlerstatus
					cin.ignore(10000, '\n'); // ignoriert das falsche Eingabe
					cout << "Ungültige Eingabe. Bitte geben Sie eine Ganzzahl zwischen 0 und 9 ein: ";
				}
			}

			if (columnMove == 0) {
				cout << "Wie viele Zuege?: >>>> ";
				cin >> undomoves;
				undo(undomoves);
				continue;
			}

			if (columnMove == 9) {
				saveGame();
				gameSaved = true;
				break;
			}

			

			playerField.dropPlaystone(columnMove, 'O'); //ZUG SPIELEN
			add(columnMove, 'O');
			displayField();
			ergebnis = playerField.isWin('X');
			if (ergebnis == true) {
				break;
			}

			


		}



	}

	
	if (gameSaved == true) {
		cout<<endl<<"Spiel wurde gespeichert und wird beendet, zum Weiterspielen Spielstand laden!"<<endl;
		return 0;
	}


	cout<<"Das Spiel ist vorbei!" << endl;

	std::cout << R"(





       
							 =++.                   
                           -@@@*                   
                           =@@@@                   
                          .%@@@%                   
                         -%@@@@=                   
                       -#@@@@@*                    
                     .*@@@@@@%.                    
                    :%@@@@@@@#:::--::.             
                   :%@@@@@@@@@@@@@@@@@#:           
           .::::..-%@@@@@@@@@@@@@@@@@@@#           
           @@@@@++@@@@@@@@@@@@@@@@@@@@@+           
           @@@@@**@@@@@@@@@@@@@@@@@@@@@-           
           @@@@@**@@@@@@@@@@@@@@@@@@@@@%           
           @@@@@**@@@@@@@@@@@@@@@@@@@@@+           
           @@@@@**@@@@@@@@@@@@@@@@@@@@#.           
           @@@@@**@@@@@@@@@@@@@@@@@@@@@:           
           @@@@@*+@@@@@@@@@@@@@@@@@@@@+            
           @@@@@*+@@@@@@@@@@@@@@@@@@@=             
           @@@@@++@@@@@@@@@@@@@@@@@@%:             
           :::::. .::--==++****+++=-. 







			               ...........                                   
                        .:::::::::::::::::.                               
                     ::::-:::::::::::::::-:::                             
                  .:-::-----:::-----:::-----:::.        :.  :: ::         
    : : :.      .:--:::-----:::-----:::-----:::--:.     .-.:: :-:.        
 .:.: : .:     :---:::::   ::::-----:::   ::::::--:      .--:::::         
  .::.::..    .::::::::     ::::::::::     .::::::::.   .:::.::.          
  .::::::.   .:::::::::     ::::::::::     ::::::::::...::::::::          
   :::::::...::::::::::.   .::::::::::.   .::::::::::::.::::::..          
   .::::::::::::::::::::   ::::::::::::   .::::::::::::    :::            
    .:::...:::::---:::::----:::-----:::----:::::----:::    .:::           
     :::  .-:::-----:::-----:::-----:::-----:::-----::::    .::-.         
    :::.  :-:::-----:::-----:::-----:::-----:::-----::::      :--.        
    :::   .::::::-:::::::-:::::::::::::::-:::::::-. .::::::::.:::-:       
   .:::...::::: .::::::::::::::::::::::::::::::::.  .:::::::..:::::.      
   ::::::::::::  :::::::::::::::::::::::::::::::..  :::::::::::.....      
   :::.:::..:::. .::::::::::::::::::::::::::::..    :::.                  
            ::::    :::::::::::::::::::::::::      .:::                   
            .::-.    ...----:::-----::::.-.        :::                    
              :--.         ::..-----....         .--:                     
               ---:.              .:            :--.                      
                .:::.     .::::::.::::.       .:::.                       
                 .:::....  ....:::.::::..  ...:::.                        
                  ..:::::.     .::::::::...::::.                          
                      ::::::::  .:::::::::::                              
                        .-::::::..:::::::-.                               
                              ...:--:::----                               
                                 .--:::-----                              
                                  :-:::----.                              
                                   .:::...                                
                                    :::                                   


)";

	return 0;
}

bool Display::checkIfWon() {
	
	if (playerField.isWin('X')==true);
	{
		cout << "X hat gewonnen!" << endl;
		return true;
	}

	if(playerField.isWin('O')==true){
		cout << "O hat gewonnen!" << endl;
		return true;
	}

	return false;

	
}



void Display::add(int column, char playStone) {
	
	chronik[sizeChronik] = column;
	chronikPlayStone[sizeChronik] = playStone;



	
	sizeChronik++;
}

void Display::undo(int moves) {

	

		sizeChronik -= moves;

		playerField.initFeld(); //Spielfeld leeren

		for(int i= 0; i < sizeChronik; i++) { //Feld neuzeichnen
			playerField.dropPlaystone(chronik[i], chronikPlayStone[i]);
		}
	

	
		initChronik(); //Chronik auf NULL setzen
		cout << "***********************************************************" <<  endl;
		cout << "Undone field:" << endl << endl;

		displayField();

	
		cout<< endl<<"***********************************************************" << endl << endl;

		//Da immer X als nächstes dran ist, muss entschieden werden wer der mover ist.

		int x = countX();
		int o = countO();

		int dif = x - o;

		if (dif != 0) {
			//wenn die dif null ist, dann kann x als nächstes dran sein
			
			if (players == 1) {
				playerField.dropPlaystonePC('O');
				displayField();
			}
			if (players == 2) {
				int columnMove;
				
				if(x>o){

					
					cout << endl << "Spieler 2 ist dran, welche Spalte?>>>> ";
					cin >> columnMove;
					playerField.dropPlaystone(columnMove, 'O');
					add(columnMove, 'O');
					displayField();
				}

				//if (o > x)  nicht nötig, da nächster zug sowie so x ist

				
			}
		
		}
		
}


void Display::initChronik() {
	for (int i = 0; i < 42; i++) {
		chronik[i] = 404;
	chronikPlayStone[i] = '-';
	}
	sizeChronik = 0;

}

int Display::countX() {
	int counter = 0;
	for (int i = 0; i < xDimension; i++) {
		for (int j = 0; j < yDimension; j++) {
			if (anker[i][j] == 'X') {
				counter++;
			}
		}
	}
	return counter;
}

int Display::countO() {
	int counter = 0;
	for (int i = 0; i < xDimension; i++) {
		for (int j = 0; j < yDimension; j++) {
			if (anker[i][j] == 'O') {
				counter++;
			}
		}
	}
	return counter;
}

void Display::saveGame() {
	string filename;
	cout << "Bitte geben Sie den Dateinamen ein: ";
	cin >> filename;
	
	ofstream file(filename);
	
	try {
		if (!file) {
			throw"Datei konnte nicht geoeffnet werden!";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
		while (!file) {
			cout << "Bitte geben Sie den Dateinamen ein: ";
			cin >> filename;
			file.open(filename);
		}
	}


	initChronik();

	for (int i = 0; i < yDimension; i++) { //Spalten
		for (int j = xDimension -1 ; j >= 0; j--) { //Reihen
			if (anker[j][i] == 'X' || anker[j][i] == 'O') {
				add(i+1, anker[j][i]); // +1 weil die Spalten von 1-7 gehen
				
			}
		}
	}

	for (int i = 0; i < sizeChronik; i++) {
		file << chronik[i];
		file << chronikPlayStone[i];
	}

	cout<<endl<<"Spiel wurde gespeichert!"<<endl;

	file.close();
}	

void Display::loadGame() {
	char tmpInt;
	char tmpChar;
	int intValue;
	int tmpSize = 0;
	
	string filename;
	cout << "Bitte geben Sie den Dateinamen ein: ";
	cin >> filename;
	
	ifstream file(filename);

	try {
		if (!file) {
			throw"Datei konnte nicht geoeffnet werden!";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
		while (!file) {
			cout << "Bitte geben Sie den Dateinamen ein: ";
			cin >> filename;
			file.open(filename);
		}
	}

	
	for (int i = 0; i < 42; i++) {

		file.get(tmpInt);
		intValue = tmpInt - '0';
		chronik[i] = intValue;

		file.get(chronikPlayStone[i]);

		
	}

	for (int i = 0; i < 10; i++) {
		cout << ".";
		Sleep(100);
	}
	
	

	cout << endl << "Spiel wurde geladen!" << endl;

	for (int i = 0; i < 42; i++) { //Feld neuzeichnen
		if ( (chronikPlayStone[i] != 'X') && (chronikPlayStone[i] != 'O')) {
			continue;
		}
		playerField.dropPlaystone(chronik[i], chronikPlayStone[i]);
		add(chronik[i], chronikPlayStone[i]);
		tmpSize++;
	}
	sizeChronik = tmpSize;
	displayField();


	
	//Da immer X als nächstes dran ist, muss entschieden werden wer der mover ist.

	int x = countX();
	int o = countO();

	int dif = x - o;

	if (dif != 0) {
		//wenn die dif null ist, dann kann x als nächstes dran sein

		if (players == 1) {
			playerField.dropPlaystonePC('O');
			displayField();
		}
		if (players == 2) {
			int columnMove;

			if (x > o) {


				cout << endl << "Spieler 2 ist dran, welche Spalte?>>>> ";
				cin >> columnMove;
				playerField.dropPlaystone(columnMove, 'O');
				add(columnMove, 'O');
				displayField();
			}

			


		}

	}

	file.close();
}