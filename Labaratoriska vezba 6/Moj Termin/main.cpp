/*Мој Термин Problem 5 (0 / 0)

Со цел да се подобри системот Мој Термин, со воведување функционалност за пресметување плати за лекарите за еден месец, 
од Министерството за здравство на Република Македонија, ги добивате следните задачи:

Да се креира класа Lekar во која што ќе се чуваат:

    факсимил на докторот (цел број)
    име (низа од максимум 10 знаци)
    презиме (низа од максимум 10 знаци)
    почетна плата (децимален број)

За класата да се имплементираат методите:

    void pecati(): Печати информации за лекарот во формат Факсимил: име презиме

    double plata(): ја враќа платата на лекарот

Да се креира класа MaticenLekar која што наследува од Lekar и во неа се чуваат дополнителни информации за:

    број на пациенти со којшто лекарот соработувал во текот на месецот (цел број)
    котизации наплатени од пациентите во текот на месецот (динамички алоцирана низа од децимални броеви)

За класата да се препокријат методитe:

    void pecati() : ги печати основните информации за лекарот, а во нов ред го печати и просекот од наплатените котизации

    double plata(): ја враќа платата на матичниот лекар
        Платата на матичниот лекар се пресметува со зголемување на основната плата за 30% од просекот од наплатените котизации за месецот

*/
#include <iostream>
#include <cstring>

using namespace std;

class Lekar{
    protected:
        int faximil;
        char name[10];
        char lastname[15];
        double salary;
    public:
        Lekar();
        Lekar(const int faximil, const char * name, const char * lastname, const double salary);
        Lekar(const Lekar &orig);
        Lekar &operator=(const Lekar &orig);
        void pecati();
        const double plata();
};

Lekar::Lekar(){
    this->faximil = 0.0;
    strcpy(this->name, "None");
    strcpy(this->lastname, "None");
    this->salary = 0.0;
}
Lekar::Lekar(const int faximil, const char * name, const char * lastname, const double salary){
    this->faximil = faximil;
    strcpy(this->name, name);
    strcpy(this->lastname, lastname);
    this->salary = salary;
}
Lekar::Lekar(const Lekar &orig){
    this->faximil = orig.faximil;
    strcpy(this->name, orig.name);
    strcpy(this->lastname, orig.lastname);
    this->salary = orig.salary;
}
Lekar &Lekar::operator=(const Lekar &orig){
    if(this != &orig){
        this->faximil = orig.faximil;
        strcpy(this->name, orig.name);
        strcpy(this->lastname, orig.lastname);
        this->salary = orig.salary;
    }
    return *this;
}
void Lekar::pecati(){
    cout << this->faximil << ": " << this->name << " " << this->lastname << endl;
}
const double Lekar::plata(){
    return this->salary;
}

class MaticenLekar : public Lekar{
    private:
        int patients;
        double * kotizacii;
    public:
        MaticenLekar();
        MaticenLekar(const Lekar orig, const int patients, double * kotizacii) : Lekar(orig){
            this->patients = patients;
            this->kotizacii = new double[patients];
            for(int i=0; i<patients; i++)
                this->kotizacii[i] = kotizacii[i];
        }
        MaticenLekar(const MaticenLekar &orig);
        MaticenLekar &operator=(const MaticenLekar &orig);
        ~MaticenLekar();
        void pecati();
        const double plata();
        const double averageKotizacii();
};

MaticenLekar::MaticenLekar(){
    this->patients = 0;
    this->kotizacii = new double[0];     
}
MaticenLekar::MaticenLekar(const MaticenLekar &orig){
    this->faximil = orig.faximil;
    strcpy(this->name, orig.name);
    strcpy(this->lastname, orig.lastname);
    this->salary = orig.salary;
    this->patients = orig.patients;
    this->kotizacii = new double[orig.patients];
    for(int i=0; i<patients; i++)
        this->kotizacii[i] = orig.kotizacii[i];
}
MaticenLekar &MaticenLekar::operator=(const MaticenLekar &orig){
    if(this != &orig){
        delete [] this->kotizacii;
        this->faximil = orig.faximil;
        strcpy(this->name, orig.name);
        strcpy(this->lastname, orig.lastname);
        this->salary = orig.salary;
        this->patients = orig.patients;
        this->kotizacii = new double[orig.patients];
        for(int i=0; i<patients; i++)
            this->kotizacii[i] = orig.kotizacii[i];
    }
    return *this;
}
MaticenLekar::~MaticenLekar(){
    delete [] this->kotizacii;
}
const double MaticenLekar::averageKotizacii(){
    double temp = 0.0;
    for(int i=0; i<this->patients; i++){
        temp += this->kotizacii[i];
    }
    return temp / this->patients * 1.0;
}
void MaticenLekar::pecati(){
    Lekar::pecati();
    cout << "Prosek na kotizacii: " << this->averageKotizacii() << endl;
}
const double MaticenLekar::plata(){
    return Lekar::plata() + (averageKotizacii() * 0.3);
}


//main
int main() {
	int n;
	cin>>n;
	int pacienti;
	double kotizacii[100];
	int faksimil;
	char ime [20];
	char prezime [20];
	double osnovnaPlata;
	
	Lekar * lekari = new Lekar [n];
	MaticenLekar * maticni = new MaticenLekar [n];
	
	for (int i=0;i<n;i++){
		cin >> faksimil >> ime >> prezime >> osnovnaPlata;
		lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);		
	}
	
	for (int i=0;i<n;i++){
		cin >> pacienti;
		for (int j=0;j<pacienti;j++){
			cin >> kotizacii[j];
		}
		maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
	}
	
	int testCase;
	cin>>testCase;
	
	if (testCase==1){
		cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
		for (int i=0;i<n;i++){
			lekari[i].pecati();
			cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
		}
	}
	else {
		cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
		for (int i=0;i<n;i++){
			maticni[i].pecati();
			cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
		}
	}
	
	delete [] lekari;
	delete [] maticni;
	
	return 0;
}