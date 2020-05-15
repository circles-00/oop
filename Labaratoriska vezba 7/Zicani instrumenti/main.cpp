/*Жичани инструменти Problem 1 (0 / 0)

Да се креира хиерархиjа на класи за репрезентациjа на жичани инструменти. За потребите на оваа хиерархиjа да се дефинира класа ZicanInstrument од коjа ќе бидат изведени двете класи Mandolina и Violina.

Во класата ZicanInstrument се чуваат податоци за:

    името на инструментот (низа од 20 знаци)
    броjот на жици
    основната цена на инструментот.

За класата Mandolina дополнително се чува неjзината форма (низа од 20 знаци).

За класата Violina дополнително се чува неjзината големина (децимален броj).

За секоjа изведените класи треба да се дефинираат соодветните конструктори и следните методи:

    cena() за пресметување на цената на инструментот
        основната цена на мандолината се зголемува за 15% доколку таа има форма во Неаполитански стил (вредноста на променливата форма е “Neapolitan”)
        основната цена на виолината се зголемува за 10% ако неjзината големина има вредност 1/4 (0.25), односно за 20% ако неjзината големина има вредност 1 (1.00)
    проптоварување на операторот ==, коj ги споредува жичаните инструменти според броjот на жици што го имаат
    преоптоварување на операторот << за печатење на сите податоци за жичаните инструменти.

Да се напише функциjа pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n) коjа на влез прима жичан инструмент, низа од покажувачи кон жичани инструменти и броj на елементи во низата. Функциjата jа печати цената на сите жичани инструменти од низата кои имаат ист броj на жици како и инструментот проследен како прв аргумент на функциjата.
*/

#include <iostream>
#include <cstring>

using namespace std;

class ZicanInstrument {
	private:
		char name[20];
		int noStrings;
		float price;
	public:
		ZicanInstrument();
		ZicanInstrument(const char * ime, const int brojZici, const float cena);
		~ZicanInstrument();
		bool operator==(const ZicanInstrument *orig);
		virtual float cena();
};

ZicanInstrument::ZicanInstrument(){
	strcpy(this->name, "None");
	this->noStrings = 0;
	this->price = 0.0;
}
ZicanInstrument::ZicanInstrument(const char * ime, const int brojZici, const float cena){
	strcpy(this->name, ime);
	this->noStrings = brojZici;
	this->price = cena;
}
ZicanInstrument::~ZicanInstrument(){}
bool ZicanInstrument::operator==(const ZicanInstrument *orig){
	if(this->noStrings == orig->noStrings)
		return true;
	else
		return false;
}
float ZicanInstrument::cena(){
	return this->price;
}

//Mandolina
class Mandolina : public ZicanInstrument {
	private:
		char shape[20];
	public:
		Mandolina();
		Mandolina(const char * ime, const int brojZici, const float cena, const char * forma) : ZicanInstrument(ime, brojZici, cena){
			strcpy(this->shape, forma);			
		}
		~Mandolina();
		float cena();
};

Mandolina::Mandolina(){
	strcpy(this->shape, "N/A");
}
Mandolina::~Mandolina(){}
float Mandolina::cena(){
	if(!strcmp(this->shape, "Neapolitan"))
		return ZicanInstrument::cena() + ZicanInstrument::cena() * 0.15;
	else return ZicanInstrument::cena();
}

//Violina
class Violina : public ZicanInstrument{
	private:
		double size;
	public:
		Violina();
		Violina(const char * ime, const int brojZici, const float cena, const float golemina) : ZicanInstrument(ime, brojZici, cena){
			this->size = golemina;
		}
		~Violina();
		float cena();
};

Violina::Violina(){
	this->size = 0.0;
}
Violina::~Violina(){}
float Violina::cena(){
	if(this->size == 0.25)
		return ZicanInstrument::cena() + ZicanInstrument::cena() * 0.1;
	else if(this->size == 1.00)
		return ZicanInstrument::cena() + ZicanInstrument::cena() * 0.2;
	else
		return ZicanInstrument::cena();
}

//global function
void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **x, int n){
	for(int i=0; i<n; i++){
		if(zi == x[i])
			cout << x[i]->cena() << endl;
	}
}

//main
int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument **zi = new ZicanInstrument*[2 * n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for(int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for(int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete [] zi;
	return 0;
}