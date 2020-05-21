/*Репозиториум за оперативни системи Problem 4 (0 / 0)

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

*/

#include <iostream>
#include <cstring>

using namespace std;

enum Tip{LINUX,UNIX,WINDOWS};

class OperativenSistem{
    private:
        char * name;
        float version;
        Tip os;
        float size;
        const void copy(const OperativenSistem &orig){
            this->name = new char[strlen(orig.name)+1];
            strcpy(this->name, orig.name);
            this->version = orig.version;
            this->os = orig.os;
            this->size = orig.size;
        }
    public:
        OperativenSistem(){
            this->name = new char[0];
            this->version = 0.0;
            this->os = UNIX;
            this->size = 0.0;
        }
        OperativenSistem(const char * name, const float version, Tip os, const float size){
            this->name = new char[strlen(name)+1];
            strcpy(this->name, name);
            this->version = version;
            this->os = os;
            this->size = size;
        }
        OperativenSistem(const OperativenSistem &orig){
            this->copy(orig);
        }
        OperativenSistem &operator=(const OperativenSistem &orig){
            if(this != &orig){
                delete [] this->name;
                this->copy(orig);
            }
            return *this;
        }
        ~OperativenSistem(){
            delete [] this->name;
        }
        const void pecati(){
            cout << "Ime: " << this->name << " Verzija: " << this->version << " Tip: " << this->os << " Golemina:" << this->size << "GB" << endl;
        }
        bool ednakviSe(OperativenSistem &os){
            if((strcmp(this->name, os.name)==0) && (this->version == os.version) && (this->os == os.os) && (this->size == os.size))
                    return true;
                else
                    return false;
            }
        int sporediVerzija(const OperativenSistem &os){
            if(this->version == os.version)
                return 0;
            else if(this->version < os.version)
                return -1;
            else
                return 1;
        }
        bool istaFamilija(const OperativenSistem &os){
            if(!(strcmp(this->name, os.name) && this->os == os.os))
                return true;
            else
                return false;
        }
};

class Repozitorium{
    private:
        char name[20];
        OperativenSistem * os;
        int noOs;
    public:
        Repozitorium(){
            this->os = new OperativenSistem[0];
            this->noOs = 0;
        }
        Repozitorium(const char * name){
            strcpy(this->name, name);
            this->os = new OperativenSistem[0];
            this->noOs = 0;
        }
        ~Repozitorium(){
            delete [] this->os;
        }
        const void pecatiOperativniSistemi(){
            cout << "Repozitorium: " << this->name << endl;
            for(int i=0; i<this->noOs; i++)
                this->os[i].pecati();
        }
        const void dodadi(const OperativenSistem &nov){
            for(int i=0; i<this->noOs; i++){
                if((this->os[i].istaFamilija(nov)) && this->os[i].sporediVerzija(nov) == -1){
                    this->os[i] = nov;
                    return ;
                }
            }

            OperativenSistem *tmp = new OperativenSistem[this->noOs + 1];
            for(int i=0; i<this->noOs; i++)
                tmp[i] = this->os[i];
            tmp[this->noOs++] = nov;
            delete [] this->os;
            this->os = new OperativenSistem[this->noOs + 1];
            for(int i=0; i<this->noOs; i++)
                this->os[i] = tmp[i];
        }
        const void izbrishi(OperativenSistem &os){
            int idx = -1;
            for (int i=0;i<this->noOs;i++){
                if (this->os[i].ednakviSe(os)){
                    idx = i;
                    break;
                }
            }
 
            if (idx==-1)
                return ;
    
            OperativenSistem * tmp = new OperativenSistem[this->noOs-1];
            int j=0;
            for (int i=0;i<this->noOs;i++){
                if (i!=idx){
                    tmp[j]=this->os[i];
                    j++;
                }
                else {
                    continue;
                }
            }
    
            this->noOs--;
            delete [] this->os;
            this->os = tmp;
        }
};



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