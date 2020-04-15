/*
Задача 3 Problem 3 (3 / 5)

Да се дефинира класа Pica за која ќе се чуваат податоци за:

    име на пицата (низа од 15 знаци)
    цена (цел број)
    состојки (динамички алоцирана низа од знаци)
    намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.

За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:

    pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
    istiSe(Pica p) - функција за споредба на две пици според состојките :

Да се дефинира класа Picerija во која се чуваат:

    име (низа од максимум 15 знаци)
    динмички алоцирана низа од објекти од класата Pica
    број на пици (цел број)

За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

    dodadi (Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
    void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.



FINKI-Pica
4
Margarita
200
Domaten sos, kaskaval, maslinovo maslo
0
Napolitana 
210
Domaten sos, kaskaval, svezi sampinjoni, maslinovo maslo
0
Kapricioza 
210
Domaten sos, kaskaval, sunka, svezi sampinjoni
30
Vegetarijana
230
Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka
20
Pica-FINKI
Tuna
230
Domaten sos, kaskaval, pcenka, maslinki, tuna, rukola
0*/


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