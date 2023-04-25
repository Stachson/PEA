#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include "Stack.h"
using namespace std;

class AdjacencyMatrix
{
	int** A; //macierz
	Stack* stackH = new Stack();
	int* sciezka;
	int* sciezka1;
	int test1;
	int upper = 2147483647;
	bool* visited;
	int** A1;
	int d;
	int dh;
	int v0;

	
	bool* tablica = new bool[n];

	struct wezel
	{
		int** B;
		int cost = 0;
		//int test;
		int* sciezka;
		wezel* parent;
		int dlugosc;
	};

	

	struct Porownaj_wezly
	{
		bool operator ()  (wezel &wezel1,wezel &wezel2)
		{
			if (wezel1.cost > wezel2.cost)	return true;
			if (wezel1.cost < wezel2.cost) return false;
		}
	};

	priority_queue<wezel, vector <wezel>,Porownaj_wezly> queue;


public:

	int n; //liczba wierzcho³ków
	AdjacencyMatrix();
	~AdjacencyMatrix();
	bool load_matrix(string file);
	bool show_matrix();
	void bruteForce(int v);
	void showResult();
	void prepare();
	void B_B(int v);
	int** copy_matrix(int **C);
	void bound(wezel* parent,int i);
	void random_problem(int N);
};

