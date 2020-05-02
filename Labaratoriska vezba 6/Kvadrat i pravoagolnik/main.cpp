/*Квадрат и правоаголник Problem 4 (0 / 0)

Да се дефинира класата Kvadrat во која што се чува информација за:

    должината на страната а на квадратот (double)

За класата да се дефинираат:

    default конструктор
    конструктор со аргументи
    copy конструктор
    double perimetar () што пресметува периметар на квадратот
    double plostina () што пресметува плоштина на квадратот
    void pecati () што печати информации за квадратот како во тест примерите

Да се имплементира класа Pravoagolnik што наследува од класата Kvadrat. Во неа се чуваат дополнителни информации за:

    проширувањето x на двете паралелни страни на квадратот (double)
    проширувањето у на другите две паралелни страни (double)

Правоаголникот всушност сега ќе има 2 страни со должина a+x и две страни со должина a+y.

За класата да се дефинираат:

    default конструктор
    конструктор Pravoagolnik (const Kvadrat &k, double x, double y)
    copy конструктор

Да се препокријат трите методи дефинирани погоре за класата Kvadrat.

Напомени:

    Ако x и y се исти, тогаш формата не е правоаголник туку е повторно квадрат. Во тој случај pecati() се повикува исто како за квадрат.
    При препокривање на методите во класата Pravoagolnik мора да има повик кон истоимените методи од класата Kvadrat
*/

#include <iostream>
#include <cstring>

using namespace std;

class Kvadrat {
    protected:
        double a;
    public:
        Kvadrat();
        Kvadrat(const double length);
        Kvadrat(const Kvadrat &orig);
        const double perimetar();
        const double plostina();
        void pecati();
};
Kvadrat::Kvadrat(){
    this->a = 0;
}
Kvadrat::Kvadrat(const double length){
    this->a = length;
}
Kvadrat::Kvadrat(const Kvadrat &orig){
    this->a = orig.a;
}
const double Kvadrat::perimetar(){
    return 4.0 * this->a;
}
const double Kvadrat::plostina(){
    return this->a * this->a;
}
void Kvadrat::pecati(){
    cout << "Kvadrat so dolzina a=" << this->a <<" ima plostina P=" << this->plostina() << " i perimetar L=" << this->perimetar() << endl;
}

//pravoagolnik
class Pravoagolnik : public Kvadrat {
    private:
        double x;
        double y;
    public:
        Pravoagolnik();
        Pravoagolnik (const Kvadrat &k, double x, double y) : Kvadrat(k) {
            this->x = x;
            this->y = y;
        }
        Pravoagolnik(const Pravoagolnik &orig);
        const double perimetar();
        const double plostina();
        void pecati();
};

Pravoagolnik::Pravoagolnik(){
    this-> x = 0;
    this-> y = 0;
}
Pravoagolnik::Pravoagolnik(const Pravoagolnik &orig){
    this->x = orig.x;
    this->y = orig.y;
}
const double Pravoagolnik::perimetar(){
    return (2.0 * (this->a + this->x)) + (2.0 * (this->a + this->y));
}
const double Pravoagolnik::plostina(){
    return (this->a + this->x) * (this->a + this->y);
}
void Pravoagolnik::pecati(){
    if(this->x == this->y){
        this->a += this->x;
        Kvadrat::pecati();
        return;
    }
    cout << "Pravoagolnik so strani: " << this->a + this->x << " i " << this->a + this->y << " ima plostina P=" << this->plostina() << " i perimetar L=" << this->perimetar() << endl;
}



//main
int main() {
	int n;
    double a,x,y;
	Kvadrat * kvadrati;
	Pravoagolnik * pravoagolnici;
	
	cin>>n;
    
    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];
    
	for (int i=0;i<n;i++){
		cin>>a;
        
		kvadrati[i] = Kvadrat(a);
	}
	
	for (int i=0;i<n;i++){
		cin>>x>>y;
        
		pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
	}
	
	int testCase;
	cin>>testCase;
    
	if (testCase==1){
		cout<<"===Testiranje na klasata Kvadrat==="<<endl;
		for (int i=0;i<n;i++)
			kvadrati[i].pecati();
	}
	else {
		cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
		for (int i=0;i<n;i++)
			pravoagolnici[i].pecati();
	}
}