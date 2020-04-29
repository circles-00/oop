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
        Nedviznina(){}
};

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