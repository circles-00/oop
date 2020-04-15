/*Репозиториум за оперативни системи Problem 4 (2 / 21)

Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:
OperativenSistem

Во класата OperativenSistem треба да се чуваат следниве податоци:

    име на оперативниот систем (динамички алоцирана низа од знаци)
    верзија (float)
    тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
    големина (во GB) (float)

Дополнително, во рамките на класата потребно е да се дефинира:

    конструктори со и без параметри
    copy constructor
    destructor
    преоптоварување на операторот =
    метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
    метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
    метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
    метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)

Repozitorium

Во класата Repozitorium треба да се чуваат следниве податоци:

    име на репозиториумот (низа од 20 знака)
    динамички алоцирана низа од OperativenSistem
    број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)

Дополнително, во рамките на класата потребно е да се дефинира:

    конструктор Repozitorium(const char *ime)
    деструктор
    метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
    метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
    метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
        Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
        Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.

FINKICloud
4
Ubuntu
16.04
1
1.25
Windows
10
3
3.5
Fedora
27
1
2.25
FreeBSD
11
2
1.75
Fedora
25
1
2.25
*/
#include <iostream>
#include <cstring>

enum Tip{LINUX, UNIX, WINDOWS};

using namespace std;

class OperativenSistem{
    private:
        char * name;
        float version;
        Tip t;
        float size;
    public:
        OperativenSistem();
        OperativenSistem(const char * ime, const float verzija, Tip type, const float golemina);
        OperativenSistem(const OperativenSistem &orig);
        OperativenSistem &operator=(const OperativenSistem &orig);
        ~OperativenSistem();
        void pecati();
        bool ednakviSe(const OperativenSistem &os);
        int sporediVerzija(const OperativenSistem &os);
        bool istaFamilija(const OperativenSistem &sporedba);
};

OperativenSistem::OperativenSistem(){
    this->name = new char[0];
    strcpy(this->name, "");
    this->t = (Tip) 0;
    this->version = 0.0;
    this->size = 0.0;
}
OperativenSistem::OperativenSistem(const char * ime, const float verzija, Tip type, const float golemina){
    this->name = new char[strlen(ime)+1];
    strcpy(this->name, ime);
    this->version = verzija;
    this->t = type;
    this->size = golemina;
}
OperativenSistem::OperativenSistem(const OperativenSistem &orig){
    this->name = new char[strlen(orig.name)+1];
    strcpy(this->name, orig.name);
    this->version = orig.version;
    this->t = orig.t;
    this->size = orig.size;
}
OperativenSistem &OperativenSistem::operator=(const OperativenSistem &orig){
    if(this!=&orig){
        delete [] this->name;
        this->name = new char[strlen(orig.name)+1];
        strcpy(this->name, orig.name);
        this->version = orig.version;
        this->t = orig.t;
        this->size = orig.size;
    }
    return *this;
}
OperativenSistem::~OperativenSistem(){
    delete [] this->name;
}
void OperativenSistem::pecati(){
    cout << "Ime: " << this->name << " " << "Verzija: " << this->version << " " << "Tip: " << this->t << " " << "Golemina:" << this->size << "GB" << endl;
}
bool OperativenSistem::ednakviSe(const OperativenSistem &os){
    if((strcmp(this->name, os.name)==0) && (this->version == os.version) && (this->t == os.t) && (this->size == os.size))
        return true;
    else 
        return false;
}
int OperativenSistem::sporediVerzija(const OperativenSistem &os){
    if(this->version == os.version)
        return 0;
    else if(os.version > this->version)
        return -1;
    else
        return 1;
}
bool OperativenSistem::istaFamilija(const OperativenSistem &sporedba){
    if((strcmp(this->name, sporedba.name)==0) && (this->t == sporedba.t))
        return true;
    else 
        return false;
}


//repo
class Repozitorium{
    private:
        char name[20];
        OperativenSistem * os;
        int currentoss;
    public:
        Repozitorium();
        Repozitorium(const char * ime);
        Repozitorium(const Repozitorium &orig);
        Repozitorium &operator=(const Repozitorium &orig);
        ~Repozitorium();
        void pecatiOperativniSistemi();
        void izbrishi(const OperativenSistem &izb);
        void dodadi(const OperativenSistem &nov);
};

Repozitorium::Repozitorium(){
    strcpy(this->name, "");
}
Repozitorium::Repozitorium(const char * ime){
    strcpy(this->name, ime);
    this->os = new OperativenSistem[0];
    this->currentoss = 0;
}
Repozitorium::Repozitorium(const Repozitorium &orig){
    strcpy(this->name, orig.name);
    this->currentoss = orig.currentoss;
    this->os = new OperativenSistem[currentoss];
    for(int i=0; i<currentoss; i++)
        this->os[i] = orig.os[i];
}
Repozitorium &Repozitorium::operator=(const Repozitorium &orig){
    if(this!=&orig){
        delete this->os;
        strcpy(this->name, orig.name);
        this->currentoss = orig.currentoss;
        this->os = new OperativenSistem[currentoss];
        for(int i=0; i<currentoss; i++)
            this->os[i] = orig.os[i];
    }
    return *this;
}
Repozitorium::~Repozitorium(){
    delete [] this->os;
}
void Repozitorium::pecatiOperativniSistemi(){
    cout << "Repozitorium: " << this->name << endl;
    for(int i=0; i<currentoss; i++){
        this->os[i].pecati();
    }
}
void Repozitorium::izbrishi(const OperativenSistem &izb){
    //naogjanje na indeksot na sistemot so treba da se brishe
        int idx = -1;
        for (int i=0;i<currentoss;i++){
            if (os[i].ednakviSe(izb)){
                idx = i;
                break;
            }
        }
 
        if (idx==-1)
            return ;
 
        OperativenSistem * tmp = new OperativenSistem[currentoss-1];
        int j=0;
        for (int i=0;i<currentoss;i++){
            if (i!=idx){
                tmp[j]=os[i];
                j++;
            }
            else {
                continue;
            }
        }
 
        currentoss--;
        delete [] os;
        os = tmp;
}
void Repozitorium::dodadi(const OperativenSistem &nov){
    for(int i=0; i<currentoss; i++){
        if(this->os[i].istaFamilija(nov) && this->os[i].sporediVerzija(nov)==-1){
            this->os[i] = nov;
            return ;
        }
    }
    OperativenSistem * temp = new OperativenSistem[currentoss+1];
    for(int j=0; j<currentoss; j++){
        temp[j] = this->os[j];
    }

    temp[currentoss++] = nov;
    delete [] this->os;
    this->os = new OperativenSistem[currentoss];
    for(int i=0; i<currentoss; i++)
        this->os[i] = temp[i];
}
//main
int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}