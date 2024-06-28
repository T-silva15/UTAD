#include "C:\code\POO\C1\C1.cpp"
#include <vector>
#include <fstream>


class Funcionario : public Pessoa {
    private:
        string setor;
        int num_func, horaExtra;
        float ordBase, pHoraExtra;
    public:
        // constructor with parameters
        Funcionario(string _setor, int _num, string _nome, string _morada, float _ordBase, int _horaExtra, float _pHoraExtra, Data _data): Pessoa(_nome, _data, _morada) {
            setor = _setor;
            num_func = _num;
            ordBase = _ordBase;
            horaExtra = _horaExtra;
            pHoraExtra = _pHoraExtra;
        }
        
        // default constructor
        Funcionario(): Pessoa(){
            setor = "";
            num_func = 0;
        }

        ~Funcionario(){
        } 

        // set and get methods
        void setSetor(string _setor) { setor = _setor; }
        void setNum(int _num) { num_func = _num; }
        string getSetor() { return setor; }
        int getNum() { return num_func; }
        void setOrdBase(float _ordBase) { ordBase = _ordBase; }
        float getOrdBase() { return ordBase; }
        void setHoraExtra(int _horaExtra) { horaExtra = _horaExtra; }
        int getHoraExtra() { return horaExtra; }
        void setPHoraExtra(float _pHoraExtra) { pHoraExtra = _pHoraExtra; }
        float getPHoraExtra() { return pHoraExtra; }
        
        

        // show method that prints object attributes
        void show() {
            cout << "Setor: " << setor << endl;
            cout << "Numero de funcionario: " << num_func << endl;
            Pessoa::show();
        }
        // update method that asks for object attributes
        void update(){
            cout << "Introduza o novo setor: ";
            cin >> setor;
            cout << "Introduza o novo numero de funcionario: ";
            cin >> num_func;
            Pessoa::ReadK();
        }
        // overload of the >> operator
        friend void operator >> (istream& is, Funcionario& f){
            char aux[100];
            
            is >> (Pessoa&) f;
            cout << "Introduza o setor: ";
            is >> f.setor;
            cout << "Introduza o numero de funcionario: ";
            is >> aux;
            f.setor = aux;            
       }
        // saves object attributes to a file
        void SaveFile(ofstream& os){

            Pessoa::SaveFile(os);
            os << num_func << ";" << setor << ";" << ordBase << ";" << horaExtra << ";"; 
        }

        // reads object attributes from a file
        void ReadFile(ifstream& is){
            Pessoa::ReadFile(is);
            char aux[100];
            is.getline(aux, 100, ';');
            num_func = atoi(aux);
            is.getline(aux, 100, ';');
            setor = aux;
            is.getline(aux, 100, ';');
            ordBase = atof(aux);
            is.getline(aux, 100, ';');
            horaExtra = atoi(aux);
        }

        // calculates the salary (abstract function)
        virtual float CalculaOrdenado() = 0;

        /* // orders and shows objects by date of birth
        
        void SortAndShow(Funcionario* v, int n){
            for(int i = 0; i < n; i++){
                for(int j = i+1; j < n; j++){
                    if(v[i].getData() > v[j].getData()){
                        // swaps objects
                        Funcionario aux = v[i];
                        v[i] = v[j];
                        v[j] = aux;
                    }
                }
            }
            // shows objects
            for (int i = 0; i < n; i++)
                v[i].show();
        }
*/

};

class Operario : public Funcionario {
    private:
        bool fTurno;
    public:
        // default constructor
        Operario() : Funcionario() {
            fTurno = false;
        }
        // constructor with parameters
        Operario(bool _fTurno, string _setor, int _num, string _nome, string _morada, float _ordBase, int _horaExtra, float _pHoraExtra, Data _data) : Funcionario(_setor, _num, _nome, _morada, _ordBase, _horaExtra, _pHoraExtra, _data)
        {
            fTurno = _fTurno;
        }
        // default destructor
        ~Operario(){
            cout << "Operario destruido!" << endl;
        }
        // set and get methods
        void setFTurno(bool _fTurno) { fTurno = _fTurno; }
        bool getFTurno() { return fTurno; }
        // calculates the salary
        float CalculaOrdenado() override {
            return getOrdBase() + getHoraExtra() * getPHoraExtra();
        }
        // saves object attributes to a file
        void SaveFile(ofstream& os){
            os << "O:";
            Funcionario::SaveFile(os);
            os << fTurno << ";";
        }
        // reads object attributes from a file
        void ReadFile(ifstream& is){
            char aux[100];
            Funcionario::ReadFile(is);
            is.getline(aux, 100, ';');
            fTurno = atoi(aux);
        }   
};

class Administrativo : public Funcionario {
    private:
        
    public:
        // default constructor
        Administrativo() : Funcionario() {   
        }
        // constructor with parameters
        Administrativo(string _setor, int _num, string _nome, string _morada, float _ordBase, int _horaExtra, float _pHoraExtra, Data _data) : Funcionario(_setor, _num, _nome, _morada, _ordBase, _horaExtra, _pHoraExtra, _data) {
        }
        // default destructor
        ~Administrativo(){
            cout << "Administrativo destruido!" << endl;
        }	
        // calculates the salary        
        float CalculaOrdenado() override {
            return getOrdBase() + getHoraExtra() * getPHoraExtra();
        }
        // saves object attributes to a file
        void SaveFile(ofstream& os){
            os << "A:";
            Funcionario::SaveFile(os);
        }
        // reads object attributes from a file
        void ReadFile(ifstream& is){
            Funcionario::ReadFile(is);
        }
};
/*
void ex1 (Funcionario* v, int n){
    ifstream file; 
    file.open("funcionarios.txt");
    if (!file)
    {
        cout << "Erro ao abrir o ficheiro" << endl;
        exit(1);
    }
    for(int i = 0; i < n; i++){
        char ch;
        file.get(ch);
        if (ch == 'O')
            v[i] = new Operario();
        if (ch == 'A')
            v[i] = new Administrativo();
        else 
            cout << "Funcionario nao reconhecido" << endl;
    }
}
*/
/*
// main function
int main(){
  Ex.5

    // define objects
    Funcionario f1("Pintura", 25023, "Joca Gaio", "Rua da direita n2", Data(20,9,1987));
    Funcionario f2("Comercial", 25024, "Ana Rola", "Rua da esquerda n3", Data(4,2,1990));

    // show object attributes
    f1.show();
    f2.show();

    // change object attributes
    f1.setMorada("Rua do meio n4");
    f1.setSetor("Ferragem");
    f2.setData(Data(23,2,1990));

    // define objects
    Funcionario f3;
    Funcionario f4;

    // ask for object attributes via << operator
    cin >> f3;
    cin >> f4;

    string ficheiro;
    
    // ask for file name
    cout << "Introduza o nome do ficheiro a criar('nome.txt'): " << endl;
    cin >> ficheiro;

    // open file
    ofstream of;
    of.open(ficheiro.c_str());

    // check if file was opened
    if (!of){
        cout << "Erro ao abrir o ficheiro" << endl;
        exit(1);
    }

    // save objects to file
    f1.SaveFile(of);
    f2.SaveFile(of);
    f3.SaveFile(of);
    f4.SaveFile(of);
    // close file    
    of.close();

    Funcionario vf[4];
    vf[0] = f1;
    vf[1] = f2;
    vf[2] = f3;
    vf[3] = f4;

    ifstream file;
    file.open(ficheiro.c_str());

    if (!file)
    {
        cout << "Erro ao abrir o ficheiro" << endl;
        exit(1);
    }
    
    for(int i = 0; i < 4; i++){
        vf[i].ReadFile(file);
        cout << "v[" << i << "] lido!" << endl;
    }

    f1.SortAndShow(vf, 4);


    cout << "Menu" << endl;
    cout << "1 - Ler ficheiro" << endl;

    exit(0);
}*/