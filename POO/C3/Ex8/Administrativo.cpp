#include "Administrativo.h"


Administrativo::Administrativo(int _num, string _setor, string _nome, string _morada, Data _data, float _ord, int _hextra)
	: Funcionario(_num, _setor, _nome, _morada, _data, _ord,  _hextra, 10)
{
	SetPrecoHorasExtra(10);
}

Administrativo::Administrativo(): Funcionario()
{
	SetPrecoHorasExtra(10);
}

float Administrativo::Calcula_Ordenado()
{
	return GetOrdBase() + GetHorasExtra() * GetPrecoHorasExtra();
}

void Administrativo::ReadLine(ifstream & is)
{
	string aux;
	Funcionario::ReadFile(is);
	getline(is, aux, '\n');
	cout << endl;
}

