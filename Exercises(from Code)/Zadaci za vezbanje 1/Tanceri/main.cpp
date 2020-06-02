#include <iostream>
#include <cstring>

using namespace std;

struct Tanc{
    char label[15];
    char origin[15];
};

struct Tancer{
    char name[20];
    char surname[20];
    Tanc t[5];
};

const void tancuvanje(Tancer *t, int n, char * zemja){
        for(int i=0; i<n; i++){
            for(int j=0; j<5; j++)
                if(!(strcmp(t[i].t[j].origin, zemja)))
                    cout << t[i].name << " " << t[i].surname << ", " << t[i].t[j].label << "\n";
        }
}

int main()
{
    int i, j, n;
    char zemja[15];
	Tancer tanceri[5];
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> tanceri[i].name;
        cin >> tanceri[i].surname;
        for(j = 0; j < 3; j++){
        	cin >> tanceri[i].t[j].label;
            cin >> tanceri[i].t[j].origin;
        }
    }
    cin >> zemja;
    tancuvanje(tanceri, n, zemja);
	return 0;
}