#include "game_of_life.h"
#include <ctime>
#include <algorithm>
bool game_of_life::slucajna_vrijednost()
{
	return rand() % (100 - 1 + 1) + 1 <= 25 ? true : false;
}

game_of_life::game_of_life()
{
	srand(time(nullptr));
	for (unsigned i = 0; i < 20; i++)
	{
		for (unsigned j = 0; j < 40; j++)
		{
			_generacija[i][j] = slucajna_vrijednost();
			_sljedeca_generacija[i][j] = false;
		}
	}
}

void game_of_life::sljedeca_generacija()
{
	initValues();
	copy(&_sljedeca_generacija[0][0], &_sljedeca_generacija[0][0] + 20 * 40, &_generacija[0][0]);
}

void game_of_life::initValues()
{
	int susjedCounter = 0;
	for (unsigned i = 0; i < 20; i++)
		for (unsigned j = 0; j < 40; j++)
		{
			susjedCounter = _susjedCounter(i, j);
			setValuesInNextGeneration(susjedCounter, i, j);
		}		
}

int game_of_life::_susjedCounter(int i, int j)
{
	int susjedCounter = 0;
	if (i == 0 && j == 0)		//Gornji Lijevi Kut
	{
		if (_generacija[i][j + 1])
			susjedCounter++;
		if (_generacija[i + 1][j])
			susjedCounter++;
		if (_generacija[i + 1][j + 1])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i == 0 && j == 39)			//Gornji Desni Kut
	{
		if (_generacija[i][j - 1])
			susjedCounter++;
		if (_generacija[i + 1][j - 1])
			susjedCounter++;
		if (_generacija[i + 1][j])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i == 19 && j == 0)			//Donji Lijevi Kut
	{
		if (_generacija[i][j + 1])
			susjedCounter++;
		if (_generacija[i - 1][j + 1])
			susjedCounter++;
		if (_generacija[i - 1][j])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i == 19 && j == 39)		//Donji Desni Kut
	{
		if (_generacija[i][j - 1])
			susjedCounter++;
		if (_generacija[i - 1][j - 1])
			susjedCounter++;
		if (_generacija[i - 1][j])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i == 0 && j >= 1 && j <= 38)		//Gornja Prva Linija
	{
		if (_generacija[i][j - 1])
			susjedCounter++;
		if (_generacija[i + 1][j - 1])
			susjedCounter++;
		if (_generacija[i + 1][j])
			susjedCounter++;
		if (_generacija[i + 1][j + 1])
			susjedCounter++;
		if (_generacija[i][j + 1])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i == 19 && j >= 1 && j <= 38)		//Donja Zadnja Linija
	{
		if (_generacija[i][j - 1])
			susjedCounter++;
		if (_generacija[i - 1][j - 1])
			susjedCounter++;
		if (_generacija[i - 1][j])
			susjedCounter++;
		if (_generacija[i - 1][j + 1])
			susjedCounter++;
		if (_generacija[i][j + 1])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i >= 1 && i <= 18 && j == 0)		// Lijeva Prva Linija
	{
		if (_generacija[i - 1][j])
			susjedCounter++;
		if (_generacija[i - 1][j + 1])
			susjedCounter++;
		if (_generacija[i][j + 1])
			susjedCounter++;
		if (_generacija[i + 1][j + 1])
			susjedCounter++;
		if (_generacija[i + 1][j])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i >= 1 && i <= 18 && j == 39)		//Desna Zadnja Linija
	{
		if (_generacija[i - 1][j])
			susjedCounter++;
		if (_generacija[i - 1][j - 1])
			susjedCounter++;
		if (_generacija[i][j - 1])
			susjedCounter++;
		if (_generacija[i + 1][j - 1])
			susjedCounter++;
		if (_generacija[i + 1][j])
			susjedCounter++;
		return susjedCounter;
	}
	else if (i >= 1 && i <= 18 && j >= 1 && j <= 38)		//Sve Ostalo u Sredini
	{
		if (_generacija[i][j - 1])
			susjedCounter++;
		if (_generacija[i - 1][j - 1])
			susjedCounter++;
		if (_generacija[i - 1][j])
			susjedCounter++;
		if (_generacija[i - 1][j + 1])
			susjedCounter++;
		if (_generacija[i][j + 1])
			susjedCounter++;
		if (_generacija[i + 1][j + 1])
			susjedCounter++;
		if (_generacija[i + 1][j])
			susjedCounter++;
		if (_generacija[i + 1][j - 1])
			susjedCounter++;
		return susjedCounter;
	}
}

void game_of_life::setValuesInNextGeneration(int susjedCounter, int i, int j)
{
	if (_generacija[i][j])
	{
		if (susjedCounter == 2 || susjedCounter == 3)
			_sljedeca_generacija[i][j] = true;
		else if (susjedCounter < 2 || susjedCounter > 3)
			_sljedeca_generacija[i][j] = false;
	}
	else
	{
		if (susjedCounter == 3)
			_sljedeca_generacija[i][j] = true;
	}
}

void game_of_life::iscrtaj()
{
	for (unsigned i = 0; i < 20; i++)
	{
		for (unsigned j = 0; j < 40; j++)
		{
			if (_generacija[i][j])
				cout << "*";
			else
				cout << "-";
		}		
		cout << endl;
	}
}
