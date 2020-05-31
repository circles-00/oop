#include<iostream>
#include<cstring>

using namespace std;

class Exception{
    public:
        const void message(){
            cout << "Pogresno vnesena registracija" << endl;
        }
};

class ImaMasa{
    public:
        virtual const double vratiMasa() = 0;
        virtual const void pecati() = 0;
        virtual ~ImaMasa(){}
};

class PaketPijalok{
    private:
        double volumenEden;
        int kolicina;
        static double gustina;
        static double masaAmbalaza;
    public:
        PaketPijalok(){
            this->volumenEden = 0;
            this->kolicina = 0;
        }
        PaketPijalok(const double volumenEden, const int kolicina){
            this->volumenEden = volumenEden;
            this->kolicina = kolicina;
        }
        const double vratiMasa(){
            return (this->volumenEden * gustina + masaAmbalaza) * this->kolicina;
        }
        const void pecati(){}
        const int getKolicina(){
            return this->kolicina;
        }
        const double getVolumen(){
            return this->volumenEden;
        }
        const static double getGustina(){
            return gustina;
        }
};
double PaketPijalok::gustina = 0.8;
double PaketPijalok::masaAmbalaza = 0.2;

class PaketSok : public PaketPijalok, public ImaMasa{
    private:
        bool daliGaziran;
    public:
        PaketSok(){
            this->daliGaziran = false;
        }
        PaketSok(const double volumenEden, const int kolicina, const bool daliGaziran) : PaketPijalok(volumenEden, kolicina){
            this->daliGaziran = daliGaziran;
        }
        const double vratiMasa(){
            if(this->daliGaziran == false)
                return PaketPijalok::vratiMasa() + this->getKolicina() * 0.1;
            else
                return PaketPijalok::vratiMasa();
        }
        const void pecati(){
            cout << "Paket sok" << endl;
            cout << "kolicina " << this->getKolicina() << ", so po " << this->getVolumen() * getGustina() << " l(dm3)" << endl;
        }
};

class PaketVino : public PaketPijalok, public ImaMasa{
    private:
        double procentAlkohol;
    public:
        PaketVino(){
            this->procentAlkohol = 0.0;
        }
        PaketVino(const double volumenEden, const int kolicina, const double procentAlkohol) : PaketPijalok(volumenEden, kolicina){
            this->procentAlkohol = procentAlkohol;
        }
        const double vratiMasa(){
            return PaketPijalok::vratiMasa() * (0.9 + this->procentAlkohol);
        }        
        const double getProcentAlkohol(){
            return this->procentAlkohol;
        }
        const void pecati(){
            cout << "Paket vino" << endl;
            cout << "kolicina " << this->getKolicina() << ", " << this->procentAlkohol*100 << "% alkohol od po " << this->getVolumen() * getGustina() << " l(dm3)" << endl;
        }
};

class Kamion{
    private:
        char * registracija;
        char * vozac;
        ImaMasa ** m;
        int brElementi;
        const void copy(const Kamion &orig){
            this->registracija = new char[strlen(orig.registracija)+1];
            this->vozac = new char[strlen(orig.vozac)+1];
            this->m = new ImaMasa *[orig.brElementi + 1];
            this->brElementi = orig.brElementi;
            strcpy(this->registracija, orig.registracija);
            strcpy(this->vozac, orig.vozac);
            for(int i=0; i<this->brElementi; i++)
                this->m[i] = orig.m[i];
        }
    public:
        Kamion(){
            this->registracija = new char[0];
            this->vozac = new char[0];
            this->m = new ImaMasa*[0];
            this->brElementi = 0;
        }
        Kamion(const char * registracija, const char * vozac){
            if(!(isalpha(registracija[0]) && isalpha(registracija[1]) && isalpha(registracija[6]) && isalpha(registracija[7]))){
                throw Exception();
            }   
            this->m = new ImaMasa*[0];
            this->brElementi = 0;
            this->registracija = new char[strlen(registracija)+1];
            this->vozac = new char[strlen(vozac)+1];
            strcpy(this->registracija, registracija);
            strcpy(this->vozac, vozac);
        }
        Kamion(const Kamion &orig){
            this->copy(orig);
        }
        Kamion &operator=(const Kamion &orig){
            if(this != &orig){
                delete [] this->registracija;
                delete [] this->vozac;
                delete [] this->m;
                this->copy(orig);
            }
            return *this;
        }
        ~Kamion(){
            delete [] this->registracija;
            delete [] this->vozac;
            delete [] this->m;
        }
        const void dodadiElement(ImaMasa *orig){
            ImaMasa ** tmp = new ImaMasa*[this->brElementi + 1];
            for(int i=0; i<this->brElementi; i++)
                tmp[i] = this->m[i];
            
            tmp[this->brElementi++] = orig;
            delete [] this->m;
            this->m = tmp;
        }
        const double vratiVkupnaMasa(){
            double total = 0.0;
            for(int i=0; i<this->brElementi; i++)
                total += this->m[i]->vratiMasa();
            return total;
        }
        const void pecati(){
            cout << "Kamion so registracija " << this->registracija << " i vozac " << this->vozac << " prenesuva: " << endl;
            for(int i=0; i<this->brElementi; i++)
                this->m[i]->pecati();
        }
        const Kamion pretovar(const char * registracija, const char *vozac){
            Kamion newTruck(registracija, vozac);
            double max = this->m[0]->vratiMasa();
            int index;
            for(int i=1; i<this->brElementi; i++){
                if(this->m[i]->vratiMasa() > max){
                    max = this->m[i]->vratiMasa();
                    index = i;
                }
            }
            for(int i=0; i<this->brElementi; i++){
                if(i == index)
                    continue;
                newTruck.dodadiElement(this->m[i]);
            }
            return newTruck;
        }
};


int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;
            try{
                cin>>reg;
                cin>>ime;
                Kamion A(reg, ime);
                ImaMasa **d = new ImaMasa*[5];
                cin>>vol>>kol;
                cin>>g;
                d[0] = new PaketSok(vol, kol, g);
                cin>>vol>>kol;
                cin>>proc;
                d[1] = new PaketVino(vol, kol, proc);
                cin>>vol>>kol;
                cin>>proc;
                d[2] = new PaketVino(vol, kol, proc);
                cin>>vol>>kol;
                cin>>g;
                d[3] = new PaketSok(vol, kol, g);
                cin>>vol>>kol;
                cin>>proc;
                d[4] = new PaketVino(vol, kol, proc);

                A.dodadiElement(d[0]);
                A.dodadiElement(d[1]);
                A.dodadiElement(d[2]);
                A.dodadiElement(d[3]);
                A.dodadiElement(d[4]);
                A.pecati();
                cout<<"Vkupna masa: "<<A.vratiVkupnaMasa()<<endl;
                cin>>reg;
                cin>>ime;
                Kamion B = A.pretovar(reg, ime);
                B.pecati();
                cout<<"Vkupna masa: "<<B.vratiVkupnaMasa()<<endl;
            }
        catch(Exception &ex){
            ex.message();
        }
}
