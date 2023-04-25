#include "AdjacencyMatrix.h"


AdjacencyMatrix::AdjacencyMatrix()
{
	n = 0;
	//stack = new Stack();
	srand(time(NULL));
	
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	if (sciezka1 != NULL)
	{
		delete[] sciezka1;
	}
	if (n != 0)
	{
		for (int i = 0; i < n; i++)
			delete A[i];
		delete[] A;
	}
}

void AdjacencyMatrix::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!" << endl;

	PCFreq = double(li.QuadPart) / 1000000000.0;   //nanosekundy

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double AdjacencyMatrix::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

bool AdjacencyMatrix::load_matrix(string fileName)
{
	if (n != 0)
	{
		for (int i = 0; i < n; i++)
			delete A[i];
		delete[] A;
	}
	else
	{
		fstream file;
		file.open(fileName.c_str(), ios::in);

		if (file.good() == false)
			return false;
		
		string help;
		for (int i = 0; i < 9; i++)
			file >> help;
		//cout << help << endl;
		if (help == "(Ascheuer)")
		{
			file >> help;
		}
		file >> n;
		for (int i = 0; i < 5; i++)
			file >> help;
		A = new long int* [n];
		for (int i = 0; i < n; i++)
		{
			A[i] = new long int[n];				// alokacja n komorek w kazdej komorce tablicy, efekt macierzy nxn
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				file >> A[i][j];			// wypelnienie koljenych komorek macierzy kolejnymi wartosciami z pliku tekstowego
			}
		}

	}
	//cout << "Rozmiar pliku: " << n << endl;
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

void AdjacencyMatrix::algorytm_zachalnny()    //za kazdym razem szukamy najblizszego sasiada
{
	//cout << "Wejscie do zachlannego" << endl;
	
	sciezka1 = new int[n];
	int v = 0;
	int wierzcholek;
	int min = 2147483647;
	int suma = 0;
	suma1 = 0;
	bool* odwiedzone;
	int* sciezka;
	sciezka = new int[n];
	sciezka[0] = 0;
	int ilosc = 1;
	int indeks = 1;
	odwiedzone = new bool[n];
	
	for (int i = 0; i < n; i++)
		odwiedzone[i] = false;
	while (ilosc != n)						// wierzcholkiem pocz¹tkowym jest 0
	{
		for (int i = 1; i < n; i++)
		{
			if (A[v][i] < min && odwiedzone[i] == false && v != i)
			{
				min = A[v][i];
				wierzcholek = i;
			}
		}
		odwiedzone[wierzcholek] = true;
		suma += A[v][wierzcholek];
		sciezka[indeks] = wierzcholek;
		indeks++;
		ilosc++;
		min = 2147483647;
		v = wierzcholek;
	}
	suma += A[v][0];
	for (int i = 0; i < n; i++)
	{
		sciezka1[i] = sciezka[i];
	}
	suma1 = suma;
	delete[] sciezka;
	delete[] odwiedzone;
}

void AdjacencyMatrix::symulowane_wyzarzanie()
{
	//sciezka1, to najlepsze mozliwe rozwi¹zanie
	xo = new int[n];  //alokacja tablic pomocniczych do przechowywania œcie¿ek
	x = new int[n];  
	int v1;		//pierwszy wierzcholek do zamiany
	int v2;		//drugi wierzcho³ek do zamiany
	for (int i = 0; i < n; i++) //skopiowanie do tablic pomocniczych aktualnie najlepszej sciezki
	{
		xo[i] = sciezka1[i];
		x[i] = sciezka1[i];
	}
	sumaxo = suma1;
	sumax = 0;

	//czêœæ odpowiedzialna za wyznaczenie temperatury pocz¹tkowej
	int* pomocx;
	pomocx = new int[n];
	int suma_pomocxo = suma1;
	int suma_pomocx = 0;
	int srednia = 0;

	for (int i = 0; i < n; i++)
		pomocx[i] = sciezka1[i];

	for (int i = 0; i < 100; i++)
	{
		v1 = rand() % (n - 1) + 1; //wybierz w sposób losowy 
		do
		{
			v2 = rand() % (n - 1) + 1;
		} while (v1 == v2);

		swap(pomocx[v1], pomocx[v2]);      //f(i) satre rozwiazanie   f(j) nowe rozwiazanie
		//obliczenie sciezki
		for (int i = 0; i < n - 1; i++)
		{
			suma_pomocx += A[pomocx[i]][pomocx[i + 1]];
		}
		srednia += (suma_pomocxo - suma_pomocx);
		suma_pomocx = 0;
		swap(pomocx[v1], pomocx[v2]);
	}
	srednia = srednia / 100;
	T = (srednia / log(0.98));
	cout << "temperatura poczatkowa: " << T << endl;
	delete[] pomocx;
	
	double czas = 10000000000;
	StartCounter();
	while (GetCounter()  < kryterium_stopu) // warunek zatrzymaniaw
	{
		//if (GetCounter() > czas)
		//{
			//cout << "czas: " << czas << ", rozwiazanie: " << suma1 << endl;
			//czas = czas + 10000000000;
		//}
		v1 = rand() % (n-1) + 1; //wybierz w sposób losowy 
		do
		{
			v2 = rand() % (n-1) + 1;
		} while (v1 == v2);
		swap(x[v1], x[v2]);
		for (int i = 0; i < (n - 1); i++)
		{
			sumax += A[x[i]][x[i + 1]];           
		}
		sumax += A[x[n - 1]][0]; //dlugosc nowego rozwiazania 
		if (rand() % 101 * 0.01 < probability())
		{
			sumaxo = sumax;
			for (int i = 0; i < n; i++)
				xo[i] = x[i];
			if (sumaxo < suma1)
			{
				suma1 = sumaxo;
				for (int i = 0; i < n; i++)
				{
					sciezka1[i] = xo[i];
				}
			}
		}
		T = T * a;
		sumax = 0;
		for (int i = 0; i < n; i++)
			x[i] = xo[i];
	}
	delete[] xo;
	delete[] x;
	sumaxo = 0;
	cout << "Temperatura koñcowa: " << T << endl;
	cout << "Suma: " << suma1 << endl;
	cout << "Sciezka: ";
	for (int i = 0; i < n; i++)
		cout << sciezka1[i] << " -> ";
	cout << endl;
	delete[] sciezka1;
}

double AdjacencyMatrix::probability()
{
	double p;
	p = exp(-((double)((sumax - sumaxo) / T)));
	if (p < (double)1)
	{
		return p;
	}
	return 1;

}
