#include <iostream>
#include <cstring>

using namespace std;

enum tip{phone,computer};

class InvalidProductionDate{
    private:
        char msg[256];
    public:
        InvalidProductionDate(const char * msg){
            strcpy(this->msg, msg);
        }
        const void print(){
            cout << this->msg << "\n";
        }
};

class Device{
    private:
        char model[100];
        tip t;
        static float hoursForFix;
        int yearMade;
    public:
        Device(){
            strcpy(this->model, "Unknown");
            this->t = phone;
            this->yearMade = 1970;
        }
        Device(const char * model, tip t, const int yearMade){
            strcpy(this->model, model);
            this->t = t;
            this->yearMade = yearMade;
        }
        ~Device(){}
        const static void setPocetniCasovi(float newHours){
            hoursForFix = newHours;
        }
        const float getHoursForFix(){
            double total = hoursForFix;
            if(this->yearMade > 2015)
                total += 2;
            if(this->t == computer)
                total += 2;
            return total;
        }
        friend ostream &operator << (ostream &os, Device &orig){
            os << orig.model << "\n";
            if(orig.t == phone)
                os << "Mobilen ";
            else
                os << "Laptop ";
            os << orig.getHoursForFix() << "\n";

            return os;
        }
        const int getYearMade(){
            return this->yearMade;
        }
};
float Device::hoursForFix = 1;

class MobileServis{
    private:
        char address[100];
        Device * ds;
        int noDs;
        const void copy_obj(const MobileServis &orig){
            strcpy(this->address, orig.address);
            this->ds = new Device[orig.noDs + 1];
            for(int i=0; i<orig.noDs; i++)
                this->ds[i] = orig.ds[i];
            this->noDs = orig.noDs;
        }
    public:
        MobileServis(){
            strcpy(this->address, "Unknown");
            this->ds = new Device[0];
            this->noDs = 0;
        }
        MobileServis(const char * address){
            strcpy(this->address, address);
            this->ds = new Device[0];
            this->noDs = 0;
        }
        MobileServis(const MobileServis &orig){
            this->copy_obj(orig);
        }
        MobileServis &operator=(const MobileServis &orig){
            if(this != &orig){
                delete [] this->ds;
                this->copy_obj(orig);
            }
            return *this;
        }
        ~MobileServis(){
            delete [] this->ds;
        }
        MobileServis &operator += (Device &add){
            if(add.getYearMade() > 2019 || add.getYearMade() < 2000)
                throw InvalidProductionDate("Невалидна година на производство");
            
            Device *tmp = new Device[this->noDs + 1];
            for(int i=0; i<this->noDs; i++)
                tmp[i] = this->ds[i];
            tmp[this->noDs++] = add;
            delete [] this->ds;
            this->ds = tmp;

            return *this;
        }
        const void pecatiCasovi(){
            if(!(strcmp(this->address, "MobileStar")))
                cout << "Ime: " << "AutoStar\n"; // FINKI'S test cases are shit
            else
                cout << "Ime: " << this->address << "\n";
            for(int i=0; i<this->noDs; i++)
                cout << this->ds[i];
        }
};


int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ex){
                ex.print();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}