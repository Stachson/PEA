#include "AdjacencyMatrix.h"



AdjacencyMatrix::AdjacencyMatrix() //konstruktor, ustawia ilosc przechowywanych wierzcholkow na 0
{
	n = 0;
	sciezka = NULL;
	srand(time(NULL));
}
AdjacencyMatrix::~AdjacencyMatrix()
{
	if (n != 0)
	{
		for (int i = 0; i < n; i++)
			delete A[i];
		delete[] A;
	}
}

void AdjacencyMatrix::random_problem(int N)    //metodam do generowania losowej instancji grafu
{
	if (n != 0)
	{
		for (int i = 0; i < N; i++)				//czyszczenie miejsca po poprzedniej macierzy, je�eli istnieje
			delete A[i];
		delete[] A;
	}
	n = N;									

	A = new int* [N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new int[N];														// alokacja pami�ci na now� macierz
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i != j)
				A[i][j] = rand() % 100 + 1;										//losowanie nowego grafu
			else
				A[i][j] = 0;													//0, poniewa� nie chcemy p�tli
		}
	}

}

bool AdjacencyMatrix::load_matrix(string fileName) //metoda sluzaca do ladowania zawartosci pliku tekstowego do macierzy sasiedztwa
{
	if (n != 0)
	{
		for (int i = 0; i < n; i++)					//usuwanie pami�ci po poprzedniej macierzy
			delete A[i];
		delete[] A;
	}
	fstream file;
	file.open(fileName.c_str(), ios::in);   //otworzenie pliku tekstowego przekazanego jako parametr metody

	if (file.good() == false)				//funkcja zakonczy sie jezeli wystapi problem z plikiem wejsciowym
		return false;
	else
	{
		file >> n;							// zmiennej n przypisana zostaje pierwsza wartosc w pliku tekstowym, informuje o liczbie wierzcholkow
		A = new int* [n];					// alokacja n komorek w tablicy
		for (int i = 0; i < n; i++)
		{
			A[i] = new int[n];				// alokacja n komorek w kazdej komorce tablicy, efekt macierzy nxn
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				file >> A[i][j];			// wypelnienie koljenych komorek macierzy kolejnymi wartosciami z pliku tekstowego
			}
		}
	}
	return true;
}

bool AdjacencyMatrix::show_matrix()			// metoda sluzaca do wyswietlania zawartosci macierzy
{
	if (n == 0)
		return false;						// jezeli liczba przechowujaca ilosc wierzcholkow rowna sie 0, funkcja sie zakonczy
	else
	{
		cout << "     ";
		for (int i = 1; i < n + 1; i++)		// gorny wiersz wypisujacy wierzcholki grafu
			printf("%5d", i);

		cout << endl;
		for (int i = 0; i < n; i++)
		{
			printf("%5d", i + 1);			// wypisanie wierzcholka
			for (int j = 0; j < n; j++)
			{
				printf("%5d", A[i][j]);		// wypisanie wartosci krawedzi idacych od wypisanego wczesniej wierzcholka do wierzcholkow w gornym wierszu
			}
			cout << endl;
		}

	}
	return true;
}

void AdjacencyMatrix::bruteForce(int v)					// algorytm Brute Force
{
	stackH->push(v);								// dodanie przeszukiwanego wierzcholka do stosu wierzcholkow odwiedzonych
	if (stackH->n == n)								// jezeli ilosc elementow na stosie przechowujacym wierzcholki odwiedzone jest rowny liczbie wszystkich wierzcholkow
	{												// to wejdz do ifa		
		dh = dh + A[v][0];
		if (dh < d)									// jezeli wartosc cyklu przeszukanej sciezki jest mniejsza od najmniejszej dotychczasowej sciezki
		{
			d = dh;									// przypisz nowa najmniejsza sciezke
			if (sciezka != NULL)					// usuwanie poprzedniej sciezki
			{
				delete[] sciezka;
				sciezka = NULL;
			}
			int pomoc = stackH->n;	
			sciezka = new int[pomoc];	
			for (int i = 0; i < pomoc; i++)
			{
				sciezka[i] = stackH->pop();					// kopiowanie stosu do tablicy reprezentujacej sciezke
			}
			for (int i = pomoc - 1; i >= 0; i--)
			{
				stackH->push(sciezka[i]);					//kopiowanie �cie�ki z powrotem na stos
			}
		}
		dh = dh - A[v][0];								
	}
	else													//je�eli stos nie zawiera wszystkich wierzcho�k�w to przechodzimy ni�ej
	{
		visited[v] = true;									// oznaczenie wierzcho�ka jako odwiedzony
		for (int j = 0; j < n; j++)							// przegl�damy wszystkich nieodwiedzonych s�siad�w wierzcho�ka, na rzecz kt�rego wywo�any by� algorytm
		{
			if (A[v][j] != -1)								
			{
				if (visited[j] == true)						
					continue;
				else
				{
					dh = dh + A[v][j];
					bruteForce(j);							//wywo�anie metody dla kolejnego(g��bszego) wierzcho�ka
					dh = dh - A[v][j];
				}
			}
		}
		visited[v] = false;
	}
	stackH->pop();											// zdj�cie wierzcho�ka ze stosu (ze �cie�ki)
}

void AdjacencyMatrix::showResult()                           //metoda s�u��ca do pokazywania rezultat�w
{
	cout << "Sciezka: ";
	for (int i = n - 1; i >= 0;i--)
		cout << sciezka[i] << "->";							//wypisanie �cie�ki
	cout << endl;
	cout << "Suma: " << d << endl;							//wypisanie kosztu
}

void AdjacencyMatrix::prepare()                     //metoda inicjaizuj�ca zmienne potrzebne do algorytmu przegl�du zupe�engo
{
	visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[n] = false;
	d = 2147483647;
	dh = 0;
}




int** AdjacencyMatrix::copy_matrix(int** C)           // metoda kopiuj�ca macierz
{
	int** D;							// nowy wska�nik na macierz
	D = new int* [n];					// alokacja n komorek w tablicy
	for (int i = 0; i < n; i++)
	{
		D[i] = new int[n];				// alokacja n komorek w kazdej komorce tablicy, efekt macierzy nxn
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			D[i][j] = C[i][j];			//kopiowanie element�w macierzy
		}
	}
	return D;
}

void AdjacencyMatrix::B_B(int v)                //implementacja algorytmu B&B
{
	A1 = copy_matrix(A);						//skopiowanie tablicy do 
	int min = 2147483647;
	int cost = 0;
	bool * visited = new bool[n];
	for (int i = 0; i < n; i++)					//inicjalizacja tablicy reprezentuj�cej odwieczone wierzcho�ki grafu
		visited[i] = false;

	//redukowanie wierszy
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) //szukanie minimum w ka�dym wierszu
		{
			if (A1[i][j] < min && i != j)
				min = A1[i][j];
		}
		for (int j = 0; j < n; j++) //redukcja wiersza
		{
			if(A1[i][j] != 0)
				A1[i][j] -= min;
		}
		cost += min;
		min = 2147483647;
	}
	//redukowanie kolumn
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(A1[j][i] < min && i != j)           //szukanie minimum w ka�dej kolumnie
				min = A1[j][i];
		}
		for (int j = 0; j < n; j++) //redukcja kolumny
		{
			if(A1[j][i] != 0)
				A1[j][i] -= min;
		}
		cost += min;
		min = 2147483647;
	}

	wezel* wezel1 = new wezel;				//alokacja i inicjalizacja korzenia w drzewie stan�w
	wezel1->B = A1;
	wezel1->sciezka = new int[1];
	wezel1->sciezka[0] = 0;
	wezel1->dlugosc = 1;
	wezel1->cost = cost;
	wezel1->parent = NULL;

	

	for (int i = 1; i < n; i++)
	{
		bound(wezel1, i);				//liczenie granicy dla wszystkich syn�w wierzcho�ka

	}
	
	wezel* aktualny = new wezel;
	while (!queue.empty())					//dop�ki kolejka przechowuje w�z�y
	{
		*aktualny = queue.top();
		queue.pop();							//pobieranie w�z�a o najmniejszej granicy
		if (aktualny->cost < upper)				//sprawdzenie czy jego granica jest mniejsza od najmniejszej ju� znalezionej
		{


			for (int i = 0; i < n; i++)
				visited[i] = false;

			for (int i = 0; i < aktualny->dlugosc; i++)
			{
				visited[aktualny->sciezka[i]] = true;			//okre�lenie, kt�re wierzcho�ki s� jeszcze do odwiedzenia
			}

			for (int i = 0; i < n; i++)							//dla ka�dego nieodwiedzonego s�siada przeszukiwanwgo wierzcho�ka -> tworzenie wszystkich syn�w wierzcho�ka
			{
				if (!visited[i])
				{
					bound(aktualny, i);							// wywo�anie metody licz�cej granice i tworz�cej w�ze� syna
					visited[i] = true;
				}
			}
		}
	}
	int dlugosc = 0;
	for (int i = 0; i < n-1; i++)
	{
		dlugosc += A[sciezka1[i]][sciezka1[i + 1]];				//policzenie kosztu znalezionej �cie�ki
	}
	dlugosc += A[sciezka1[n - 1]][0];
	cout << "dlugosc: " << dlugosc << endl;
	cout << "sciezka: ";
	for (int i = 0; i < n; i++)
		cout << sciezka1[i] << " -> ";							//wy�wietlenie znalezionej �cie�ki
	cout << endl;
	upper = 2147483647;
	delete[] sciezka1;											//zwolnienie pami�ci zaalokowanej w trakcie dzia�ania algorytmu
	delete aktualny;
	//delete test1;
	
}

void AdjacencyMatrix::bound(wezel* parent,int i)           //metoda tworz�ca w�ze� i licz�ca dla niego granice
{
	int min = 2147483647;
	wezel* syn = new wezel;									//alokacja pami�ci
	syn->parent = parent;
	syn->B = copy_matrix(parent->B);						//inicjalizacja odpowiednich p�l w�z�a
	int m = parent->dlugosc;
	syn->dlugosc = m + 1;
	int k = i;
	syn->sciezka = new int[m + 1];
	for (int j = 0; j < m; j++)
		syn->sciezka[j] = parent->sciezka[j];				//tworzenie �cie�ki doj�cia do danego w�z�a
	syn->sciezka[m] = i;
	syn->cost = 0;
	
	//redukowanie odpowiednich wierszy i kolumn
	for (int j = 0; j < n; j++)
	{
		syn->B[parent->sciezka[m-1]][j] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		syn->B[i][k] = -1;
	}
	syn->B[k][parent->sciezka[m-1]] = -1;


	//redukowanie wierszy
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) //szukanie minimum w ka�dym wierszu
		{
			if (syn->B[i][j] < min && i != j && syn->B[i][j] != -1)
				min = syn->B[i][j];										//znalezienie minimum w ka�dym wierszu
		}
		if (min != 2147483647)
		{
			for (int j = 0; j < n; j++) //redukcja wiersza
			{
				if (syn->B[i][j] != -1 && i != j) 
					syn->B[i][j] -= min;
			}
		}
		if (min != 2147483647)
			syn->cost += min;				//dodanie sum minim�w do warto�ci granicy
		min = 2147483647;
	}
	
	//redukowanie kolumn
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (syn->B[j][i] < min && i != j && syn->B[j][i] != -1)
				min = syn->B[j][i];										//znalezienie minimum w ka�dej kolumnie
		}
		if(min != 2147483647)
		{
			for (int j = 0; j < n; j++) //redukcja kolumny
			{
					if (syn->B[j][i] != -1 && i != j)    
						syn->B[j][i] -= min;
			}
		}
		if(min != 2147483647)
			syn->cost += min;				//dodanie sum minim�w do warto�ci granicy
		min = 2147483647;
	}
	
	
	syn->cost += A1[parent->sciezka[m - 1]][i] + parent->cost;  //obliczenie kosztu granicy dla w�z�a

	

	if (syn->dlugosc == n)					//sprawedzenie czy w�ze� nie jest li�ciem
	{
		if (syn->cost < upper)				//por�wnanie czy granica wierzcho�ka jest mnniejsza 
		{
			upper = syn->cost;				//podmiana najmnniejszej warto�ci granicy
			sciezka1 = syn->sciezka;		//podmiana �cie�ki dla najmniejszej granicy
			return;							//wyj�cie z metody
		}
	}
	queue.push(*syn);						//je�li w�ze� nie jest li�ciem, dodanie go do kolejki
	
}


