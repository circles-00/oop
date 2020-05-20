/*Маратон Problem 4 (0 / 0)

Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:

    име (динамички алоцирана низа од знаци)
    пол (bool)
    возраст (цел број) (5 поени).

За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)

Дополнително за оваа класа да се преоптоварат:

    оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
    операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)

Да се дефинира класа Maraton за кој се чуваат:

    локација (низа од максимум 100 знаци)
    низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
    број на учесници (цел број) (5 поени).

За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени) Исто така да се 
имплементираат следните методи:

    оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
    prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
    pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)
*/

#include <iostream>
#include <cstring>

using namespace std;

class Ucesnik{
    private:
        char * name;
        bool sex;
        int age;
        void copy(const Ucesnik &orig){
            this->name = new char[strlen(orig.name)+1];
            strcpy(this->name, orig.name);
            this->sex = orig.sex;
            this->age = orig.age;
        }
    public:
        Ucesnik();
        Ucesnik(const char * ime, const bool pol, const int vozrast);
        Ucesnik(const Ucesnik &orig);
        ~Ucesnik();
        bool operator>(const Ucesnik &orig);
        friend ostream& operator<<(ostream& os, const Ucesnik &orig){
            os << orig.name << endl;
            os << orig.sex << endl;
            os << orig.age << endl;

            return os;
        }
};

Ucesnik::Ucesnik(){
    this->name = new char[0];
    strcpy(this->name, "");
    this->sex = false;
    this->age = 0;
}
Ucesnik::Ucesnik(const char * ime, const bool pol, const int vozrast){
    this->name = new char[strlen(ime)+1];
    strcpy(this->name, ime);
    this->sex = pol;
    this->age = vozrast;
}
Ucesnik::Ucesnik(const Ucesnik &orig){
    this->copy(orig);
}
Ucesnik::~Ucesnik(){
    delete [] this->name;
}
bool Ucesnik::operator>(const Ucesnik &orig){
    if(this->age < orig.age)
        return true;
    else
        return false;
}

class Maraton{
    private:
        char location[100];
        Ucesnik * array;
        int noUcesnici;
    public:
        Maraton();
        Maraton(const char * lokacija);
};


//main
int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
    	u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
	m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
	return 0;
}