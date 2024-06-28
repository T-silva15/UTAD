#include "Data.h"

Data::Data(){
}


Data::Data(int d, int m, int a)	{
	this->dia = d;
	this->mes = m;
	this->ano = a;		
}

Data::Show(){
	cout << "Data: " << dia << "/" << mes << "/" << ano ;
}

Data::Update(){
	int temp;
	
	cout << "----------- Atualizar data -----------" << endl;
	
	cout << "Introduza o dia:" << endl;
	cin >> temp;
	this->setDia(temp);
	
	cout << "Introduza o mes:" << endl;
	cin >> temp;
	this->setMes(temp);
	
		cout << "Introduza o ano:" << endl;
	cin >> temp;
	this->setAno(temp);	
}

Data::Igual(Data d1){
	
	if (d1.ano != this->ano || d1.mes != this->mes || d1.dia != this->dia){
			return(false);
	} else {
			return(true);
	}	

}


Data::operator==(Data d1){
	
	if (d1.ano != this->ano || d1.mes != this->mes || d1.dia != this->dia){
			return(false);
	} else {
			return(true);
	}
}

Data::operator!=(Data d1){
	
	if(d1.dia == this->dia)
		return false;
		
	if(d1.mes == this->mes)
		return false;
		
	if(d1.ano == this->ano)
		return false;
		
	return true;	

}



ostream & operator << (ostream &os,  Data data)
{
	os << data.getDia() << "/" << data.mes << "/" << data.ano ;

	return os;
}

istream & operator >> (istream &is, Data &data)
{	int aux;

	cout << "Dia: ";
	is >> aux;
	data.setDia(aux);
	cout << "Mês: ";
	is >> aux;
	data.setMes(aux);
	cout << "Ano: ";
	is >> aux;
	data.setAno(aux);

	return is;
}

void Data::SaveFile(ofstream& os)
{
	os << "Data: "<< getDia() << "/" << getMes() << "/" << getAno() << "\n";
}

void Data::ReadFile(ifstream& is)
{	
	string line;
 	while(getline(is, line)) {
 	
    cout << line << endl;
   };
}

bool Data::operator < (const Data data) const
{
	if (data.ano < ano)
		return(false);
	else	if (data.ano == ano && data.mes < mes)
		return(false);
	else	if (data.ano == ano && data.mes == mes && data.dia < dia)
		return(false);
	return(true);
}

bool Data::operator >(const Data data) const
{
	if (data.ano > ano)
		return(false);
	else	if (data.ano == ano && data.mes > mes)
		return(false);
	else	if (data.ano == ano && data.mes == mes && data.dia > dia)
		return(false);
	return(true);
}
