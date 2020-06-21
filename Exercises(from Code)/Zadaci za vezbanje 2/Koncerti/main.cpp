#include<iostream>
#include<string.h>
using namespace std;

class Koncert{
    private:
        char title[20];
        char location[20];
        static float sale;
        float price;
        const void copy_obj(const Koncert &orig){
            strcpy(this->title, orig.title);
            strcpy(this->location, orig.location);
            this->price = orig.price;
        }
    public:
        Koncert(){
            strcpy(this->title, "Uknown");
            strcpy(this->location, "None");
            this->price = 0.0;
        }
        Koncert(const char * title, const char * location, const float price){
            strcpy(this->title, title);
            strcpy(this->location, location);
            this->price = price;
        }
        Koncert(const Koncert &orig){
            this->copy_obj(orig);
        }
        Koncert &operator=(const Koncert &orig){
            if(this != &orig)
                this->copy_obj(orig);
            return *this;
        }
        static void setSezonskiPopust(const float newSale){
            sale = newSale;
        }
        static float getSezonskiPopust(){
            return sale;
        }
        virtual const float cena(){
            return this->price - this->price * sale;
        }
        const char * getNaziv(){
            return this->title;
        }
        const char * getTitle(){
            return this->title;
        }
};

float Koncert::sale = 0.2;

class ElektronskiKoncert : public Koncert{
    private:
        char * DJ;
        float length;
        bool time;
        const void copy_obj(const ElektronskiKoncert &orig){
            this->DJ = new char[strlen(orig.DJ)+1];
            strcpy(this->DJ, orig.DJ);
            this->length = orig.length;
            this->time = orig.time;
        }
    public:
        ElektronskiKoncert(){
            this->DJ = new char[0];
            this->length = 0;
            this->time = false;
        }
        ElektronskiKoncert(const char * title, const char * location, const float price, const char * DJ, const float length, const bool time) : Koncert(title, location, price){
            this->DJ = new char[strlen(DJ) + 1];
            strcpy(this->DJ, DJ);
            this->length = length;
            this->time = time;
        }
        ElektronskiKoncert(const ElektronskiKoncert &orig) : Koncert(orig){
            this->copy_obj(orig);
        }
        ElektronskiKoncert &operator=(const ElektronskiKoncert &orig){
            if(this != &orig){
                delete [] this->DJ;
                Koncert::operator=(orig);
                this->copy_obj(orig);
            }
            return *this;
        }
        ~ElektronskiKoncert(){
            delete [] this->DJ;
        }
        const float cena(){
            float price = Koncert::cena();
            if(this->length > 5 && this->length < 7)
                price += 150;
            else if(this->length > 7)
                price += 360;
            if(this->time == true)
                price -= 50;
            else
                price += 100;

            return price;
        }
};

 void najskapKoncert(Koncert ** koncerti, int n){
     float max = koncerti[0]->cena();
     int index = 0;
     int count = 0;
     for(int i=1; i<n; i++){
         if(max < koncerti[i]->cena()){
            max = koncerti[i]->cena();
            index = i;
         }
        ElektronskiKoncert *tmp = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if(tmp)
            count++;
     }
     cout << "Najskap koncert: " << koncerti[index]->getTitle() << " " << koncerti[index]->cena() << "\n";
     cout << "Elektronski koncerti: " << count << " od vkupno " << n << "\n";
 }

 bool prebarajKoncert(Koncert ** koncerti, int n, const char * naziv, bool elektronski){
    if(elektronski == true){    
        for(int i=0; i<n; i++){
            ElektronskiKoncert *tmp = dynamic_cast <ElektronskiKoncert *>(koncerti[i]);
            if(tmp){
                if(strcmp(koncerti[i]->getTitle(), naziv) == 0){
                    cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<"\n";
                    return true;
                }
            }       
        }
    }
    else{
        for(int i=0; i<n; i++){
            if(strcmp(koncerti[i]->getTitle(), naziv) == 0){
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<"\n";
                return true;
            }
        }
    }
    return false;
 }

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}
