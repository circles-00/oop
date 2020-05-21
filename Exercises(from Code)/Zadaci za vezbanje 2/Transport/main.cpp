/*Транспорт Problem 1 (0 / 0)

Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

    конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
    метод cenaTransport, за пресметување на цената на понудата на следниот начин:
        За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
        За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
    преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)

Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)
*/
#include <iostream>
#include <cstring>

using namespace std;

class Transport{
    protected:
        char * destination;
        int price;
        int km;
        const void copy(const Transport &orig){
            this->destination = new char[strlen(orig.destination)+1];
            strcpy(this->destination, orig.destination);
            this->price = orig.price;
            this->km = orig.km;
        }
    public:
        Transport(){
            this->destination = new char[0];
            this->price = 0;
            this->km = 0;
        }
        Transport(const char * destination, const int price, const int km){
            this->destination = new char[strlen(destination)+1];
            strcpy(this->destination, destination);
            this->price = price;
            this->km = km;
        }
        Transport(const Transport &orig){
            this->copy(orig);
        }
        Transport &operator=(const Transport &orig){
            if(this != &orig){
                delete [] this->destination;
                this->copy(orig);
            }
            return *this;
        }
        ~Transport(){
            delete [] this->destination;
        }
        virtual double cenaTransport(){
            return this->price;
        }
        bool operator<(const Transport &orig){
            if(this->km < orig.km)
                return true;
            else
                return false;
        }
        const int getKm(){
            return this->km;
        }
        const char * getDest(){
            return this->destination;
        }
};

class AvtomobilTransport : public Transport{
    private:
        bool platen;
    public:
        AvtomobilTransport(){
            this->platen = false;
        }
        AvtomobilTransport(const char * destination, const int price, const int km, const bool platen) : Transport(destination, price, km){
            this->platen = platen;
        }
        ~AvtomobilTransport(){}
        double cenaTransport(){
            if(this->platen)
                return this->price + (this->price * 0.2);
            else
                return this->price;
        }      
};

class KombeTransport : public Transport{
    private:
        int lugje;
    public:
        KombeTransport(){
            this->lugje = 0;
        }
        KombeTransport(const char * destination, const int price, const int km, const int lugje) : Transport(destination, price, km){
            this->lugje = lugje;
        }
        ~KombeTransport(){}
        double cenaTransport(){
            return this->price - (200 * this->lugje);
        }
};

const void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport ponuda){
   //sort
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(ponudi[i]->getKm() > ponudi[j]->getKm()){
                Transport *tmp = ponudi[i];
                ponudi[i] = ponudi[j];
                ponudi[j] = tmp;
            }
        }
    }


   for(int i=0; i<n; i++){   
       if(ponudi[i]->cenaTransport() > ponuda.cenaTransport())
            cout << ponudi[i]->getDest() << " " << ponudi[i]->getKm() << " " << ponudi[i]->cenaTransport() << endl;
   }
}

//main
int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
