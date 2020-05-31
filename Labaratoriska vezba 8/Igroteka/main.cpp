/*Игротека Problem 2 (0 / 0)

Во една игротека има 2 типа играчки: топки и коцки. Коцките и топките се опишани со параметри како што се:

    боја (char *)
    густина (int).

Дополнително за топките се знае и радиусот (int), додека за коцките целосните димензии (висина, ширина и длабочина – int).

За секоја од класите треба да се дефинираат методи getMasa() и getVolumen(). Масата на играчката се пресметува како производ од волуменот и густината на играчката. За PI користете ја вредноста 3.14.

Во функцијата main да се декларира променлива kupche што претставува динамички алоцирана низа кон Igrachka. Во зависност од првиот влезен параметар се внесуваат објекти од класите Topka или Kocka (1 - се внесува топка, 2 - се внесува коцка).

Од тастатура да се внесат податоци за коцката на Петра Kocka petra. Во главната функција во да се отпечатат:

    Да се отпечати DA ако вкупната маса на сите играчки е поголема од масата на играчката на Петра, а NE во спротивно.

    Разликата по апсолутна вредност на волуменот на играчката со максимален волумен во купчето и волуменот на коцката на Петра. Форматот е:

    Razlikata e: {razlika}

Задачата да се реши со тоа што класите Kocka и Topka ќе наследуваат од класите Forma и Igrachka.

Дополнителни барања:

    Во класата Igrachka да се додаде уште една чисто виртуелна функција float getPlostina(). Истата да се имплементира во класите Kocka и Topka
    Во главната функција, дополнително да се испечати и: Разликата по апсолутна вредност на плоштината на играчката со минимална плоштина во купчето и плоштината на коцката на Петра во истиот формат како и второто барање погоре.

*/
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    virtual float getPlostina() = 0;
};

class Forma{
protected:
    char boja[100];
    int gustina;
public:
    Forma(){
        strcpy(this->boja, "None");
        this->gustina = 0;
    }
    Forma(const char * boja, const int gustina){
        strcpy(this->boja, boja);
        this->gustina = gustina;
    }
    ~Forma(){}
    float getVolumen(){
        return 0;
    }
    float getMasa(){
        return 0;
    }
    float getPlostina(){
        return 0;
    }
};

class Kocka : public Forma, public Igrachka{
    private:
        int visina;
        int sirina;
        int dlabocina;
    public:
        Kocka(){
            this->visina = 0;
            this->sirina =0;
            this->dlabocina = 0;
        }
        Kocka(const char * boja, const int gustina, const int visina, const int sirina, const int dlabocina) : Forma(boja, gustina){
            this->visina = visina;
            this->sirina = sirina;
            this->dlabocina = dlabocina;
        }
        ~Kocka(){}
        float getVolumen(){
            return this->visina * this->sirina * this->dlabocina;
        }
        float getMasa(){
            return this->getVolumen() * this->gustina;
        }
        float getPlostina(){
            return 2*(this->dlabocina*this->sirina + this->dlabocina*this->visina + this->sirina*this->visina);
        }
};

class Topka : public Forma, public Igrachka{
    private:
        int radius;
    public:
        Topka(){
            this->radius = 0;
        }
        Topka(const char * boja, const int gustina, const int radius) : Forma(boja, gustina){
            this->radius = radius;
        }
        ~Topka(){}
        float getVolumen(){
            return 4./3*3.14*radius*radius*radius;
        }
        float getMasa(){
            return this->getVolumen() * this->gustina;
        }
        float getPlostina(){
            return this->getVolumen()*gustina;
        }
};



int main(){
	//vnesi informacii za kupche
    int n, type, gustina, visina, sirina, dlabocina, radius;
    cin >> n;
    Igrachka ** kupche = new Igrachka*[n];
    char boja[50];

    for(int i=0; i<n; i++){
        cin >> type;
        if(type == 1){
            cin >> boja >> gustina >> radius;
            kupche[i] = new Topka(boja, gustina, radius);
        }
        else if(type == 2){
            cin >> boja >> gustina >> visina >> sirina >> dlabocina;
            kupche[i] = new Kocka(boja, gustina, visina, sirina, dlabocina);
        } 
    }
    //vnesi informacii za igrachkata na Petra
    cin >> boja >> gustina >> visina >> sirina >> dlabocina;
    Kocka petra(boja, gustina, visina, sirina, dlabocina);
	//baranje 1
    float total = 0.0;
    for(int i=0; i<n; i++){
        total += kupche[i]->getMasa();
    }

    if(total > petra.getMasa())
        cout << "DA" << endl;
    else
        cout << "NE" << endl;

	//baranje 2
    double max = kupche[0]->getVolumen();
    double min = kupche[0]->getPlostina();
    for(int i=1; i<n; i++){
        if(max < kupche[i]->getVolumen())
            max = kupche[i]->getVolumen();
        if(min > kupche[i]->getPlostina())
            min = kupche[i]->getPlostina();
    }
    cout << "Razlikata e: " << fabs(max - petra.getVolumen()) << endl;
    //дополнително барање 2
    cout << "Razlikata e: " << fabs(min - petra.getPlostina()) << endl;
	return 0;
}