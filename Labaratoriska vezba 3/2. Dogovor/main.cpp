/*Договор Problem 2 (0 / 0)

Да се дефинира класа Potpisuvac во која се чуваат информации за:

    име (низа од максимум 20 знаци)
    презиме (низа од максимум 20 знаци)
    ЕМБГ (низа од максимум 14 знаци)

За класата да се дефинира copy конструктор, default конструктор и конструктор со аргументи.

Да се дефинира класа Dogovor, во која се чуваат информации за:

    број на договор (int),
    категорија на договор (низа од 50 знаци),
    поле од 3 потпишувачи на договорот (објекти од класата Potpisuvac)

Во класата да се додаде метод кој ќе проверува дали постојат два исти потпишувачи (имаат ист ЕМБГ).

*/

#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
	//vasiot kod ovde
    private:
        char name[20];
        char surname[20];
        char embg[14];
	public:
    	Potpisuvac(){}
    	Potpisuvac(const char * ime, const char * prezime, const char * embg);
        Potpisuvac(const Potpisuvac &orig);
        const char * getembg();
};

Potpisuvac::Potpisuvac(const char * ime, const char * prezime, const char * embg){
    strcpy(this->name, ime);
    strcpy(this->surname, prezime);
    strcpy(this->embg, embg);
}
Potpisuvac::Potpisuvac(const Potpisuvac &orig){
    strcpy(this->name, orig.name);
    strcpy(this->surname, orig.surname);
    strcpy(this->embg, orig.embg);
}
const char * Potpisuvac::getembg() {
            return embg;
}
class Dogovor
{
    //vasiot kod ovde
    private:
        int idContract;
        char contractCat[50];
        Potpisuvac array[3];
    public:
        Dogovor(){}
        Dogovor(int broj, const char * kategorija, const Potpisuvac * p);
        bool proverka();
};

Dogovor::Dogovor(int broj, const char * kategorija, const Potpisuvac * p){
    this->idContract=broj;
    strcpy(this->contractCat, kategorija);
    array[0]=p[0];
    array[1]=p[1];
    array[2]=p[2];
}

bool Dogovor::proverka(){
    if((strcmp(this->array[0].getembg(), this->array[1].getembg())==0))
        return true;
    else if((strcmp(this->array[0].getembg(), this->array[2].getembg())==0))
        return true;
    else if((strcmp(this->array[1].getembg(), this->array[2].getembg())==0))
        return true;
    else return false;
}


//ne smee da se menuva main funkcijata
int main()
{
    char embg[13], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p1(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p2(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p3(ime, prezime, embg);
    	cin >> broj >> kategorija;
    	Potpisuvac p[3];
    	p[0] = p1; p[1] = p2; p[2] = p3;
    	Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl; 
    	if(d.proverka() == true)
    	    cout << "Postojat potpishuvaci so ist EMBG" << endl;
    	else
    	    cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}