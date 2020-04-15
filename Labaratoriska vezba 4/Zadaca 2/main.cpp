/*/*Задача 2 Problem 2 (0 / 0)

Да се дефинира класата Film во која се чуваат информации за:

    *име на филмот (динамички алоцирано поле од знаци)
    *мемориската зафатнина на филмот изразена во MB
    *жанр на филмот кој може да биде: акција, комедија или драма (енумерација zanr)

Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинира функцијата:

    *pecati() - функција во која ќе се печатат одделени со цртичка(-): мемориска зафатнина на филмот со постфикс MB и името на филмот во наводници.

Да се креира класата DVD во која се чуваат информации за :

    *низа од филмови снимени на DVD-то (Поле од најмногу 5 објекти од класата Film )
    *број на филмови снимени на DVD-то
    *меморискиот капацитет на DVD-то (во MB)

Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинираат методите:

    dodadiFilm (Film f) - со кој се додава филмот f на DVDто, 
    но само ако има доволно преостанато место (земајќи го предвид меморискиот капацитет 
    на DVD-то
    и мемориската зафатнина на снимените филмови) и
    притоа да има помалку од 5 филмови на DVD-то.

    pecatiFilmoviDrugZanr(zanr z) – со кој се печатат информациите за сите филмови кои 
    НЕ се од жанрот zanr (акција, комедија или драма).

    (дополнително барање):float procentNaMemorijaOdZanr(zanr z)- 
    со кој се пресметува процентот на меморијата која ја зафаќаат 
    филмовите од жанр z на DVD-то.
1
Terminator 20 0

out
===== Testiranje na klasata Film ======
20MB-"Terminator"
*/

#include <iostream>
#include <cstring>
using namespace std;

enum zanr{AKCIJA,KOMEDIJA,DRAMA};

//class Film
class Film{
    private:
        char name[50];
        int memory;
        zanr z;
    public:
        Film(){}
        Film(const char * ime, const int memorija, zanr g);
        Film &operator=(const Film &orig);
        Film(const Film &orig);
        void pecati();
        int getMemory();
        int getZanr();
};

Film::Film(const char * ime, const int memorija, zanr g){
    strcpy(this->name,ime);
    this->memory=memorija;
    this->z=g;
}
Film &Film::operator=(const Film &orig){
    if(this!=&orig){
        strcpy(this->name,orig.name);
        this->memory=orig.memory;
        this->z=orig.z;
    }
    return *this;
}
Film::Film(const Film &orig){
    strcpy(this->name,orig.name);
    this->memory=orig.memory;
    this->z=orig.z;
}
void Film::pecati(){
    cout << this->memory << "MB-" << "\"" << this->name << "\"" << endl;
}
int Film::getMemory(){
    return this->memory;
}
int Film::getZanr(){
    return this->z;
}

//class DVD
class DVD{
    private:
        Film f[5];
        int noFilms;
        int currentsize;
        int capacity;
    public:
        DVD(){}
        DVD(int kapacitet);
        void dodadiFilm(Film f);
        Film * getFilm(int i);
        int getBroj();
        void pecatiFilmoviDrugZanr(zanr z);
        float procentNaMemorijaOdZanr(zanr z);
};

DVD::DVD(int kapacitet){
    this->capacity=kapacitet;
    this->noFilms=0;
    this->currentsize=0;
}
/*void DVD::dodadiFilm(Film f){
    int totalmemory=0;
    for(int i=0; i<noFilms; i++){
        totalmemory = totalmemory + this->f[i].getMemory();
    }
    totalmemory+=f.getMemory();
    if((this->capacity > totalmemory) && (this->noFilms < 5)){
        this->f[noFilms] = f;
    }
    noFilms++;
}*/
void DVD::dodadiFilm(Film nov)
    {
        if(this->capacity>=currentsize + nov.getMemory())
        {
            if(noFilms<5)
            {
                f[noFilms] = nov;
                noFilms++;
                currentsize+=nov.getMemory();
            }
        }
    }
Film *DVD::getFilm(int i){
    return &this->f[i];
}
int DVD::getBroj(){
    return this->noFilms;
}
void DVD::pecatiFilmoviDrugZanr(zanr z){
    for(int i=0; i<this->noFilms; i++){
        if(this->f[i].getZanr() != z)
            this->f[i].pecati();
    }
}
float DVD::procentNaMemorijaOdZanr(zanr z){
    float memory=0;
    for(int i=0; i<this->noFilms; i++){
        if(this->f[i].getZanr() == z){
            memory+=f[i].getMemory();
        }
    }

    return memory*100/this->currentsize;
}


//main
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i))->pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i))->pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
		cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
		DVD omileno(40);
		cin >> n;
		for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";
		
	}

    return 0;
}