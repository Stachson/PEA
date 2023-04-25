#pragma once
#include <iostream>
#include <fstream>
#include "Stack.h"
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;

class AdjacencyMatrix
{
	int n;
	long int** A;
	Stack* stack;
	int* sciezka1;
	int suma1;
	double PCFreq = 0.0;
	__int64 CounterStart = 0;
	int* xo;//tymczasowe najlepsze rozwi¹zanie
	int* x; //tymczasowe rozwi¹zanie
	int sumaxo;
	int sumax = 0;
	double T;
	

	public:
		double kryterium_stopu;
		double a;
		AdjacencyMatrix();
		~AdjacencyMatrix();
		bool load_matrix(string fileName);
		bool show_matrix();
		void symulowane_wyzarzanie();
		void algorytm_zachalnny();
		void StartCounter();
		double GetCounter();
		double probability();



};

