#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;
class NegativnaVrednost{
    private:
        char mesg[100];
    public:
        NegativnaVrednost(const char * msg){
            strcpy(this->mesg, msg);
        }
        const void msg(){
            cout << this->mesg << "\n";
        }
};
class Oglas{
    private:
        char title[50];
        char desc[100];
        char category[30];
        double price;
    public:
        Oglas(){
            strcpy(this->title, "Uknown");
            strcpy(this->desc, "None");
            strcpy(this->category, "Uncategorized");
            this->price = 0.0;
        }
        Oglas(const char * title, const char * category, const char * desc, const double price){
            strcpy(this->title, title);
            strcpy(this->category, category);
            strcpy(this->desc, desc);
            this->price = price;
        }
        bool operator>(Oglas &orig){
            if(this->price > orig.price)
                return true;
            else
                return false;
        }
        friend ostream & operator<<(ostream &os, const Oglas &orig){
            os << orig.title << "\n";
            os << orig.desc << "\n";
            os << orig.price << " evra" <<"\n";
            return os;            
        }
        const double getPrice(){
            return this->price;
        }
        const char * getCat(){
            return this->category;
        }
};

class Oglasnik{
    private:
        char name[20];
        Oglas * og;
        int noOglasi;
        const void copy_obj(const Oglasnik &orig){
            strcpy(this->name, orig.name);
            this->noOglasi = orig.noOglasi;
            this->og = new Oglas[orig.noOglasi + 1];
            for(int i=0; i<orig.noOglasi; ++i)
                this->og[i] = orig.og[i];
        }
    public:
        Oglasnik(){
            strcpy(this->name, "Unknown");
            this->og = new Oglas[0];
            this->noOglasi = 0;
        }
        Oglasnik(const char * name){
            strcpy(this->name, name);
            this->og = new Oglas[0];
            this->noOglasi = 0;
        }
        Oglasnik &operator=(const Oglasnik &orig){
            if(this != &orig){
                delete [] this->og;
                this->copy_obj(orig);
            }
            return *this;
        }
        Oglasnik(const Oglasnik &orig){
            this->copy_obj(orig);
        }
        Oglasnik &operator += (Oglas &orig){
            if(orig.getPrice() < 0)
                throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
            Oglas *tmp = new Oglas[this->noOglasi + 1];
            for(int i=0; i<this->noOglasi; ++i)
                tmp[i] = this->og[i];
            tmp[this->noOglasi++] = orig;
            delete [] this->og;
            this->og = tmp;

            return *this;
        }
        friend ostream & operator<<(ostream &os, const Oglasnik &orig){
            os << orig.name << "\n";
            for(int i=0; i<orig.noOglasi; ++i)
                cout << orig.og[i] << "\n";
            return os;
        }
        void oglasiOdKategorija(const char *k){
            for(int i=0; i<this->noOglasi; ++i){
                if(strcmp(this->og[i].getCat(), k) == 0)
                    cout << this->og[i];
            }
        }
        void najniskaCena(){
            Oglas min = this->og[0];
            int minindex = 0;
            for(int i=0; i<this->noOglasi; ++i){
                if(min > this->og[i]){
                    min = this->og[i];
                    minindex = i;
                }
            }
        }
};


int main(){
    
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;
    
    int tip;
    cin>>tip;
    try {
        if (tip==1){
            cout<<"-----Test Oglas & operator <<-----" <<endl;
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            cout<<o;
        }
        else if (tip==2){
            cout<<"-----Test Oglas & operator > -----" <<endl;
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o1(naslov, kategorija, opis, cena);
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o2(naslov, kategorija, opis, cena);
            if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
            else cout<<"Prviot oglas ne e poskap."<<endl;    
        }
        else if (tip==3){
            cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
            cin.get();
            cin.getline(naziv,49);
            cin>>n;
            Oglasnik ogl(naziv);
            for (int i = 0; i < n; i++){
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            cout<<ogl;
        }
        else if (tip==4){
            cout<<"-----Test oglasOdKategorija -----" <<endl ;
            cin.get();
            cin.getline(naziv,49);
            cin>>n;
            Oglasnik ogl(naziv);
            for (int i = 0; i < n; i++){
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            cin.get();
            cin.getline(k,29);
            cout<<"Oglasi od kategorijata: " <<k<<endl;
            ogl.oglasiOdKategorija(k);
        
        }
        else if (tip==5){
            cout<<"-----Test Exception -----" <<endl ;
            cin.get();
            cin.getline(naziv,49);
            cin>>n;
            Oglasnik ogl(naziv);
            for (int i = 0; i < n; i++){
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);            
                ogl+=o;
            }
            cout<<ogl;
        
        }
        else if (tip==6){
            cout<<"-----Test najniskaCena -----" <<endl ;
            cin.get();
            cin.getline(naziv,49);
            cin>>n;
            Oglasnik ogl(naziv);
            for (int i = 0; i < n; i++){
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);            
                ogl+=o;            
            }
            cout<<"Oglas so najniska cena:"<<endl;
            ogl.najniskaCena();
        
        }
        else if (tip==7){
            cout<<"-----Test All -----" <<endl ;
            cin.get();
            cin.getline(naziv,49);
            cin>>n;
            Oglasnik ogl(naziv);
            for (int i = 0; i < n; i++){
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);            
                ogl+=o;
            }
            cout<<ogl;
            
            cin.get();
            cin.get();
            cin.getline(k,29);
            cout<<"Oglasi od kategorijata: " <<k<<endl;
            ogl.oglasiOdKategorija(k);
            
            cout<<"Oglas so najniska cena:"<<endl;
            ogl.najniskaCena();
        
        }
    }
    catch (NegativnaVrednost &ex){
        ex.msg();
    }
    
	return 0;
}
