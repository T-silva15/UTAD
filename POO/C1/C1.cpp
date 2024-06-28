#include <fstream>
#include <iostream>
// using namespace std to avoid having to specify it later 
using namespace std;

class Data {

private:
    int dia;
    int mes;
    int ano;

public:
    // standard constructor (no parameters given)
    Data() {
        dia = 1;
        mes = 1;
        ano = 2000;
    }

    // construtor user defined parameters
    Data(int d, int m, int a) {
        setDia(d);
        setMes(m);
        setAno(a);
    }
    // virtual destructor (~)
    virtual ~Data(){}

    // inline get and set functions for the day
    int getDia() { return dia; }
    void setDia(int d) { dia = d; }

    // inline get and set functions for the month
    int getMes() { return mes; }
    void setMes(int m) { mes = m; }

    // inline get and set functions for the year
    int getAno() { return ano; }
    void setAno(int a) { ano = a; }
    
    // shows every value within a Data object in date form (d/m/a)
    virtual void show(){ 
        cout << dia << "/" << mes << "/" << ano << endl; 
        }

    // updates Data object using parameters specified by the caller)
    virtual void update(int d, int m, int a){
        setDia(d);
        setMes(m);
        setAno(a); 
    }

    // updates Data objects using direct user input
    virtual void updateIO(){
        int d, a, m;
        cout << "Introduza o novo dia: " << endl;
        cin >> d;
        cout << "Introduza o novo mes: " << endl;
        cin >> m;
        cout << "Introduza o novo ano: " << endl;
        cin >> a;
        setDia(d);
        setMes(m);
        setAno(a);
    }

    // checks if two Data objects are equal (having exactly the same values)
    bool igual(Data data2){
        if (getDia() == data2.getDia() && getMes() == data2.getMes() && getAno() == data2.getAno()){
            cout << "Os objetos sao iguais!" << endl;
            return true;
        }
        cout << "Os objetos sao diferentes!" << endl;
        return false;
    }   

    
    bool operator > (Data data2) {
        if (ano > data2.ano) {
            cout << "O primeiro objeto e mais recente!" << endl;
            return true;
        } else if (ano < data2.ano) {
            cout << "O segundo objeto e mais recente!" << endl;
            return false;
        } else if (mes > data2.mes) {
            cout << "O primeiro objeto e mais recente!" << endl;
            return true;
        } else if (mes < data2.mes) {
            cout << "O segundo objeto e mais recente!" << endl;
            return false;
        } else if (dia > data2.dia) {
            cout << "O primeiro objeto e mais recente!" << endl;
            return true;
        } else if (dia < data2.dia) {
            cout << "O segundo objeto e mais recente!" << endl;
            return false;
        } else {
            cout << "Os objetos têm a mesma data!" << endl;
            return false;
        }
    }

    // overloads == operator to allow for object comparing
    bool operator == (Data data2){
        return (dia == data2.dia) && (mes == data2.mes) && (ano == data2.ano);
    }

    // overloads != operator to allow for object comparing
    bool operator != (Data data2){
        return (dia != data2.dia) && (mes != data2.mes) && (ano != data2.ano);
    }

    // overloads << operator to allow for object output
    friend void operator << (ostream&  output, Data data){
        output << data.dia << "/" << data.mes << "/" << data.ano << endl;
    }

    // overloads >> operator to allow for a simpler object input
    friend void operator >> (istream& input, Data data){ 
        int d, m, a;
       
        //day input 
        cout << "Introduza o dia: ";
        input >> d;
        data.setDia(d);
        
        //month input
        cout << "Introduza o mes: ";
        input >> m;
        data.setMes(m);
        
        //year input
        cout << "Introduza o ano: ";
        input >> a;
        data.setAno(a);
    }

    void ReadFile(ifstream& is)
    {	char input[10];
        
        is.getline(input, 10, '/');
        dia = atoi(input);
        is.getline(input, 10, '/');
        mes = atoi(input);
        is.getline(input, 10, ';');
        ano = atoi(input);
    };

    void SaveFile(ofstream& os){

        os << getDia() << "/" << getMes() << "/" <<getAno() << ";";
    }

};

class Pessoa {
private:
    string nome;
    Data data;
    string morada;
public:
    // standard constructor (no parameters given)     
    Pessoa() {
        nome = "N/A";
        morada = "N/A";
    }
    // construtor user defined parameters
    Pessoa(string n, Data _data, string mor){
        nome = n;
        morada = mor;
        data = _data;
    }   

    // virtual destructor (~)  
    virtual ~Pessoa(){}

    // inline get and set functions for the name
    string getNome() { return nome; }
    void setNome(string n) { nome = n; }

    // inline get and set functions for the address
    string getMorada() { return morada; }
    void setMorada(string mor) { morada = mor; }

    // get and set functions for the date
    string getData() { 
        string d = to_string(data.getDia()); 
        string m = to_string(data.getMes()); 
        string a = to_string(data.getAno());

        string data = d + "/" + m + "/" + a;

        return data;
    }
    void setData(Data(_data)) { 
        data = _data;
    }

    // shows every value within a Pessoa object in date form (d/m/a)
    void show(){
        cout << "Nome: " << nome << endl;
        cout << "Data de nascimento: " << getData() << endl;
        cout << "Morada: " << morada << endl;
    }

    // updates Pessoa object using parameters input by the caller)
    void ReadK(){
        cout << "Introduza o novo nome: " << endl;
        cin >> nome;
        data.updateIO();
        cout << "Introduza a nova morada: " << endl;
        cin >> morada;
    }
    
    // overloads << operator to allow for object input
    friend void operator >> (istream& input, Pessoa& p) {
        int d, m, a;
        string n, mor;
       
        //name input
        cout << "Introduza o nome: ";
        input >> n;
        p.setNome(n);

        //day input 
        cout << "Introduza o dia: ";
        input >> d;
        p.data.setDia(d);
        
        //month input
        cout << "Introduza o mes: ";
        input >> m;
        p.data.setMes(m);
        
        //year input
        cout << "Introduza o ano: ";
        input >> a;
        p.data.setAno(a);

        //adress input
        cout << "Introduza a morada: ";
        input >> mor;
        p.setMorada(mor);
    }

    // overloads << operator to allow for object output
    friend void operator << (ostream& output, Pessoa p){

        string d = p.getData();

        output << p.nome << endl << d << endl << p.morada << endl;
    } 

    // overloads != operator to allow for object comparing
    bool operator != (Pessoa p2){

        string data1 = getData();
        string data2 = p2.getData();

        return (nome != p2.nome) && (morada != p2.morada) && (data1 != data2);  
    }

    // overloads == operator to allow for object comparing
    bool operator == (Pessoa p2){

        string data1 = getData();
        string data2 = p2.getData();

        return (nome == p2.nome) && (morada == p2.morada) && (data1 == data2);  
    }

    // method that checks which of the objects is older(date comparing)
    void MaisNovo (Pessoa p2){
        int d1 = data.getDia();
        int m1 = data.getMes();
        int a1 = data.getAno();

        int d2 = p2.data.getDia();
        int m2 = p2.data.getMes();
        int a2 = p2.data.getAno();

        if (a2 < a1){
            cout << "A pessoa mais nova e: " << getNome() << endl;
        } else if (a2 > a1){
            cout << "A pessoa mais nova e: " << p2.getNome() << endl;
        } else if (m2 < m1){
            cout << "A pessoa mais nova e: " << getNome() << endl;
        } else if (m2 > m1){
            cout << "A pessoa mais nova e: " << p2.getNome() << endl;
        } else if (d2 < d1){
            cout << "A pessoa mais nova e: " << getNome() << endl;
        } else if (d2 > d1){
            cout << "A pessoa mais nova e: " << p2.getNome() << endl;
        } else {
            cout << "As pessoas tem a mesma idade!" << endl;
        }
    }

    // stores data from the object in a file
    void SaveFile(ofstream& output){

        output << getNome() << ";" << data.getDia() << ";" << data.getMes() << ";" << data.getAno() << ";" << getMorada() << endl;
    }

    // reads data from a file and stores it in the object
    void ReadFile(ifstream& is){
        string m1, m2, m3, m4, mt;
        char input[50];
        
        // Read the name from the file
        is.getline(input, 50, ';');
        setNome(input);

        // Read the day, month, and year from the file
        is >> input;
        data.setDia(atoi(input));
        is >> input;
        data.setMes(atoi(input));
        is >> input;
        data.setAno(atoi(input));
        // Read the address from the file    
        is.getline(input, 50);
        setMorada(input);
    }

};

// function to ask user for name and age and print it to him (including IO)
int e1x1(void){
    int age; 
    string name;

    cout << "Escreva o seu nome: " << endl;
    cin >> name;
    cout << "Escreva a sua idade: " << endl;
    cin >> age;

    cout << "O seu nome e "<< name << " e a sua idade e " << age << endl;
    system("pause");
    return 0;
}

// reads different types of data to certain variables
int e1x2(void){
    int i;
    float r;
    char c;
    string s;

    cout << "Introduza um numero inteiro: " << endl;
    cin >> i;
    cout << "Introduza um numero real: " << endl;
    cin >> r;
    cout << "Introduza um caracter: " << endl;
    cin >> c;
    cout << "Introduza uma string: " << endl;
    cin >> s;

    cout << "O inteiro: " << i << " o real: " << r << " o caracter: " << c << " a string: " << s << endl;
    system("pause");
    return 0;
} 

// writes given data on a file
int e2x3(void){
    int num;
    int age;
    string name;
    int n; 

    cout << "Introduza o número de alunos que pretende introduzir: ";
    cin >> n;

    ofstream of;

    of.open("alunos.txt");
    if (!of){
        cout << "Houve um erro na abertura do ficheiro!";
        exit(1);
    }

    for (int i = 0; i < n; i++){
        cout << "Escreva o seu nome: " << endl;
        cin >> name;
        cout << "Escreva a sua idade: " << endl;
        cin >> age;
        cout << "Escreva o seu numero: " << endl;
        cin >> num;
        of << name << ";" << age << ";" << num << endl;
    }

    of.close();
    return 0;
}

// outputs data from a file to the console
int e2x4(void){

    string line;
    int n;
    ifstream rf;

    rf.open("alunos.txt");
    if (!rf){
        cout << "Erro ao abrir o ficheiro!";
        exit(1);
    }
    do {
        rf >> line;
        cout << line << endl;
    } while (getline(rf, line));
    
    rf.close();
    return 0;
}

// uses the Data class impelemented above
int e3(void){

    // standard constructor (no parameters input by the user)
    Data data1;
    // contructor with user given parameters
    Data data2(24,9,2023);

    // shows initial dates using the different class constructors
    data1.show();
    data2.show();

    // updates both dates using the different updating functions (with parameters and with IO)
    data1.update(12,5,2024);
    data2.updateIO();

    // shows final dates after being updated
    data1.show();
    data2.show();

    // outputs result of the compare function (checks to see they're equal)
    data1.igual(data2);
    
    // output result of the compare method (checks to see if they're equal) (defined inside the class)
    if (data1 == data2){
        cout << "Os objetos sao iguais!" << endl;
    } else {
        cout << "Os objetos sao diferentes!" << endl;
    }

    cout << data2;

    cin >> data2;

    cout << data2;

    ifstream is;

    is.open("data.txt");
    if (!is){
        cout << "Não foi possivel abrir o ficheiro!";
        exit(1);
    }
    data1.ReadFile(is);

    cout << "Ficheiro lido: " << data1;

    ofstream os;

    os.open("data1.txt");
    if(!os){
        cout << "Não foi possivel abrir o ficheiro!";
        exit(1);
    }
    data2.SaveFile(os);
    
    return 0;
}

void Menor1990(Pessoa lp[]);

// uses the Pessoa class implemented above
int e4(void){
    // creates two objects (instances) of the class Pessoa
    Pessoa p1("Joao Culatra", Data(20,9,1987), "Rua da direita n2");
    Pessoa p2("Joni Rato", Data(4,2,1990), "Rua da esquerda n3");
    
    // uses the show method to print each person's parameters
    p1.show();
    p2.show();

    Pessoa p3;
    Pessoa p4;

   // initializes default object (using the standard constructor)
    
    // reads and changes p3's parameters through the ReadK method
    p3.ReadK();

    

    cin >> p4;
    cout << p4;

    if (p1 == p2){
        cout << "Os Objetos sao iguais" << endl; 
    }else{
        cout << "Os Objetos sao diferentes" << endl; 
        } 
    
    if (p1 != p2){
        cout << "Os Objetos sao diferentes" << endl;
    }else{
        cout << "Os Objetos sao iguais" << endl; 
        }

    p1.MaisNovo(p2);

    
    ofstream os;
    os.open("pessoa.txt");

    if (!os){
        cout << "Não foi possivel abrir o ficheiro!";
        exit(1);
    }

    p1.SaveFile(os);
    os.close();

    ifstream is;
    is.open("pessoa.txt");

    if (!is){
        cout << "Não foi possivel abrir o ficheiro!";
        exit(1);
    }

    p3.ReadFile(is);
    is.close();


    p3.show();

    Pessoa P[4] = {p1, p2, p3, p4};
//    Menor1990(P);
    
    return 0;
}

/*
void Menor1990(Pessoa lp[]){
        
    for (int i = 0; i<sizeof(lp); i++){
        if (lp[i].data.getAno() < 1990){
            lp[i].show();
        }
    }
}
*/

int main(void){
    //e1x1();
    //e1x2();
    //e2x3();
    //e2x4();
    //e3();
    e4();
    return 0;
}  