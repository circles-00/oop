#include<iostream>
#include<string.h>
using namespace std;

class Delo{
    private:
        char name[50];
        int year;
        char origin[50];
        const void copy_obj(const Delo &orig){
            strcpy(this->name, orig.name);
            this->year = orig.year;
            strcpy(this->origin, orig.origin);
        }
    public:
        Delo(){
            strcpy(this->name, "None");
            this->year = 0;
            strcpy(this->origin, "Uknown");
        }
        Delo(const char * name, const int year, const char * origin){
            strcpy(this->name, name);
            this->year = year;
            strcpy(this->origin, origin);
        }
        Delo(const Delo &orig){
            this->copy_obj(orig);
        }
        Delo &operator=(const Delo &orig){
            if(this != &orig)
                this->copy_obj(orig);
            return *this;
        }
        ~Delo(){}
        bool operator==(Delo &orig){
            return !(strcmp(this->name, orig.name));
        }
        const char * getIme(){
            return this->name;
        }
        const int getYear(){
            return this->year;
        }
        const char * getOrigin(){
            return this->origin;
        }
};

class Pretstava{
    protected:
        Delo d;
        int noSold;
        char data[15];
    public:
        Pretstava(){
            this->noSold = 0;
            strcpy(this->data, "None");
        }
        Pretstava(const Delo d, const int noSold, const char * data){
            this->d = d;
            this->noSold = noSold;
            strcpy(this->data, data);
        }
        ~Pretstava(){}
        virtual const int cena(){
            int n,m;
            int god=d.getYear();
            if(god>1900) m=50;
            else if(god>1800 && god <1900) m=75;
            else m=100;
            
            if(!strcmp(d.getOrigin(),"Rusija"))  n=150;
            else if(!strcmp(d.getOrigin(),"Italija")) n=100;
            else n=80;
        
            return m+n;
        }
        Delo getDelo(){
            return this->d;
        }
        const int getSold(){
            return this->noSold;
        }
};

class Balet : public Pretstava{
    private:
        static int fee;
    public:
        Balet(){}
        Balet(const Delo d, const int noSold, const char * data) : Pretstava(d, noSold, data){}
        ~Balet(){}
        static void setCenaBalet(int newFee){
            fee = newFee;
        }
        const int cena(){
            return Pretstava::cena() + fee;
        }
};
int Balet::fee=150;

class Opera : public Pretstava{
    public:
        Opera(){}
        Opera(const Delo d, const int noSold, const char * data) : Pretstava(d, noSold, data){}
        ~Opera(){}
};

int prihod(Pretstava **p, int n){
    int total = 0.0;
    for(int i=0; i<n; i++)
        total += p[i]->cena() * p[i]->getSold();
    return total;
}

int brojPretstaviNaDelo(Pretstava **p, int n, Delo &d){
    int count = 0;
    for(int i=0; i<n; i++)
        if(p[i]->getDelo() == d)
            count++;
    return count;
}


//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;
    
    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;
        
    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;
    
    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();
        
        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
    
    }break;
    
    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        
        }
        cout<<prihod(pole,n);
    }break;
    
    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;
        
    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        
        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;
    
    };


return 0;
}
