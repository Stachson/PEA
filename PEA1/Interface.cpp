#include "Interface.h"

//Klasa s�u��ca do przechowywania wiadomo�ci wy�wietlanych na konsoli
//Stworzona po ty, by klada g��wna by�a mo�liwie jak najbardziej przejrzysta

Interface::Interface()
{

}

void Interface::main_menu() // glowne menu programu
{
	cout << "Wybierz, co chcesz zrobic" << endl;
	cout << "1 - Wczytac graf z pliku txt" << endl;
	cout << "2 - Wygenerowac graf losowo" << endl;
	cout << "3 - Brute Force" << endl;
	cout << "4 - B&B" << endl;
	cout << "5 - Wyswietlic wczytany/wygenerowany graf" << endl;
	cout << "6 - Opuscic program" << endl;
}

