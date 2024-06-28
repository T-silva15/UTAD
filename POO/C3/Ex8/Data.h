#pragma once
#include<iostream>
#include<fstream>

using namespace std; 

class Data{
	
	
	private:
	    int ano;
	    int dia;
	    int mes;

	public:
	    // Setters    
	    inline void setDia(int d) {
	        dia = d;    
	    }
	    
	    inline void setMes(int m) {
	        mes = m;    
	    }
	    
	   inline void setAno(int a) {
	        ano =a;    
	    }
	    
	    // Getters
	   inline int getDia() {
	      return dia;
	    }
	    
	    inline int getMes() {
	      return mes;
	    }
	    
	    inline int getAno() {
	      return ano;
	    }
    
    public:
    	Data();
    	Data(int a, int d, int m);
    	Show();
    	Update();
    	Igual(Data d1);
    	operator==(Data d1);
    	operator!=(Data d1);
    		
    	friend ostream & operator << (ostream &os, Data data);
		friend istream & operator >> (istream &is, Data &data);
	
		void SaveFile(ofstream& os);
		void ReadFile(ifstream& is);
		
		bool operator < (const Data data) const;
		bool operator > (const Data data) const;
};


