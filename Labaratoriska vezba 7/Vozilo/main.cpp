/*Возило Problem 3 (0 / 0)

Да се дефинира класа Vozilo која ќе содржи информација за неговата маса (децимален број), ширина и висина (цели броеви).

Од оваа класа да се изведе класата Автомобил во која како дополнителна информација се чува информацијата за бројот на врати (цел број).

Од класата возило да се изведе и класата Автобус во која се чуваат информации и за бројот на патници кои може да ги пренесува.

Од класата возило да се изведе класата Камион во која се чуваат информации и за максималната маса која може да се товари на него (децимална вредност).

За сите класи да се креираат погодни контруктори, како и set и get функции.

Да се дефинира класа ParkingPlac за која се чува динамичко алоцирано поле од покажувачи кон Vozilo, како и бројот на елементи во полето. Во оваа класа да се дефинираат:

    конструктор
    деструктор
    операторот += за додавање на ново возило (аргументот е покажувач кон Vozilo)
    функција float presmetajVkupnaMasa() со која се пресметува вкупната маса на сите возила во паркинг плацот
    функција int brojVozilaPoshirokiOd(int l) со која се пресметува бројот на возила кои се пошироки од дадената вредност
    функција void pecati() со која се печати: Brojot na avtomobili e X, brojot na avtobusi e Y i brojot na kamioni e Z.
    функција int pogolemaNosivostOd(Vozilo& v) во која се враќа бројот на сите камиони кои имаат носивост поголема од масата на возилото предадено како аргумент.

Да се дефинира виртуелна функција int vratiDnevnaCena() во класата Vozilo и истата да се преоптовари во сите изведени класи. За секој автомобил со помалку од 5 врати дневната цена е 100, а инаку е 130 денари. За секој камион цената се пресметува со формулата: (masa+nosivost)*0.02. За секој автобус цената е 5 денари по лице кое може да се пренесува.

Во класата ParkingPlac да се додаде следната функција: - функција int vratiDnevnaZarabotka() со која се враќа дневната заработка од сите возила на паркингот.
*/

#include<iostream>
#include<cstring>
using namespace std;

class Vozilo {
    protected:
        float mass;
        int width;
        int height;
    public:
        Vozilo();
        Vozilo(const float mass, const int width, const int height);
        ~Vozilo();
        virtual int vratiDnevnaCena();
        const float getMass();
        const int getWidth();
};

Vozilo::Vozilo(){
    this->mass = 0.0;
    this->width = 0;
    this->height = 0;
}
Vozilo::Vozilo(const float mass, const int width, const int height){
    this->mass = mass;
    this->width = width;
    this->height = height;
}
Vozilo::~Vozilo(){}
int Vozilo::vratiDnevnaCena(){
    return 0;
}
const float Vozilo::getMass(){
    return this->mass;
}
const int Vozilo::getWidth(){
    return this->width;
}
//Avtomobil
class Avtomobil : public Vozilo{
    private:
        int doors;
    public:
        Avtomobil();
        Avtomobil(const float mass, const int width, const int height, const int doors) : Vozilo(mass, width, height){
            this->doors = doors;
        }
        ~Avtomobil();
        int vratiDnevnaCena();
};
Avtomobil::Avtomobil(){
    this->doors = 0;
}
Avtomobil::~Avtomobil(){}
int Avtomobil::vratiDnevnaCena(){
    if(this->doors < 5)
        return 100;
    else 
        return 130;
}

//Avtobus
class Avtobus : public Vozilo{
    private:
        int passengers;
    public:
        Avtobus();
        Avtobus(const float mass, const int width, const int height, const int passengers) : Vozilo(mass, width, height){
            this->passengers = passengers;
        }
        ~Avtobus();
        int vratiDnevnaCena();
};

Avtobus::Avtobus(){
    this->passengers = 0;
}
Avtobus::~Avtobus(){}
int Avtobus::vratiDnevnaCena(){
    return this->passengers * 5;
}

//Kamion
class Kamion : public Vozilo{
    private:
        float maxMass;
    public:
        Kamion();
        Kamion(const float mass, const int width, const int height, const float maxMass) : Vozilo(mass, width, height){
            this->maxMass = maxMass;    
        }
        ~Kamion();
        int vratiDnevnaCena();
        const float getMaxMass();
};

Kamion::Kamion(){
    this->maxMass = 0.0;
}
Kamion::~Kamion(){}
int Kamion::vratiDnevnaCena(){
    return (this->mass + this->maxMass) * 0.02;
}
const float Kamion::getMaxMass(){
    return this->maxMass;
}
//ParkingPlac
class ParkingPlac{
    private:
        Vozilo ** v;
        int noElements;
    public:
        ParkingPlac();
        ~ParkingPlac();
        ParkingPlac &operator+=(Vozilo * orig){
            Vozilo ** tmp = new Vozilo * [this->noElements + 1];
            for(int i=0; i <this->noElements; i++) {
                tmp[i] = v[i];
            }
            tmp[this->noElements++] = orig;
            //delete [] v;
            v = tmp;
            return *this;
        }
        float presmetajVkupnaMasa();
        int brojVozilaPoshirokiOd(int l);
        void pecati();
        int pogolemaNosivostOd(Vozilo &v);
        int vratiDnevnaZarabotka();
};

ParkingPlac::ParkingPlac(){
    this->v = new Vozilo * [1];
    this->noElements = 0;
}
ParkingPlac::~ParkingPlac(){
   delete [] this->v;
}
float ParkingPlac::presmetajVkupnaMasa(){
    float mass=0.0;
    for(int i=0; i<this->noElements; i++){
        mass += this->v[i]->getMass();
    }
    return mass;
}
int ParkingPlac::brojVozilaPoshirokiOd(int l){
    int count=0;
    for(int i=0; i<this->noElements; i++){
        if(this->v[i]->getWidth() > l)
            count++;
    }
    return count;
}
void ParkingPlac::pecati(){
    int koli = 0; int avtobusi = 0; int kamioni = 0;
    for(int i=0; i<this->noElements; i++){
        Vozilo *a = dynamic_cast<Avtomobil*>(this->v[i]);
        Vozilo *b = dynamic_cast<Avtobus*>(this->v[i]);
        Vozilo *c = dynamic_cast<Kamion*>(this->v[i]);
        if(a)
            koli++;
        if(b)
            avtobusi++;
        if(c)
            kamioni++;
    }
    cout << "Brojot na avtomobili e " << koli << ", brojot na avtobusi e " << avtobusi << " i brojot na kamioni e " << kamioni << "." << endl;
}
int ParkingPlac::pogolemaNosivostOd(Vozilo &v){
    int count = 0;
    for(int i=0; i<this->noElements; i++){
        Kamion * tmp = dynamic_cast<Kamion *>(this->v[i]);
        if(tmp){
            if(tmp->getMaxMass() > v.getMass())
                count++;
        }
    }
    return count;
}
int ParkingPlac::vratiDnevnaZarabotka(){
    int profit = 0;
    for(int i=0; i<this->noElements; i++){
        profit += this->v[i]->vratiDnevnaCena();
    }
    return profit;
}
//main
int main(){
ParkingPlac p;

int n;
cin>>n;
int shirina,visina, broj;
float masa,nosivost;
for (int i=0;i<n;i++){
    int type;
    cin>>type;
    if(type==1){
        cin>>masa>>shirina>>visina>>broj;
        Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
        p+=a;
    }
    if(type==2){
        cin>>masa>>shirina>>visina>>broj;
        p+=new Avtobus(masa,shirina,visina,broj);
    }
    if(type==3){
        cin>>masa>>shirina>>visina>>nosivost;
        p+=new Kamion(masa,shirina,visina,nosivost);
    }
}

p.pecati();

cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
Avtomobil a(1200,4,3,5);
cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
