/*Уредување на дом Problem 1 (0 / 0)

Во оваа задача е потребно да уредите даден дом со маси. Креирајте класа Masa со следниве атрибути:

    должина (целобројна вредност)
    ширина (целобројна вредност)

конструктор со и без параметри и метода pecati().

Креирајте класа Soba која содржи:

    маса (објект од класата Маса)
    должина на собата (целобројна вредност)
    ширина на собата (целобројна вредност)

конструктор со и без параметри и метода pecati() во која се повикува и pecati() за објектот Masa.

Креирајте класа Kukja со атрибути:

    соба (објект од класата Soba)
    адреса (низа од 50 знаци), и соодветни методи.

конструктор со и без параметри, деструктор и метода pecati() во која се повикува и pecati() за објектот Soba
*/


#include <iostream>
#include <cstring>

using namespace std;
// class Masa
class Masa {
    private:
        int width;
        int length;
    public:
        Masa(){}
        Masa(int w, int l);
        void pecati();
};

Masa::Masa(int w, int l) {
    this->width = w;
    this->length = l;
}
void Masa::pecati(){
    cout << "Masa: " << width << " " << length << endl;
}
// class Soba
class Soba {
    private:
        int width;
        int length;
        Masa masa;
    public:
        Soba(){}
        Soba(int w, int l, Masa m);
        void pecati();
};

Soba::Soba(int w, int l, Masa m) {
    this->width = w;
    this->length = l;
    this->masa = m;
}

void Soba::pecati(){
    cout << "Soba: " << width << " " << length << " ";
    masa.pecati();
}

// class Kukja
class Kukja {
    private:
        Soba soba;
        char address[50];
    public:
        Kukja(){}
        Kukja(Soba s, const char * adresa);
        void pecati();
};
 
Kukja::Kukja(Soba s, const char * adresa){
    this->soba = s;
    strcpy(this->address, adresa);
}
void Kukja::pecati(){
    cout << "Adresa: " << address << " ";
    soba.pecati();
}
//ne smee da se menuva main funkcijata!
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
    	Masa m(masaSirina,masaDolzina);
    	int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Soba s(sobaSirina,sobaDolzina,m);
    	char adresa[30];
        cin>>adresa;
    	Kukja k(s,adresa);
    	k.pecati();
	}
    
    return 0;
}