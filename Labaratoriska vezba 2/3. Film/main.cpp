/* Филм Problem 3 (0 / 0)

Да се дефинира класа Film, во која ќе се чуваат информации за:

    *име низа од 100 знаци
    *режисер низа од 50 знаци
    *жанр низа од 50 знаци
    *година цел број

Сите променливи треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

    *default конструктор и конструктор со аргументи
    *метод за печатење на информациите за филмот

Дополнително да се реализира надворешна функција:

    void pecati_po_godina(Film *f, int n, int godina) која ќе прима аргумент низа од филмови, вкупниот број на филмови и година,
    а треба да ги отпечати само филмовите кои се направени во дадената година.
   
    Ime: Wall-E
    Reziser: Andrew_Stanton
    Zanr: Animation
    Godina: 2008
*/

#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class Film {
    private:
        char name[100];
        char director[50];
        char genre[50];
        int year;
    public:
        Film(){}
        Film(const char *ime, const char *reziser, const char *zanr, int god);
        void print();
        int getyear();
};
Film::Film(const char *ime, const char *reziser, const char *zanr, int god) {
            strcpy(name, ime);
            strcpy(director, reziser);
            strcpy(genre, zanr);
            year = god;
}

void Film::print() {
    cout << "Ime: "<< name << endl;
    cout << "Reziser: " << director << endl;
    cout << "Zanr: " << genre << endl;
    cout << "Godina: " << year << endl;
}

int Film::getyear() {
    return year;
}

void pecati_po_godina(Film *f, int n, int godina){
    for(int i=0; i<n; i++){
        if(f[i].getyear() == godina)
            f[i].print();
    }
}

int main() {
 	int n;
 	cin >> n;
 	//da se inicijalizira niza od objekti od klasata Film
    Film f[100];
 	for(int i = 0; i < n; ++i) {
 		char ime[100];
 		char reziser[50];
 		char zanr[50];
 		int godina;
 		cin >> ime;
 		cin >> reziser;
 		cin >> zanr;
 		cin >> godina;
 		//da se kreira soodveten objekt
        f[i] = Film(ime,reziser,zanr,godina);
 	}
 	int godina;
 	cin >> godina;
 	//da se povika funkcijata pecati_po_godina
    pecati_po_godina(f,n,godina);
 	return 0;
 }