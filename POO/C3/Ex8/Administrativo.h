#pragma once
#include "Funcionario.h"
class Administrativo :public Funcionario
{
	public:
		Administrativo(int _num, string _setor, string _nome, string _morada, Data _data, float _ord, int _hextra);
		Administrativo();
		
		float Calcula_Ordenado();
		void ReadLine(ifstream & is);
		
		
};


