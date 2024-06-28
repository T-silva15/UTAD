#include "Funcionario.h"
#include <iostream>
#include <stdlib.h>
Funcionario::Funcionario()
{
}

Funcionario::~Funcionario()
{
}

Funcionario::Funcionario(int _num, string _setor, string _nome, string _morada, Data _data, float _ord_base, int _hextra, float _p_horas_extra) :Pessoa(_nome, _morada, _data)
{
	setor = _setor;
	num = _num;
	
	ord_base = _ord_base;
	h_extra = _hextra;
	p_horas_extra = _p_horas_extra;
}

void Funcionario::Show(void)
{
	Pessoa::Show();
	cout << "Num:" << num << ";Setor:" << setor << "\n";
}



istream & operator >> (istream &is, Funcionario &F)
{
	char aux[100];

	is >> (Pessoa &)F;
	cout << "Num:";
	is >> F.num;
	cout << "Setor:";
	is >> aux;
	F.setor = aux;

	return is;
}

void Funcionario::SaveFile(ofstream &os)
{
	Pessoa::SaveFile(os);
	os << num << ";" << setor << ";";
}

void Funcionario::ReadFile(ifstream &is)
{
	char aux[100];
	string t;

	Pessoa::ReadFile(is);
	is.getline(aux, 100, ';');
	num = atoi(aux);
	is.getline(aux, 100, ';');
	setor = aux;
	is.getline(aux, 100, ';');
	ord_base = atoi(aux);
	
	
	is.getline(aux, 100, ';');
	p_horas_extra = atoi(aux);
	/*getline(is, t, '\n');
	
	cout << endl; */
}

void Funcionario::ReadLine(ifstream &is)
{
	char aux[100];

	Pessoa::ReadFile(is);
	is.getline(aux, 100, ';');
	num = atoi(aux);
	is.getline(aux, 100, ';');
	setor = aux;
	is.getline(aux, 100, ';');
	ord_base = atoi(aux);
	
	
	is.getline(aux, 100, ';');
	p_horas_extra = atoi(aux);
	
	cout << endl;
	

}

void Funcionario::ReadK(void)
{
	Pessoa::ReadK();
	cout << "Num:";
	cin >> num;
	cout << "Setor:";
	cin >> setor;

	//extra 
	cout << "Ord Base:";
	cin >> ord_base;

	cout << "Horas Extras";
	cin >> h_extra;
	
	cin.clear();
	fflush(stdin);
}


