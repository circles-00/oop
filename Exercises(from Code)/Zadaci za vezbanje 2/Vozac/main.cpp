#include <iostream>
#include <cstring>

using namespace std;

class Vozac{
    protected:
        char name[100];
        int age;
        int noRaces;
        bool isVeteran;
    public:
        Vozac(){
            strcpy(this->name, "None");
            this->age = 0;
            this->noRaces = 0;
            this->isVeteran = false;
        }
        Vozac(const char * name, const int age, const int noRaces, const bool isVeteran){
            strcpy(this->name, name);
            this->age = age;
            this->noRaces = noRaces;
            this->isVeteran = isVeteran;
        }
        virtual ~Vozac(){}     
        virtual const double getSalaryPerRace() = 0;
        virtual const double getTax() = 0;
        friend ostream &operator << (ostream &os, Vozac &orig){
            os << orig.name << "\n" << orig.age << "\n" << orig.noRaces << "\n";
            if(orig.isVeteran)
                os << "VETERAN\n";
            return os;
        }
        bool operator==(Vozac &orig){
            return(this->getSalaryPerRace() == orig.getSalaryPerRace());
        }
};

class Avtomobilist : public Vozac{
    private:
        double price;
    public:
        Avtomobilist(){
            this->price = 0.0;
        }
        Avtomobilist(const char * name, const int age, const int noRaces, const bool isVeteran, const double price) : Vozac(name, age, noRaces, isVeteran){
            this->price = price;
        }
        ~Avtomobilist(){}
        const double getSalaryPerRace(){
            return this->price / 5;
        }
        const double getTax(){
            return this->noRaces > 10 ? this->getSalaryPerRace() * 0.15 : this->getSalaryPerRace() * 0.1;
        }
};

class Motociklist : public Vozac{
    private:
        int power;
    public:
        Motociklist(){
            this->power = 0;
        }
        Motociklist(const char * name, const int age, const int noRaces, const bool isVeteran, const int power) : Vozac(name, age, noRaces, isVeteran){
            this->power = power;
        }
        ~Motociklist(){}
        const double getSalaryPerRace(){
            return this->power * 20;
        }
        const double getTax(){
           return this->isVeteran ? this->getSalaryPerRace() * 0.25 : this->getSalaryPerRace() * 0.2;
        }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vv){
    int count = 0;
    for(int i=0; i<n; i++)
        if(*v[i] == *vv)
            count++;
    return count;
}



int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->getTax() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}