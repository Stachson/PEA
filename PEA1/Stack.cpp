#include "Stack.h"

//Klasa reprezentujaca stos wykorzystywany w algorytmie Brute Force

Stack::Stack()		// konstruktor, ustawia liczbe elementow na 0
{
	n = 0;
}

void Stack::push(int newValue)		//odlozenie na stos
{
	number* newNumber = new number;	//alokacja nowej struktury przechowujacej wartosc oraz adres kolejnego elementu
	newNumber->value = newValue;	//przypisanie nowemu elementowi wartosci przekazanej w parametrze

	if (n == 0)
	{
		top = newNumber;			// jezeli stos jest pusty nowy elment staje sie zarowno poczatkiem jak i koncem stosu
		bottom = newNumber;			//poczatek - element najglebiej stosu
		top->next = NULL;			// koniec - element na szczycie stosu
		bottom->next = NULL;
		n++;						// zwiekszenie ilosci przechowywanych elementow
	}
	else
	{
		if (n == 1)					// dodanie elementu na stos w przypadku gdy stos ma 1 element
		{
			top->next = newNumber;
			top = newNumber;
			bottom->next = top;		//koniec jest bezposrednio nad poczatkiem w stosie
			top->next = NULL;
			n++;					// zwiekszenie ilosci przechowywanych elementow
		}
		else
		{
			top->next = newNumber;	// dodanie elementu na stis w przypadku gdy stos ma wiecej niz 1 element
			top = newNumber;
			top->next = NULL;		// ustawienie nowego konca
			n++;
		}
	}
}

int Stack::pop()		// zdjecie elementu ze stosu
{
	if (n == 0)			
	{
		return -1;		// jezeli stos jest pusty, zwracana jest wartosc -1, ktora nam to sygnalizuje
	}
	else
	{
		if (n == 1)		// zdejmowanie ze stosu jezeli jest na nim 1 element
		{
			int help = top->value;
			number* nowy = top;
			delete nowy;
			bottom = NULL;
			top = NULL;

			n--;
			return help;
		}
		else
		{
			number* nowy;
			nowy = bottom;
			while (nowy->next->next)
			{
				nowy = nowy->next;
			}
			int returnValue = nowy->next->value;
			top = nowy;
			delete nowy->next; // zamieeniona kokejnosc
			top->next = NULL;
			
			n--;
			return returnValue;

		}

	}
}

