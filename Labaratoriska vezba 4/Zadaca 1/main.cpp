/*Задача 1 Problem 1 (0 / 1)

Да се дефинира класа ParkingPlac во која се чуваат податоци за:

    *Адреса на плацот (низа од знаци, максимум 20),
    *Идентификациски број на плацот (динамичка низа од знаци),
    *Цена за паркирање за 1 час (цел број),
    *Заработка на паркинг плацот (цел број)

параметри потребни за дополнителниот дел од задачата:

    *Динамичка низа од класата Avtomobil
    *Број на паркирани автомобили во даден момент

За потребите на класата да се имплементираат :

    *соодветни конструктори и деструктор, и потребните get-функции (погледнете ги повиците во main функцијата)

    *функција pecati() за печатење на податоците за еден паркинг плац во следниот формат:

    *идентификациски_број адреса - X denari, ако X е заработката на паркинг плацот X не е 0

    *идентификациски_број адреса , ако X =0

    *функција platiCasovi(int casovi) која на заработката ја додава платената вредност за дадениот број на часови.
    *функција daliIstaAdresa(ParkingPlac p) во која се споредува дали дадениот паркинг плац е на иста адреса како паркинг плацот p.

Во дадената main функција прво се внесуваат n паркинг плацеви. Потоа се внесуваат m плаќања и на крај се печатат сите паркинг плацеви од низата кои имаат иста адреса со дадениот паркинг плац (објектот pCentar).

ДОПОЛНИТЕЛНО БАРАЊЕ

Дефинирајте класа Avtomobil во која се чуваат податоците за:

    *Бојата на автомобилот (низа од знаци, максимум 20)
    *Брендот на автомобилот (низа од знаци, максимум 20)
    *Моделот на автомобилот (низа од знаци, максимум 20)

За потребите на класата ќе треба да :

    *Се имплементира конструктор
    *Да го преоптоварите assignment operator-от

Понатака да пишете метод за класата ParkingPlac наречен parkirajVozilo(Avtomobil novoVozilo), неговата цел ќе биде да се паркира ново возило на паркингот во кој се повикува методот.

На крај ќе треба да се испечатат паркираните возила во еден паркинг преку методот pecatiParkiraniVozila() кој исто така треба да биде имплементиран во класата ParkingPlac.

Ориентирајте се според дадениот код во main методот за како се ова треба да го имплементирате.

2
Cvetan Dimov
C12 100
Cvetan Dimov
C11 80
2
C12 2
C11 1

out
=========
C12 Cvetan Dimov - 200 denari
C11 Cvetan Dimov - 80 denari
*/

#include<iostream>
#include <cstring>

using namespace std;

// class Avtomobil
class Avtomobil{
    private:
        char color[20];
        char brand[20];
        char model[20];
    public:
        Avtomobil(){}
        Avtomobil(const char * boja, const char * brend, const char * model);
        Avtomobil& operator=(const Avtomobil &orig);
        void print();
};
Avtomobil::Avtomobil(const char * boja, const char * brend, const char * model){
    strcpy(this->color,boja);
    strcpy(this->brand,brend);
    strcpy(this->model,model);
}
Avtomobil &Avtomobil::operator=(const Avtomobil &orig){
    if(this!=&orig){
        strcpy(this->color,orig.color);
        strcpy(this->brand,orig.brand);
        strcpy(this->model,orig.model);
    }
    return *this;
}
void Avtomobil::print(){
    cout << this->color << " " << this->brand << " " << this->model << endl;
}

//class ParkingPlac
class ParkingPlac {
    private:
        char address[20];
        char id[50];
        int costperhour;
        int profit;
        Avtomobil * a;
        int noParked;
    public:
        ParkingPlac(){}
        ParkingPlac(const char * adresa, const char * id, const int cenanacas);
        ~ParkingPlac();
        void parkirajVozilo(const Avtomobil * n, int br);
        void pecati();
        const char * getId();
        void platiCasovi(int brojcasovi);
        bool daliIstaAdresa(ParkingPlac p);
        void pecatiParkiraniVozila();
};
ParkingPlac::ParkingPlac(const char * adresa, const char * id, const int cenanacas){
    strcpy(this->address,adresa);
    strcpy(this->id,id);
    this->costperhour=cenanacas;
    this->profit=0;
}
ParkingPlac::~ParkingPlac(){
    delete [] this->a;
}
void ParkingPlac::pecati(){
    if(this->profit){
        cout << this->id << " " << this->address << " - " << this->profit << " denari" << endl;
    } else {
        cout << this->id << " " << this->address << endl;
    }
}
const char * ParkingPlac::getId(){
    return this->id;
}
void ParkingPlac::platiCasovi(int brojcasovi){
    this->profit = profit + (brojcasovi * this->costperhour);
}
bool ParkingPlac::daliIstaAdresa(const ParkingPlac p){
    if(!strcmp(this->address,p.address))
        return true;
    else
        return false;
}
void ParkingPlac::parkirajVozilo(const Avtomobil * n, int br){
    this->noParked=br;
    this->a = new Avtomobil[noParked];
    for(int i=0; i<br; i++){
        *(a+i) = *(n+i);
    }
}
void ParkingPlac::pecatiParkiraniVozila(){
    cout << "Vo parkingot se parkirani slednite vozila: " << endl;
    for(int i=0; i<this->noParked; i++){
        cout << i+1 << ".";
        a[i].print();
    }
}

int main(){

	ParkingPlac p[100];
	int n,m;
	char adresa[50],id[50];
	int brojcasovi,cenacas;
	cin>>n;
	if(n > 0){


		for (int i=0;i<n;i++){
	        cin.get();
			cin.getline(adresa,50);
			cin>>id>>cenacas;
			
			ParkingPlac edna(adresa,id,cenacas);
	        
	        p[i]=edna;
		}
	    
		//plakjanje
		cin>>m;
		for (int i=0;i<m;i++){

			cin>>id>>brojcasovi;
	        
	        int findId=false;
	        for (int j=0;j<m;j++){
	            if (strcmp(p[j].getId(),id)==0){
	                p[j].platiCasovi(brojcasovi);
	                findId=true;
	            }
	        }
			if (!findId)
	        cout<<"Ne e platen parking. Greshen ID."<<endl;
		}

	    cout<<"========="<<endl;
	    ParkingPlac pCentar("Cvetan Dimov","C10",80);
		for (int i=0;i<n;i++){
	        if (p[i].daliIstaAdresa(pCentar))
	            p[i].pecati();
        }

	} else {

		ParkingPlac najdobarPlac("Mars", "1337", 1);
	    int brVozila;
	    cin >> brVozila;
        Avtomobil *n = new Avtomobil[brVozila];
	    for(int i = 0; i < brVozila; ++i){

	    	char boja[20];
	    	char brend[20];
	    	char model[20];

	    	cin >> boja >> brend >> model;
            *(n+i) = Avtomobil(boja, brend, model);
	    	
	    }
        najdobarPlac.parkirajVozilo(n,brVozila);
        delete [] n;
	    if(brVozila != 0)
	    najdobarPlac.pecatiParkiraniVozila();

	}  
}