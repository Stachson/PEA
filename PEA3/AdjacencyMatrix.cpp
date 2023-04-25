#include "AdjacencyMatrix.h"




AdjacencyMatrix::AdjacencyMatrix()
{
	n = 0;
	srand(time(NULL));
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
		if (help == "(Ascheuer)")
		{
			file >> help;
		}
		file >> n;
		for (int i = 0; i < 5; i++)
			file >> help;
		A = new int* [n];
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

void AdjacencyMatrix::generate_population() // generowanie populacji pocz¹tkowej
{


	int wierzcholek;
	bool* odwiedzony;
	odwiedzony = new bool[n]; // tablica wygenerowanych wierzcholkow
	int dlugosc_nowego;;
	populacja_poczatkowa = new osobnik[wielkosc_populacji]; // tablica struktur przechowuj¹cych populacjê pocz¹tkow¹
	for (int j = 0; j < wielkosc_populacji; j++)    //ilosc wygenerowanych osobników
	{
		dlugosc_nowego = 0;
		populacja_poczatkowa[j].sciezka = new int[n]; // alokacja sciezki kazdego osobnika
		for (int i = 0; i < n; i++) // tablica wygenerowanych wierzcholkow
			odwiedzony[i] = false;
		//tworzenie pojedynczego osobnika
		populacja_poczatkowa[j].sciezka[0] = 0; // 0 jest wierzcholkiem poczatkowym dla kazdego osobnika
		odwiedzony[0] = true;
		for (int i = 1; i < n; i++)
		{
			do
			{
				wierzcholek = rand() % (n - 1) + 1; //wierzcholek od 0 do (n-1)
			} while (odwiedzony[wierzcholek] == true); // powtorz losowanie jesli wierzcholek jest juz uzyty
			
			odwiedzony[wierzcholek] = true;
			populacja_poczatkowa[j].sciezka[i] = wierzcholek; //dodanie wierzcholka do sciezki osobnika

		}
		for (int k = 0; k < (n - 1); k++)
		{
			dlugosc_nowego += A[populacja_poczatkowa[j].sciezka[k]][populacja_poczatkowa[j].sciezka[k + 1]]; //obliczanie dlugosci sciezki dla kazdego osobnika
		}
		dlugosc_nowego += A[populacja_poczatkowa[j].sciezka[n - 1]][0];
		populacja_poczatkowa[j].dlugosc = dlugosc_nowego;
		
	}
	
	delete[] odwiedzony; // zwolnienie pamiêci po tablicy odwiedzonych wierzcho³ków
}

void AdjacencyMatrix::selection() //selekcja osobników
{
	 // alokacja pamiêci na now¹ populacjê
	
	int k = 0.8 * wielkosc_populacji; //rozmiar turnieju
	wybrany = new bool[wielkosc_populacji]; //bool * wybrany
	for (int i = 0; i < wielkosc_populacji; i++)
		wybrany[i] = false;
	int* turniej = new int[k]; // tablica do przeprowadzania turniejów
	int rodzic;
	int min_dlugosc;
	// wybor k losowych osobnikow
	// wybor najlepszego jako rodzica
	// to samo
	// krzyzowanie i dodanie nowego osobnika do populacji
	// powtórzenie tyle razy ¿eby wysz³o wielkoscc_populacji osobnikow

	for (int i = 0; i < wielkosc_populacji; i = i + 2) //wielkosc_populacji razy stworzenie nowego osobnika
	{
		for (int j = 0; j < k; j++) //wybor 4 kandydatow do turnieju
		{
			do
			{
				rodzic = rand() % (wielkosc_populacji - 1);  
			} while (wybrany[rodzic] == true); //kazdy musi byc inny
			wybrany[rodzic] = true;
			turniej[j] = rodzic; //dodanie kandydata do turnieju
		}

		min_dlugosc = 2147483647;
		for (int j = 0; j < k; j++)
		{
			if (populacja_poczatkowa[turniej[j]].dlugosc < min_dlugosc)
			{
				min_dlugosc = populacja_poczatkowa[turniej[j]].dlugosc;   //wybranie najleszego z turnieju jako rodzica1
				rodzic1 = turniej[j];
			}
		}
		//wybór rodzica2 w ten sam sposób
		for (int i = 0; i < wielkosc_populacji; i++) //reset tabeli wybranych z wyj¹tkiem rodzica1
			wybrany[i] = false;
		wybrany[rodzic1] = true;

		for (int j = 0; j < k; j++) //wybor 4 kandydatow do turnieju
		{
			do
			{
				rodzic = rand() % (wielkosc_populacji - 1);
			} while (wybrany[rodzic] == true); //kazdy musi byc inny
			wybrany[rodzic] = true;
			turniej[j] = rodzic; //dodanie kandydata do turnieju
		}
		min_dlugosc = 2147483647;
		for (int j = 0; j < k; j++)
		{
			if (populacja_poczatkowa[turniej[j]].dlugosc < min_dlugosc)
			{
				min_dlugosc = populacja_poczatkowa[turniej[j]].dlugosc;   //wybranie najleszego z turnieju jako rodzica2
				rodzic2 = turniej[j];
			}
		}

		for (int i = 0; i < wielkosc_populacji; i++) //reset tabeli wybranych
			wybrany[i] = false;

		order_crossover(i); //wywo³anie krzy¿owania
	}
	delete[] turniej;
	delete[] wybrany;
}

void AdjacencyMatrix::order_crossover(int j)
{
	int pierwszy;
	int drugi;
	float czy_krzyzowanie = rand() % 101 * 0.01;
	
	if (czy_krzyzowanie > wspolczynnik_krzyzowania)      
	{
		for (int i = 0; i < n; i++)
			nowa_populacja[j].sciezka[i] = populacja_poczatkowa[rodzic1].sciezka[i];
		nowa_populacja[j].dlugosc = populacja_poczatkowa[rodzic1].dlugosc;

		for (int i = 0; i < n; i++)
			nowa_populacja[j + 1].sciezka[i] = populacja_poczatkowa[rodzic2].sciezka[i];
		nowa_populacja[j+1].dlugosc = populacja_poczatkowa[rodzic2].dlugosc;
		return;
	}
	

	odwiedzony = new bool[n];
	for (int i = 0; i < n; i++)
		odwiedzony[i] = false;
	int punkt_podzialu1 = rand() % (n - 2) + 2; //losowanie punktu podzialu
	int punkt_podzialu2;
	do
	{
		punkt_podzialu2 = rand() % (n - 2) + 2;
	} while (punkt_podzialu2 == punkt_podzialu1);

	if (punkt_podzialu1 < punkt_podzialu2)
	{
		pierwszy = punkt_podzialu1;
		drugi = punkt_podzialu2;
	}
	else
	{
		pierwszy = punkt_podzialu2;
		drugi = punkt_podzialu1;
	}

	nowa_populacja[j].sciezka[0] = 0;
	for (int i = pierwszy, k = 0; i < drugi; i++,k++)
	{
		nowa_populacja[j].sciezka[i] = populacja_poczatkowa[rodzic1].sciezka[i]; //kopiowanie segmentu z rodzica1
		odwiedzony[nowa_populacja[j].sciezka[i]] = true;
	} 
	//tablica na nieskopiowane elementy
	tablica2 = new int[n-1];
	//kopiowanie pozosta³ych elementów rodzica do tablicy od rodzica2
	int pozycja = 0;
	for (int i = drugi; i < n; i++, pozycja++)
	{
		tablica2[pozycja] = populacja_poczatkowa[rodzic2].sciezka[i];
	}
	for (int i = 1;i < drugi; i++,pozycja++) 
	{
		tablica2[pozycja] = populacja_poczatkowa[rodzic2].sciezka[i];
	}
	
	pozycja = drugi;
	int pozycja2 = 0;
	for (int i = 0; pozycja < n;i++, pozycja++,pozycja2++)
	{
		if (odwiedzony[tablica2[i]] == true)
		{
			pozycja--;
			continue;
		}
		else
		{
			nowa_populacja[j].sciezka[pozycja] = tablica2[i];
		}
	}
	
	pozycja = 1;

	for (int i = pozycja2; pozycja < pierwszy; i++)
	{
		if (odwiedzony[tablica2[i]] == true)
		{
			continue;
		}
		else
		{
			nowa_populacja[j].sciezka[pozycja] = tablica2[i];
			pozycja++;

		}
	}
	

	////////////////////// teraz to samo dla drugiego potomka
	
	for (int i = 0; i < n; i++)
		odwiedzony[i] = false;

	delete[] tablica2;
	 punkt_podzialu1 = rand() % (n - 2) + 2; //losowanie punktu podzialu
	do
	{
		punkt_podzialu2 = rand() % (n - 2) + 2;
	} while (punkt_podzialu2 == punkt_podzialu1);

	if (punkt_podzialu1 < punkt_podzialu2)
	{
		pierwszy = punkt_podzialu1;
		drugi = punkt_podzialu2;
	}
	else
	{
		pierwszy = punkt_podzialu2;
		drugi = punkt_podzialu1;
	}

	nowa_populacja[j + 1].sciezka[0] = 0;
	for (int i = pierwszy, k = 0; i < drugi; i++, k++)
	{
		nowa_populacja[j+1].sciezka[i] = populacja_poczatkowa[rodzic1].sciezka[i]; //kopiowanie segmentu z rodzica1
		odwiedzony[nowa_populacja[j+1].sciezka[i]] = true;
	}
	//tablica na nieskopiowane elementy
	tablica2 = new int[n-1];
	//kopiowanie pozosta³ych elementów rodzica do tablicy od rodzica2
	pozycja = 0;
	for (int i = drugi; i < n; i++, pozycja++)
	{
		tablica2[pozycja] = populacja_poczatkowa[rodzic2].sciezka[i];
	} 
	for (int i = 1; i < drugi; i++, pozycja++) // i < drugi
	{
		tablica2[pozycja] = populacja_poczatkowa[rodzic2].sciezka[i];
	}

	// teraz w tablicy2 znajduj¹ siê nieskopiowane elementy
	//dodawanie pozosta³ych elementów do potomka nie licz¹c tych ju¿ dodanych
	pozycja = drugi;
	pozycja2 = 0;
	for (int i = 0; pozycja < n; i++, pozycja++, pozycja2++)
	{
		if (odwiedzony[tablica2[i]] == true)
		{
			pozycja--;
			continue;
		}
		else
		{
			nowa_populacja[j+1].sciezka[pozycja] = tablica2[i];
		}
	}
	pozycja = 1;
	//i jest do poruszania siê po tablicy2 do kopiowania elementów
	for (int i = pozycja2; pozycja < pierwszy; i++)
	{
		if (odwiedzony[tablica2[i]] == true)
		{
			continue;
		}
		else
		{
			nowa_populacja[j+1].sciezka[pozycja] = tablica2[i];
			pozycja++;

		}
	}
	//obliczanie wartosci sciezki nowych osobnikow
	int dlugosc1 = 0;
	int dlugosc2 = 0;
	
	for (int i = 0; i < (n-1); i++)
	{
		dlugosc1 += A[nowa_populacja[j].sciezka[i]][nowa_populacja[j].sciezka[i + 1]];
		dlugosc2 += A[nowa_populacja[j+1].sciezka[i]][nowa_populacja[j+1].sciezka[i + 1]];
	}
	//cout << "Obliczanie sumy2" << endl;
	dlugosc1 += A[nowa_populacja[j].sciezka[n - 1]][0];
	nowa_populacja[j].dlugosc = dlugosc1;
	dlugosc2 += A[nowa_populacja[j+1].sciezka[n - 1]][0];
	nowa_populacja[j+1].dlugosc = dlugosc2;
	

	delete[] odwiedzony;
	delete[] tablica2;
}

void AdjacencyMatrix::mutation() //zamiana dwóch losowych miast ze sob¹ w œcie¿ce
{
	float czy_mutacja = rand() % 1001 * 0.001;
	int pozycja1;
	int pozycja2;
	if (czy_mutacja < wspolczynnik_mutacji)
	{
		pozycja1 = rand() % (n - 2) +2;
		do
		{
			pozycja2 = rand() % (n - 2) +2;
		} while (pozycja2 == pozycja1);
		int losowy_osobnik = rand() % (wielkosc_populacji - 1);
		int pomoc = nowa_populacja[losowy_osobnik].sciezka[pozycja1];
		nowa_populacja[losowy_osobnik].sciezka[pozycja1] = nowa_populacja[losowy_osobnik].sciezka[pozycja2];
		nowa_populacja[losowy_osobnik].sciezka[pozycja2] = pomoc;
		int dlugosc = 0;
		for (int i = 0; i < (n - 1); i++)
		{
			dlugosc += A[nowa_populacja[losowy_osobnik].sciezka[i]][nowa_populacja[losowy_osobnik].sciezka[i + 1]];
		}
		dlugosc += A[nowa_populacja[losowy_osobnik].sciezka[n - 1]][nowa_populacja[losowy_osobnik].sciezka[0]];
		nowa_populacja[losowy_osobnik].dlugosc = dlugosc;

	}
}

void AdjacencyMatrix::change_population()
{
	for (int i = 0; i < wielkosc_populacji; i++)
	{
		populacja_poczatkowa[i].dlugosc = nowa_populacja[i].dlugosc;
		for (int j = 0; j < n; j++)
			populacja_poczatkowa[i].sciezka[j] = nowa_populacja[i].sciezka[j];
	}

}

void AdjacencyMatrix::genetic_algorithm()
{
	nowa_populacja = new osobnik[wielkosc_populacji];
	for (int i = 0; i < wielkosc_populacji; i++)
		nowa_populacja[i].sciezka = new int[n];

	sciezka = new int[n];
	min = 2147483647;
	double czas = 10000000000; //10 sekundy
	StartCounter();
	generate_population();
	while (GetCounter() < kryterium_stopu)
	{
			selection(); // i krzyzowanie
			mutation();
			change_population();
			for (int i = 0; i < wielkosc_populacji; i++)
			{
				if (populacja_poczatkowa[i].dlugosc < min)
				{
					min = populacja_poczatkowa[i].dlugosc;
					for (int j = 0; j < n; j++)
					{
						sciezka[j] = populacja_poczatkowa[i].sciezka[j];
					}
				}
			}
			//cout << min << endl;
			if (GetCounter() > czas)
			{
				cout << "czas: " << czas/1000000000 << ", min: " << min << endl;
				czas += 10000000000; // wyœwietlanie co 10 sekund
			}
		
	}
	cout << "Zakonczono chyba z sukcesem" << endl;
	cout << "Najlepsza znaleziona dlugosc: " << min << endl;
	cout << "Najkrotsza sciezka:" << endl;
	for (int i = 0; i < n; i++)
		cout << sciezka[i]<<" ";	
}

//druga mutacja na potem

/*
	do
	{
		punkt_podzialu2 = rand() % (n - 2) + 2; //losowanie drugiego punktu podzialu
	} while (punkt_podzialu2 == punkt_podzialu1);
	if (punkt_podzialu1 < punkt_podzialu2)
	{
		pierwszy = punkt_podzialu1;
		drugi = punkt_podzialu2;
	}
	else
	{
		pierwszy = punkt_podzialu2;
		drugi = punkt_podzialu1;
	}

	int* tablica = new int[drugi - pierwszy];
	for (int i = pierwszy,j = 0; i < drugi; i++,j++)
	{
		tablica[j] = populacja_poczatkowa
	}

*/



