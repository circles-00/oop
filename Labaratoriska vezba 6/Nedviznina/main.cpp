/*Недвижнина Problem 1 (0 / 0)

Да се развие класа Nediviznina за коjа се чуваат следниве информации:

    адреса (динамички алоцирана низа од знаци)
    квадратура (цел боj)
    цена за квадрат (цел боj)

За оваа класа да се имплементираат соодветните конструктори и следните методи:

    cena() коj ќе jа враќа цената на недвижнината (квадратура * цена-за-квадрат)
    pecati() коj ќе ги испечати сите информации за истата
    danokNaImot() коj го ваќа данокот што се плаќа за недвижнината, а истиот се пресметува како 5% од цената на недвижнината.

Од оваа класа да се изведе класа Vila за коjа дополнително се чува данок на луксуз (цел боj, пр. 10%). За оваа класа да се преоптоварат 
методите:

    pecati()
    danokNaImot() со тоа што пресметаниот данок се зголемува процентуално за данокот на луксуз.

И за двете класи треба да се преоптовари operator >>.
*/

#include <iostream>
#include <cstring>

using namespace std;

class Nedviznina{
    private:
        char * address;
        int area;
        int price;
    public:
        Nedviznina();
        ~Nedviznina();
        int cena();
        void pecati();
        float danokNaImot();
        const char * getAdresa();
        const int getArea();
        const int getPrice();
        void setaddress(const char * adresa);
        void setarea(const int kvadratura);
        void setprice(const int cena);
        friend istream & operator >> (istream &input,  Nedviznina &orig){
            char temp[25];
            input >> temp;
            delete [] orig.address;
            orig.address = new char[strlen(temp)+1];
            strcpy(orig.address, temp);
            input >> orig.area >> orig.price;

            return input;
        }
};

Nedviznina::Nedviznina(){
    this->address = new char[0];
    strcpy(this->address, "");
    this->area = 0;
    this-> price = 0;
}
Nedviznina::~Nedviznina(){
    delete [] this->address;
}
int Nedviznina::cena(){
    return this->area * this->price;
}
void Nedviznina::pecati(){
    cout << this->address << ", Kvadratura: " << this->area << ", Cena po Kvadrat: " << this->price << endl;
}
float Nedviznina::danokNaImot(){
    return ((this->area * this->price)*5)/100.0;
}
const char * Nedviznina::getAdresa(){
    return this->address;
}
const int Nedviznina::getArea(){
    return this->area;
}
const int Nedviznina::getPrice(){
    return this->price;
}
void Nedviznina::setaddress(const char * adresa){
    delete [] this->address;
    this->address = new char[strlen(adresa)+1];
    strcpy(this->address, adresa);
}
void Nedviznina::setarea(const int kvadratura){
    this->area = kvadratura;
}
void Nedviznina::setprice(const int cena){
    this->price = cena;
}

class Vila: public Nedviznina{
    private:
        int luxurytax;
    public:
        Vila();
        ~Vila();
        void pecati();
        float danokNaImot();
        friend istream & operator >> (istream &input,  Vila &orig){
            char adresa[25];
            int area;
            int cena;
            input >> adresa >> area >> cena >> orig.luxurytax;
            orig.setaddress(adresa);
            orig.setarea(area);
            orig.setprice(cena);

            return input;
        }
};

Vila::Vila(){
    this->luxurytax = 0;
}
Vila::~Vila(){}
void Vila::pecati(){
    cout << this->getAdresa() << ", Kvadratura: " << this->getArea() << ", Cena po Kvadrat: " << this->getPrice() << ", Danok na luksuz: " << this->luxurytax << endl;
}
float Vila::danokNaImot(){
    return (((this->getArea() * this->getPrice())*5)/100.0) + (((this->getArea() * this->getPrice())*this->luxurytax)/100.0);
}

//main
int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}