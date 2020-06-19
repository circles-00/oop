#include <iostream>
#include <cstring>

using namespace std;

class SMS{
    private:
        char number[12];
        double price;
    public:
        SMS(){
            this->price = 0.0;
            strcpy(this->number, "N/A");
        }
        SMS(const char * number, const double price){
            strcpy(this->number, number);
            this->price = price;
        }
        virtual ~SMS(){}
        virtual const double SMS_cena(){
            return this->price;
        }
        friend ostream &operator << (ostream &os, SMS &orig){
            os << "Tel: " << orig.number << " - cena: " << orig.SMS_cena() << "den.\n";

            return os;
        }
};

class RegularSMS : public SMS{
    private:
        char msg[1000];
        bool isRoaming;
        static int rProcent;
    public:
        RegularSMS(){
            strcpy(this->msg, "No Message");
            this->isRoaming = false;
        }
        RegularSMS(const char * number, const double price, const char * msg, const bool isRoaming) : SMS(number, price){
            strcpy(this->msg, msg);
            this->isRoaming = isRoaming;            
        }
        ~RegularSMS(){}
        static const void set_rProcent(const int newProcent){
            rProcent = newProcent;
        }
        const double SMS_cena(){
            int length = ((strlen(this->msg)-1)/160) + 1;
            double total = SMS::SMS_cena();
            if(this->isRoaming == true)
                total += total * rProcent/100;
            else
                total += total * 0.18;
            return total * length;
        }
};
int RegularSMS::rProcent = 300;

class SpecialSMS : public SMS{
    private:
        bool isCharity;
        static int sProcent;
    public:
        SpecialSMS(){
            this->isCharity = false;
        }
        SpecialSMS(const char * number, const double price, const bool isCharity) : SMS(number, price){
            this->isCharity = isCharity;
        }
        ~SpecialSMS(){}
        static const void set_sProcent(const int newProcent){
            sProcent = newProcent;
        }
        const double SMS_cena(){
            if(this->isCharity)
                return SMS::SMS_cena();
            else
                return SMS::SMS_cena() + SMS::SMS_cena() * sProcent/100;
        }
};
int SpecialSMS::sProcent = 150;

const void vkupno_SMS(SMS** poraka, int n){
    int regCount = 0; int specCount = 0;
    double regTotal = 0.0; double specTotal = 0.0;
    for(int i=0; i<n; i++){
        RegularSMS *r = dynamic_cast<RegularSMS *>(poraka[i]);
        if(r){
            regCount++;
            regTotal += poraka[i]->SMS_cena();
        }
        SpecialSMS *s = dynamic_cast<SpecialSMS *>(poraka[i]);
        if(s){
            specCount++;
            specTotal += poraka[i]->SMS_cena();
        }
    }
    cout << "Vkupno ima " << regCount << " regularni SMS poraki i nivnata cena e: " << regTotal << "\n";
    cout << "Vkupno ima " << specCount << " specijalni SMS poraki i nivnata cena e: " << specTotal << "\n";
}

int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;
				
				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;	
        SMS *sms1, *sms2;	
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;
        
            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;	
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;
        
        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;	
        SMS *sms1, *sms2;	
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;
        
            cin >> tel;
			cin >> cena;
			cin >> hum;	
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;
        
        delete sms1, sms2;
	}
	
	return 0;
}
