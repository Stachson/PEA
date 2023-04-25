#include <iostream>
#include <windows.h>
#include "Interface.h"
#include "AdjacencyMatrix.h"
using namespace std;


double PCFreq = 0.0;
__int64 CounterStart = 0;
void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!" << endl;

	PCFreq = double(li.QuadPart) / 1000000000.0;   //nanosekundy

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

int main()
{
	int choice;
	string fileName;
	bool isRight = false;
	AdjacencyMatrix* matrix;
	matrix = new AdjacencyMatrix();
	float test;


	while (true)
	{
		Interface::main_menu();
		cin >> choice;
		switch (choice)
		{
			case 1:
				cout << "Podaj nazwe pliku" << endl;
				cin >> fileName;
				isRight = matrix->load_matrix(fileName);
				if (!isRight)
					cout << "Blad wczytania pliku" << endl;
				break;
			case 2:
				test = rand() % 100 * 0.01;
				cout << test << endl;
				break;
			case 3:
				break;
			case 4:
				matrix->algorytm_zachalnny();
				matrix->symulowane_wyzarzanie();
				break;
			case 5:
				//miejsce na tabu search
				break;
			case 6:
				isRight = matrix->show_matrix();
				if (!isRight)
					cout << "Macierz nie istnieje" << endl;
				break;
			case 7:
				cout << "Wprowadzi kryterium stopu:" << endl;
				cin>>matrix->kryterium_stopu;
				matrix->kryterium_stopu = matrix->kryterium_stopu * 1000000000; //w nanosekundach
				break;
			case 8:
				cout << "Wprowadz wspolczynnik zmiany temperatury" << endl;
				cin >> matrix->a;
				break;
			case 9:
				return 0;
				break;
			default:
				cout << "Niepoprawny znak" << endl;
				break;
		}
	}
	return 0;
}

