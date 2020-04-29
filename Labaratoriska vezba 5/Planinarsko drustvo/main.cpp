/*Планинарско друштво Problem 3 (0 / 0)

Да се креира класа за претставување на планинарско друштво во која ќе се чуваат информации за 

името на друштвото 
(динамички алоцирана низа од знаци), број на поминати тури (цел број) и број на членови во планинарското друштво (цел број). 
За оваа класа да се напише:
    оператор + за собирање на две друштва што како резултат враќа друштво со број на членови еднаков на збирот од членовите од двете друштва,
    а останатите атрибути на резултантното друштво ги добиваат вредностите на соодветните атрибути од друштвото со поголем број на членови

    оператори >, < за споредба во однос на бројот на членови во планинарските друштва

    оператор << за печатење на информациите за планинарското друштво

Да се напише функција што на влез прима низа од планинарски друштва и вкупен број на друштва во низата и 
го печати планинарското друштво што има најголем број на членови .
Input:
Vodno
5
100
Korab
7
50
Аурора
2
10
Output:
Ime: Vodno Turi: 5 Clenovi: 150
Najmnogu clenovi ima planinarskoto drustvo: Ime: Vodno Turi: 5 Clenovi: 100
*/
#include <iostream>
#include <cstring>
using namespace std;

class PlDrustvo{
    private:
        char * name;
        int tourscount;
        int memberscount;
    public:
        PlDrustvo(){
            this->name = new char[0];
            strcpy(this->name, "");
            this->tourscount = 0;
            this->memberscount = 0;
        }
        PlDrustvo(const char * ime, const int brTuri, const int brClenovi){
            this->name = new char[strlen(ime)+1];
            strcpy(this->name, ime);
            this->tourscount = brTuri;
            this->memberscount = brClenovi;
        }
        ~PlDrustvo(){
            delete [] this->name;
        }
        PlDrustvo &operator+(PlDrustvo vtoro){
            if(this->memberscount < vtoro.memberscount){
                delete [] this->name;
                this->name = new char[strlen(vtoro.name)+1];
                strcpy(this->name, vtoro.name);
                this->tourscount = vtoro.memberscount;
            }
            this->memberscount += vtoro.memberscount;
            return *this;
        }
};



//main
int main()
{        		
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
   	{
    	char ime[100];
    	int brTuri;
    	int brClenovi;
    	cin>>ime;
    	cin>>brTuri;
    	cin>>brClenovi;
    	PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;
    	
   	}
    
    pl = drustva[0] + drustva[1];
    cout<<pl;   
    
    najmnoguClenovi(drustva, 3);
    
    return 0;
}
