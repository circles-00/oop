#include <iostream>
#include <cstring>
#define MAX 100

using namespace std;

enum typeC{standard,loyal,vip};

class UserExistsException{
    private:
        char msg[256];
    public:
        UserExistsException(const char * msg){
            strcpy(this->msg, msg);
        }
        const void print(){
            cout << this->msg;
        }
};


class Customer{
    private:
        char name[50];
        char email[50];
        typeC type;
        int noBought;
        static int baseSale;
        static int addSale;
        const void copy_obj(const Customer &orig){
            strcpy(this->name, orig.name);
            strcpy(this->email, orig.email);
            this->type = orig.type;
            this->noBought = orig.noBought;
        }
    public:
        Customer(){
            strcpy(this->name, "Unknown");
            strcpy(this->email, "none@none.com");
            this->type = (typeC)0;
            this->noBought = 0;
        }
        Customer(const char * name, const char * email, typeC type, const int noBought){
            strcpy(this->name, name);
            strcpy(this->email, email);
            this->type = type;
            this->noBought = noBought;
        }
        Customer(const Customer &orig){
            this->copy_obj(orig);
        }
        Customer &operator=(const Customer &orig){
            if(this != &orig)
                this->copy_obj(orig);
            return *this;
        }
        const int sale(){
            if(this->type == standard)
                return 0;
            else if(this->type == loyal)
                return baseSale;
            else
                return addSale + baseSale;
        }
        static const void setDiscount1(const int newDisc){
            baseSale = newDisc;
        }
        friend ostream &operator << (ostream &os, Customer &orig){
            os << orig.name << "\n" << orig.email << "\n" << orig.noBought << "\n";
            if(orig.type == standard)
                os << "standard ";
            else if(orig.type == loyal)
                os <<"loyal ";
            else
                os << "vip ";
            os << orig.sale() << "\n";

            return os;
        }
        const char * getEmail(){
            return this->email;
        }
        const typeC getType(){
            return this->type;
        }
        const int getNoBought(){
            return this->noBought;
        }
        const void setType(typeC newType){
            this->type = newType;
        }
};
int Customer::baseSale = 10;
int Customer::addSale = 20;

class FINKI_bookstore{
    private:
        Customer * cs;
        int noCs;
        const void copy_obj(const FINKI_bookstore &orig){
            this->cs = new Customer[orig.noCs+1];
            for(int i=0; i<orig.noCs; i++)
                this->cs[i] = orig.cs[i];
            this->noCs = orig.noCs;
        }
    public:
        FINKI_bookstore(){
            this->cs = new Customer[0];
            this->noCs = 0;
        }
        FINKI_bookstore(const FINKI_bookstore &orig){
            this->copy_obj(orig);
        }
        FINKI_bookstore &operator=(const FINKI_bookstore &orig){
            if(this != &orig){
                delete [] this->cs;
                this->copy_obj(orig);
            }
            return *this;
        }
        ~FINKI_bookstore(){
            delete [] this->cs;
        }
        FINKI_bookstore &operator += (Customer &add){
            for(int i=0; i<this->noCs; i++)
                if(!(strcmp(this->cs[i].getEmail(), add.getEmail())))
                    throw UserExistsException("The user already exists in the list!\n");
            Customer * tmp = new Customer[this->noCs+1];
            for(int i=0; i<this->noCs; i++)
                tmp[i] = this->cs[i];
            tmp[this->noCs++] = add;
            delete [] this->cs;
            this->cs = tmp;

            return *this;
        }
        const void setCustomers(Customer * customers, int n){
            this->noCs = n;
            this->cs = new Customer[n+1];
            for(int i=0; i<n; i++)
                this->cs[i] = customers[i];
        }
        const void update(){
            for(int i=0; i<this->noCs; i++){
                if(this->cs[i].getType() == standard && this->cs[i].getNoBought() > 5)
                    this->cs[i].setType(loyal);
                else if(this->cs[i].getType() == loyal && this->cs[i].getNoBought() > 10)
                    this->cs[i].setType(vip);
            }
        }
        friend ostream &operator << (ostream &os, FINKI_bookstore &orig){
            for(int i=0; i<orig.noCs; i++)
                os << orig.cs[i];
            return os;
        }
};

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    
    try{
        fc+=c;
    }
    
    catch(UserExistsException &ex){
        ex.print();
    }
    
    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;
   
}
