#include <iostream>
#include "Interface.h"
#include "AdjacencyMatrix.h"
#include "Stack.h"
#include <windows.h>
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
	bool isRight;
	AdjacencyMatrix* matrix;
	matrix = new AdjacencyMatrix();
	/*
	int N = 20;
	long long int suma = 0;
	for (int i = 0; i < 100; i++)
	{
		matrix->random_problem(N);
		StartCounter();
		matrix->B_B(0);
		suma += GetCounter();
	}
	cout << suma / 100;
	*/
	
	while (true)
	{
		Interface::main_menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Podaj nazwe pliku z zakonczeniem .txt" << endl;
			cin >> fileName;
			isRight = matrix->load_matrix(fileName);
			if (!isRight)
				cout << "Niepowodzenie wgrania pliku" << endl;
			break;
		case 2:
			matrix->random_problem(10);
			matrix->show_matrix();
			break;

		case 3:  //Brute Force
			matrix->prepare();
			matrix->bruteForce(0);
			matrix->showResult();

			break;

		case 4:
			matrix->B_B(0);
			

			break;
		case 5:
			isRight = matrix->show_matrix();
			if (!isRight)
				cout << "Macierz nie istnieje" << endl;
			break;
		case 6:
			return 0;
			break;
		default:
			cout << "NIeprawidlowy znak" << endl;
			break;
		}
	}
	return 0;	
}
