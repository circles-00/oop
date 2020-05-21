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
        const void copy(const Ucesnik &orig){
            this->name = new char[strlen(orig.name)+1];
            strcpy(this->name, orig.name);
            this->sex = orig.sex;
            this->age = orig.age;
        }
    public:
        Ucesnik(){
            this->name = new char[0];
            strcpy(this->name, "");
            this->sex = false;
            this->age = 0;
        }
        Ucesnik(const char * name, const bool sex, const int age){
            this->name = new char[strlen(name)+1];
            strcpy(this->name, name);
            this->sex = sex;
            this->age = age;
        }
        Ucesnik(const Ucesnik &orig){
            this->copy(orig);
        }
        Ucesnik &operator=(const Ucesnik &orig){
            if(this != &orig){
                delete [] this->name;
                this->copy(orig);
            }
            return *this;
        }
        ~Ucesnik(){
            delete [] this->name;
        }
        bool operator>(Ucesnik &orig){
            if(this->age > orig.age)
                return true;
            else
                return false;
        }
        friend ostream &operator<<(ostream &os, Ucesnik &orig){
            os << orig.name << endl;
            if(orig.sex)
                os << "mashki" << endl;
            else
                os << "zhenski" << endl;
            os << orig.age << endl;
            return os;
        }
        int getAge(){
            return this->age;
        }
};

class Maraton{
    private:
        char location[100];
        Ucesnik * ucs;
        int noUcs;
        const void copy(const Maraton &orig){
            strcpy(this->location, orig.location);
            this->noUcs = orig.noUcs;
            for(int i=0; i<this->noUcs; i++)
                this->ucs[i] = orig.ucs[i];
        }
    public:
        Maraton(){
            strcpy(this->location, "None");
            this->ucs = new Ucesnik[0];
            this->noUcs = 0;
        }
        Maraton(const char * location){
            strcpy(this->location, location);
            this->ucs = new Ucesnik[0];
            this->noUcs = 0;
        }
        Maraton(const Maraton &orig){
            this->copy(orig);
        }
        Maraton &operator=(const Maraton &orig){
            if(this != &orig){
                delete [] this->ucs;
                this->copy(orig);
            }
            return *this;
        }
        ~Maraton(){
            delete [] this->ucs;
        }
        Maraton &operator +=(const Ucesnik &orig){
            Ucesnik * tmp;
            tmp = new Ucesnik[this->noUcs + 1];
            for(int i=0; i<this->noUcs; i++)
                tmp[i] = this->ucs[i];

            tmp[this->noUcs++] = orig;
            delete [] this->ucs;
            this->ucs = new Ucesnik[this->noUcs + 1];
            this->ucs = tmp;

            return *this; 
        }
        double prosecnoVozrast(){
            double total = 0.0;
            for(int i=0; i<this->noUcs; i++)
                total += this->ucs[i].getAge();
            return total/this->noUcs;
        }
        const void pecatiPomladi(Ucesnik &orig){
            for(int i=0; i<this->noUcs; i++){
                if(orig > this->ucs[i])
                    cout << this->ucs[i];
            }
        }
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