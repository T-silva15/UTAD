#pragma once
#include "Pessoa.h"
#include <string>

class Funcionario : public Pessoa {
	private:
		string setor;
		int num;
		
		float ord_base;
		int h_extra;
		float p_horas_extra;
		
		
	public:
		Funcionario();
		virtual ~Funcionario();
		Funcionario(int _num, string _setor, string _nome, string _morada, Data _data, float _ord_base, int _hextra, float _p_horas_extra);
		
		void SetNum(int _num) { 
			num = _num; 
		}
		
		void SetSetor(string _setor) { 
			setor = _setor; 
		}
		
		int GetNum(void) { 
			return num; 
		}
		
		string GetSetor(void) { 
			return setor; 
		}	
		
		void Show(void);
		
		friend istream & operator >> (istream &is, Funcionario &F);
		
		void SaveFile(ofstream &os);
		void ReadFile(ifstream &is);
		void ReadLine(ifstream &is);
		
		virtual float Calcula_Ordenado() = 0;
		void ReadK(void);
		
		float GetOrdBase() { 
			return ord_base; 
		}
		
		void SetOrdBase(float _ord) { 
			ord_base = _ord; 
		}
		
		float GetPrecoHorasExtra() { 
		return p_horas_extra; 
		}
		void SetPrecoHorasExtra(float _ph) { 
		p_horas_extra = _ph; 
		}
		
		int GetHorasExtra() { 
			return h_extra; 
		}
		
		void SetHorasExtra(int _h) {
		 	h_extra = _h; 
		}
};

