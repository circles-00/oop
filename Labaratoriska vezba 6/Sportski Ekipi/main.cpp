/*Спортски екипи Problem 2 (0 / 0)

Да се дефинира класа Ekipa за коjа се чуваат следниве информации:

    името на екипата (низа од наjмногу 15 знаци)
    броj на порази
    броj на победи

За оваа класа да се дефинира метод pecati() коjа ги печати податоците за екипаta. Од оваа класа да се изведe новa класa, FudbalskaEkipa.

За фудбалската екипа дополнително се чуваат информации за:

    вкупниот броj на црвени картони
    вкупниот броj жолти картони
    броjот на нерешени натпревари

За фудбалската екипа да се преоптовари методот pecati(), така што покрај останатите информации, ќе се испечатат и 
бројот на нерешени резултати и вкупен број на поени во формат: Име на екипа, броj на победи, броj на порази, броj на 
нерешени натпревари и вкупен броj на поени (за победа фудбалската екипа добива 3 поени, додека за нерешен резултата, 1 поен);
*/

#include <iostream>
#include <cstring>

using namespace std;

class Ekipa{
    private:
        char name[15];
        int wins;
        int loses;
    public:
        Ekipa();
        Ekipa(const char * ime, const int pobedi, const int izgubi);
        ~Ekipa(){}
        void pecati();
        const char * getName();
        const int getWins();
        const int getLoses();
};

Ekipa::Ekipa(){
    strcpy(this->name, "");
    this->wins = 0;
    this->loses = 0;
}
Ekipa::Ekipa(const char * ime, const int pobedi, const int izgubi){
    strcpy(this->name, ime);
    this->wins = pobedi;
    this->loses = izgubi;
}
void Ekipa::pecati(){
    cout << "Ime: " << this->name << " Pobedi: " << this->wins << " Porazi: " << this->loses << endl;
}
const char * Ekipa::getName(){
    return this->name;
}
const int Ekipa::getWins(){
    return this->wins;
}
const int Ekipa::getLoses(){
    return this->loses;
}


class FudbalskaEkipa: public Ekipa{
    private:
        int redcards;
        int yellowcards;
        int draws;
    public:
        FudbalskaEkipa();
        FudbalskaEkipa(const char * ime, const int pobedi, const int izgubi, const int ck, const int zk, const int ner) : Ekipa(ime, pobedi, izgubi){
            this->redcards = ck;
            this->yellowcards = zk;
            this->draws = ner;
        }
        ~FudbalskaEkipa(){}
        void pecati();
};

FudbalskaEkipa::FudbalskaEkipa(){
    this->redcards = 0;
    this->yellowcards = 0;
    this->draws = 0;
}
void FudbalskaEkipa::pecati(){
    cout << "Ime: " << this->getName() << " Pobedi: " << this->getWins() << " Porazi: " << this->getLoses() << " Nereseni: " << this->draws << " Poeni: " << (this->getWins() * 3) + (this->draws * 1) << endl;
}

//main
int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}