/*Фабрика Problem 3 (0 / 0)

Креирајте класа Rabotnik која во себе содржи:

    ime (низа од максимум 30 знаци)
    prezime (низа од максимум 30 знаци)
    plata (целобројна вредност)

За оваа класа да се креираат default конструктор и конструктор со аргументи. Да се имплементираат и следните методи:

    getPlata() која ја враќа платата на работникот
    pecati() која ги печати името, презимето и платата.

Креирајте класа Fabrika во која има:

    rabotnik [100] (низа од вработени)
    brojVraboteni (целобројна вредност)

Во класата имплементирајте ги следните методи:

    pecatiVraboteni() ги печати сите вработени
    pecatiSoPlata(int plata) ги печати сите вработени со плата поголема или еднаква на дадената во аргументот (int plata).

Во главната функција се внесуваат податоци за n вработени. Притоа прво се внесува n, па податоците за сите n вработени.
Во последниот ред се чита минималната плата.

На излез да се прикажат прво сите вработени, а потоа само оние со поголема плата од минималната. 
Треба да се корисатат методите pecatiVraboteni и pecatiSoPlata!
*/

#include <iostream>
#include <cstring>

using namespace std;

class Rabotnik{
    private:
        char name[30];
        char surname[30];
        int salary;
    public:
        Rabotnik(){}
        Rabotnik(const char * ime, const char * prezime, int plata);
        int getPlata();
        void pecati();
};

Rabotnik::Rabotnik(const char * ime, const char * prezime, int plata){
    strcpy(this->name, ime);
    strcpy(this->surname, prezime);
    this->salary=plata;
}

int Rabotnik::getPlata(){
    return this->salary;
}

void Rabotnik::pecati(){
    cout << this->name << " " << this->surname << " " << this->getPlata() << endl;
}

//class Fabrika
class Fabrika {
    private:
        Rabotnik array[100];
        int brojVraboteni;
    public:
        Fabrika(){}
        Fabrika(const Rabotnik * r, int n);
        void pecatiVraboteni();
        void pecatiSoPlata(int plata);
};
Fabrika::Fabrika(const Rabotnik * r, int n){
    for(int i=0; i<n; i++){
        this->array[i] = *(r+i);
    }
    this->brojVraboteni=n;
}
void Fabrika::pecatiVraboteni(){
    cout << "Site vraboteni:" << endl;
    for(int i=0; i<this->brojVraboteni; i++){
        this->array[i].pecati();
    }
}

void Fabrika::pecatiSoPlata(int plata){
    cout << "Vraboteni so plata povisoka od " << plata << " :" << endl;
    for(int i=0; i<this->brojVraboteni; i++){
        if((this->array[i].getPlata()) > plata){
            this->array[i].pecati();
        }
           
    }
}

int main(void){
    char name[30], surname[30];
    int salary, minSalary;
    Rabotnik r[100];
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        cin >> name;
        cin >> surname;
        cin >> salary;
        r[i] = Rabotnik(name,surname,salary);
    }

    Fabrika f(r,n);
    cin >> minSalary;
    f.pecatiVraboteni();
    f.pecatiSoPlata(minSalary);

}