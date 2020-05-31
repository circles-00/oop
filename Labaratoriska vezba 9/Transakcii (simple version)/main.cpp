#include<iostream>
#include<cstring>

using namespace std;

class InvalidDateException{
    private:
        int day;
        int month;
        int year;
    public:
        InvalidDateException(){
            this->day = 0;
            this->month = 0;
            this->year = 0;
        }
        InvalidDateException(const int day, const int month, const int year){
            this->day = day;
            this->month = month;
            this->year = year;
        }
        const void showMsg(){
            cout << "Invalid Date " << this->day <<  "/" << this->month << "/" << this->year <<endl;
        }
};

class NotSupportedCurrencyException{
    private:
        char currency[4];
    public:
        NotSupportedCurrencyException(){
            strcpy(this->currency, "Uknown");
        }
        NotSupportedCurrencyException(const char * currency){
            strcpy(this->currency, currency);
        }
        const void showMsg(){
            cout << this->currency << " is not a supported currency" << endl;
        }
};

class Transakcija{
    protected:
        int day;
        int month;
        int year;
        double total;
        static double eur;
        static double usd;
    public:
        Transakcija(){
            this->day = 0;
            this->month = 0;
            this->year = 0;
            this->total = 0.0;
        }
        Transakcija(const int day, const int month, const int year, const double total){
            if(day<1 || day>31 || month<1 || month>12 || year < 1)
                throw InvalidDateException(day, month, year);
            this->day = day;
            this->month = month;
            this->year = year;
            this->total = total;
        }
        virtual const double voDenari() = 0;
        virtual const void pecati() = 0;
        const static void setEUR(double newEUR);
        const static void setUSD(double newUSD);
        const static double getEUR();
        const static double getUSD();
};
double Transakcija::eur = 61.0;
double Transakcija::usd = 50.0;
const double Transakcija::getEUR(){
    return eur;
}
const double Transakcija::getUSD(){
    return usd;
}
const void Transakcija::setEUR(double newEUR){
    eur = newEUR * 1.0;
}
const void Transakcija::setUSD(double newUSD){
    usd = newUSD * 1.0;
}

class DenarskaTransakcija : public Transakcija{
    public:
        DenarskaTransakcija(const int day, const int month, const int year, const double total) : Transakcija(day, month, year, total) {}
        const double voDenari(){
            return this->total;
        }
        const void pecati(){
            cout << this->day << "/" << this->month << "/" << this->year << " " << this->total << " MKD" << endl;
        }
        ~DenarskaTransakcija(){}
};

class DeviznaTransakcija : public Transakcija {
    private:
        char currency[4];
    public:
    DeviznaTransakcija(){
        strcpy(this->currency, "Uknown");
    }
        DeviznaTransakcija(const int day, const int month, const int year, const double total, const char * currency) : Transakcija(day, month, year, total){
            if((strcmp(currency, "EUR")) && (strcmp(currency, "USD")))
                throw NotSupportedCurrencyException(currency);
            strcpy(this->currency, currency);
        }
        const double voDenari(){
            if(!(strcmp(this->currency, "USD")))
                return this->total * usd;
            else
                return this->total * eur;
        }
        const void pecati(){
            cout << this->day << "/" << this->month << "/" << this->year << " " << this->total << " " << this->currency << endl;
        }
        ~DeviznaTransakcija(){}
};

class Smetka{
    private:
        Transakcija ** tii;
        int noTransactions;
        char smetka[15];
        double saldo;
        const void copy(const Smetka &orig){
            this->tii = new Transakcija *[orig.noTransactions + 1];
            this->noTransactions = orig.noTransactions;
            strcpy(this->smetka, orig.smetka);
            this->saldo = orig.saldo;
        }
    public:
        Smetka(){
            this->tii = new Transakcija *[0];
            this->noTransactions = 0;
            strcpy(this->smetka, "N/A");
            this->saldo = 0.0;
        }
        Smetka(const char * smetka, const double saldo){
            this->tii = new Transakcija *[0];
            this->noTransactions = 0;
            strcpy(this->smetka, smetka);
            this->saldo = saldo;
        }
        Smetka(const Smetka &orig){
            this->copy(orig);
        }
        Smetka &operator=(const Smetka &orig){
            if(this != &orig){
                delete [] this->tii;
                this->copy(orig);
            }

            return *this;
        }
        ~Smetka(){
            delete [] this->tii;
        }
        Smetka &operator+=(Transakcija *orig){
            Transakcija **tmp = new Transakcija*[this->noTransactions + 1];
            for(int i=0; i<this->noTransactions; i++)
                tmp[i] = this->tii[i];
            tmp[this->noTransactions++] = orig;
            delete [] this->tii;
            this->tii = tmp;

            return *this;
        }
        const void izvestajVoDenari(){
            double total = 0.0;
            for(int i=0; i<this->noTransactions; i++)
                total += this->tii[i]->voDenari();
            cout << "Korisnikot so smetka: " << this->smetka << " ima momentalno saldo od " << this->saldo + total << " MKD" << endl;
        }
        const void pecatiTransakcii(){
            for(int i=0; i<this->noTransactions; i++)
                this->tii[i]->pecati();
        }
};


int main () {
	
	Smetka s ("300047024112789",1500);
	
	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];
	
	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
		cin>>tip>>den>>mesec>>godina>>iznos;		
		if (tip==2){
			cin>>valuta;
			try{
                Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
                s+=t;
            }
			catch (InvalidDateException &dateExc){
                dateExc.showMsg();
            }
            catch (NotSupportedCurrencyException &cExc){
                cExc.showMsg();
            }
		}
		else {
			try{
                Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
                s+=t;
            }
            catch (InvalidDateException &dateExc){
                dateExc.showMsg();
            }
            catch (NotSupportedCurrencyException &cExc){
                cExc.showMsg();
            }
		}
			
	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
   
    
    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;
    
        
    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    
    
	
	
	return 0;
}