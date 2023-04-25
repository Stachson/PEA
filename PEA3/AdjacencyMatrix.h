#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

class AdjacencyMatrix
{

	int** A;
	int n;
	int* sciezka = new int[n];
	double PCFreq = 0.0;
	__int64 CounterStart = 0;
	int rodzic1;
	int rodzic2;
	int min = 2147483647;
	
	struct osobnik
	{
		int *sciezka;
		int dlugosc;
	};

	osobnik * populacja_poczatkowa;
	osobnik* nowa_populacja;
	bool* odwiedzony;
	bool* wybrany;
	int* tablica2;
	

	public:
		double kryterium_stopu;
		int wielkosc_populacji = 0;
		double wspolczynnik_mutacji;
		double wspolczynnik_krzyzowania;
		AdjacencyMatrix();
		~AdjacencyMatrix();
		bool load_matrix(string fileName);
		bool show_matrix();
		void StartCounter();
		double GetCounter();
		void generate_population();
		void selection(); //seleckja rodziców
		void order_crossover(int j);//
		void genetic_algorithm();
		void mutation();
		void change_population();
		

};

