/*Тајни пораки Problem 5 (0 / 0)

Да се имплементира апстрактна класа Secret со два чисто виртуелни методи:

    double simpleEntropy() - се пресеметува како бројот на уникатни (цифри/букви) поделен со бројот на вкупно знаци. (2 поени)
    int total()- го враќа вкупниот број на цифри/букви. (1 поени)

Од оваа класа да се имплементираат две изведени класи DigitSecret (цифри 0-9) и CharSecret (букви a-z) во кои се чува низа од максимум 100 цифри односно 100 мали букви од a до z (1 поени).

Да се имплементира соодветен конструктор, како и следните оператори:

    оператори== и != за споредување на два објекти од каков било тип (DigitSecret,CharSecret) според елементите што ги содржат (1 поени)
    оператор << за печатење на стандарден излез во формат: (1 поени)

[cifri/bukvi] Simple entropy: [entropy] Total: [total]

Да се имплементираaт методите:

    void process(Secret **secrets, int n) - што прима низа од покажувачи од класата Secret и нивниот број и треба да го отпечати елементот со најголема вредност за simpleEntropy. (3 поени)
    void printAll(Secret **secrets, int n) - што прима исти аргументи како претходниот и треба да ги испечати сите елементи во низата secrets. (1 поен)

*/
#include<iostream>
#include<cstring>

using namespace std;

class Secret{
    public:
        virtual const int total() = 0;
        virtual const double simpleEntropy() = 0;
        bool operator==(Secret &orig){
        if((simpleEntropy() == orig.simpleEntropy())&&(total() == orig.total())){
            return true;
        }
        else
           return false;    
        }
        bool operator!=(Secret &orig){
         if((simpleEntropy() == orig.simpleEntropy())&&(total() == orig.total())){
            return false;
        }
        else
            return true;   
    }
};

class DigitSecret : public Secret{
    private:
        int cifri[100];
        int noElements;
    public:
        DigitSecret(){
            this->noElements = 0;
        }
        DigitSecret(const int * cifri, const int noElements){
            for(int i=0; i<100; i++)
                this->cifri[i] = cifri[i];
            this->noElements = noElements;
        }
        const int total(){
            return this->noElements;
        }
        const double simpleEntropy(){
            int unique = 0; int temp = 0;
            for(int i=0; i<this->noElements; i++){
                temp = 0;
                for(int j=0; j<this->noElements; j++){
                    if(this->cifri[i] == this->cifri[j])
                        temp++;
                }
                if(temp == 1)
                    unique++;
            }
            return double (unique) / this->total();
        }
    
        friend ostream & operator<<(ostream &os, DigitSecret &orig){
            for(int i=0; i<orig.noElements; i++)
                os << orig.cifri[i];
            os << " Simple entropy: " << orig.simpleEntropy() << " Total: " << orig.total();

            return os;
        }
};

class CharSecret : public Secret {
    private:
        char chars[100]; 
    public:
        CharSecret(){}
        CharSecret(const char * chars){
            strcpy(this->chars, chars);
        }
        const int total(){
            return strlen(this->chars);
        }
        const double simpleEntropy(){
            int unique = 0; int temp = 0;
            for(int i=0; i<this->total(); i++){
                temp = 0;
                for(int j=0; j<this->total(); j++){
                    if(this->chars[i] == this->chars[j])
                        temp++;
                }
                if(temp == 1)
                    unique++;
            }
            return double (unique) / this->total();
        }

        friend ostream &operator<<(ostream &os, CharSecret &orig){
            for(int i=0; i<orig.total(); i++)
                os << orig.chars[i];
            cout << " Simple entropy: " << orig.simpleEntropy() << " Total: " << orig.total();    
            return os;
        }
};

void process(Secret **secrets, int n){
    int maxIndex = 0;
    double max = secrets[0]->simpleEntropy();
    for(int i=0; i<n; i++){
        if(secrets[i]->simpleEntropy() > max){
            max = secrets[i]->simpleEntropy();
            maxIndex = i;
        }
    }
    DigitSecret * ds = dynamic_cast<DigitSecret *>(secrets[maxIndex]);
    if(ds)
        cout << (*ds);
    else{
        CharSecret * cs = dynamic_cast<CharSecret *>(secrets[maxIndex]);
        cout << (*cs);
    }
}

void printAll(Secret **secrets, int n){
        for(int i = 0; i<n; i++){
            CharSecret *cs = dynamic_cast<CharSecret *>(secrets[i]);
            if(cs)
                cout << (*cs) << endl;
            else{
            DigitSecret *ds = dynamic_cast<DigitSecret *>(secrets[i]);
                cout << (*ds) << endl;
            }
    }
}



int main() {
    int n;
    cin >> n;
    if(n == 0) {
		cout << "Constructors" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
  		cout << "operator <<" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
  		cout << "== and !=" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
  		cout << "Secret processor" << endl;
		int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
		int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }
    
    return 0;
}