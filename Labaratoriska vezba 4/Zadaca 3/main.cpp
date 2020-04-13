#include <iostream>
#include <cstring>
 
using namespace std;
 
//Vasiot kod tuka
 
class Pica{
private:
   
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje=0;
   
public:
   
    Pica(char* ime="",int cena=0,char* sostojki="",int namaluvanje=0){
        strncpy(this->ime,ime,15);
        this->cena=cena;
        this->namaluvanje=namaluvanje;
        this->sostojki=new char [strlen(sostojki)+1];
        strcpy(this->sostojki,sostojki);
    }
   
    Pica(const Pica &p){
        strncpy(this->ime,p.ime,15);
        this->cena=p.cena;
        this->namaluvanje=p.namaluvanje;
        this->sostojki=new char [strlen(p.sostojki)+1];
        strcpy(this->sostojki,p.sostojki);
    }
   
    Pica& operator=(const Pica& p){
        if(this!=&p){
            strncpy(this->ime,p.ime,15);
            this->cena=p.cena;
            this->namaluvanje=p.namaluvanje;
            this->sostojki=new char [strlen(p.sostojki)+1];
            strcpy(this->sostojki,p.sostojki);
        }
        return *this;
    }
   
    ~Pica(){
        delete [] sostojki;
    }
   
    void pecati(){
        cout<<ime<<" - "<<sostojki<<", "<<cena<<" ";
        if(namaluvanje>0&&namaluvanje<=100){
            cout<<cena-cena*namaluvanje/100<<endl;
        }
    }
   
    bool istiSe(Pica &p){
        if(strcmp(this->sostojki,p.sostojki)==0) return true;
        else return false;
    }
   
    char* getSostojki(){
        return sostojki;
    }
   
    int getNamaluvanje(){
        return namaluvanje;
    }
   
};
 
class Picerija{
private:
    char ime[15];
    Pica *pici;
    int brojPici;
public:
    Picerija(){}
   
    Picerija(char *ime){
        strncpy(this->ime,ime,15);
        pici=new Pica [0];
        brojPici=0;
    }
   
    Picerija(const Picerija& p){
        strncpy(this->ime,p.ime,15);
        this->brojPici=p.brojPici;
        this->pici=new Pica [brojPici];
        for(int i=0;i<brojPici;i++){
            this->pici[i]=p.pici[i];
        }
    }
   
    ~Picerija(){
        delete [] pici;
    }
   
    void dodadi(Pica &p){
        int flag=0;
        for(int i=0;i<brojPici;i++){
            if(strcmp(this->pici[i].getSostojki(),p.getSostojki())==0){
                flag=1;
            }
        }
        if(flag==0){
            Pica *tmp=new Pica[brojPici];
            for(int i=0;i<brojPici;i++){
                tmp[i]=this->pici[i];
            }
            delete [] this->pici;
            this->pici=new Pica[brojPici+1];
            for(int i=0;i<brojPici;i++){
                this->pici[i]=tmp[i];
            }
            this->pici[brojPici]=p;
            delete [] tmp;
            brojPici++;
        }
    }
   
    char* getIme(){
        return this->ime;
    }
   
    void piciNaPromocija(){
        for(int i=0;i<brojPici;i++){
            if((this->pici[i].getNamaluvanje())!=0){
                this->pici[i].pecati();
            }
        }
    }
   
    void setIme(char* ime){
        strncpy(this->ime,ime,15);
    }
   
   
};
 
int main () {
 
    int n;
    char ime[15];
    cin >> ime;
    cin >> n;
 
    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }
 
    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);
 
    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();
 
    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();
 
    return 0;
   
}