#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "Interface.h"
#include "AdjacencyMatrix.h"
using namespace std;


int main()
{
	int choice;
	string fileName;
	AdjacencyMatrix* matrix = new AdjacencyMatrix();
	bool czyPoprawna;
	
	while (true)
	{
		Interface::menu_glowne();
		cin >> choice;
		switch (choice)
		{
			case 1: //wczytaj dane z pliku
				cout << "Podaj nazwe pliku" << endl;
				cin >> fileName;
				czyPoprawna = matrix->load_matrix(fileName);
				if (!czyPoprawna)
					cout << "Operacja siê nie uda³a" << endl;
				break;
			case 2: //wyœwietl graf
				czyPoprawna = matrix->show_matrix();
				if (!czyPoprawna)
					cout << "operacja siê nie uda³a" << endl;
			break;
			case 3: //wielkosc populacji pocz¹tkowej
				cout << "Podaj wielkosc populacji poczatkowej:"<<endl;
				cin >> matrix->wielkosc_populacji;
				break;
			case 4: //wspolczynnik mutacji
				cout << "Wprowadz wspolczynnik mutacji:" << endl;
				cin >> matrix->wspolczynnik_mutacji;
				break;
			case 5: //wspó³czynnik krzy¿owania
				cout << "Wprowadz wspolczynnik krzyzowania:" << endl;
				cin >> matrix->wspolczynnik_krzyzowania;
				break;
			case 6: //metoda krzy¿owania

				break;
			case 7: //metoda mutacji

				break;
			case 8: //uruchom algorytm
				matrix->genetic_algorithm();
				break;
			case 9:
				cout << "Wprowadz kryterium stopu: " << endl;
				cin >> matrix->kryterium_stopu;
				matrix->kryterium_stopu = matrix->kryterium_stopu * 1000000000; //w nanosekundach
				break;
			case 10: //wyjdŸ z programu
				return 0;
				break;
			default:
				cout << "Wprowadzono zly znak" << endl;
		}
	}


}
