/*Numbers Problem 4 (0 / 0)

Да се дефинира апстрктна класа Number со следните чисто виртуелни методи:

    double doubleValue() -ја враќа децималната вредност на даден број
    int intValue()- ја враќа целобројната вредност на даден број
    void print() - печати информации за бројот. (1 поен)

Од оваа класа да се изведат две класи:

    Integer (во која што се чува еден број од тип int)
    Double (во која што се чува еден број од тип double) (1 поен).

За двете изведени класи да се имплементираaт соодветен конструктори, како и да се препокријат методите од основната класа. (1 поени)

Да се преоптовари операторот == којшто ќе споредува два броеви според нивната вредност (објекти од класа Number) (1 поен)

Дополнително да се дефинира класа Numbers во која што ќе се чуваат:

    динамички алоцирана низа од покажувачи кон објекти од класата Number
    број на елементи во низата од покажувачи

За класата да се имплементира соодветен конструктор (default) , како и: (1 поени)

    операторот += за додавање на броеви во низата од броеви (1 поен)
        Бројот се додава ако и само ако сите броеви што се веќе додадени во низата се различни од него
    функција void statistics() која што печати информации за броевите во низата: (2 поени)

Count of numbers: [број на броеви во низата

Sum of all numbers: [сума на сите броеви во низата]

Count of integer numbers: [број на цели броеви (Integer)]

Sum of integer numbers: [сума на сите цели броеви (Integer)]

Count of double numbers: [број на децимални броеви (Double)]

Sum of double numbers: [сума на сите децимални броеви (Double)]

    функција void integersLessThan (Integer n) која што ги печати сите цели броеви помали од бројот n (1 поен)
    функција void doublesBiggerThan (Double n) која што ги печати сите децимални броеви поголеми од бројот n (1 поен)

*/
#include <iostream>
#include <cstring>
using namespace std;

class Number {
    public:
        virtual const double doubleValue() = 0;
        virtual const int intValue() = 0;
        virtual const void print() = 0;
}; 

bool operator==(Number *left, Number &right){
    if(left->doubleValue() == right.doubleValue())
        return true;
    else
        return false;
}

class Integer : public Number {
    private:
        int integer;
    public:
        Integer(){
            this->integer = 0;
        }
        Integer(const int integer){
            this->integer = integer;
        }
        ~Integer(){}
        const int intValue(){
            return this->integer;     
        }
        const double doubleValue(){
            return double (this->integer);
        }
        const void print(){
            cout << "Integer: " << this->integer << endl;
        } 
};

class Double : public Number{
    private:
        double floatingNo;
    public:
        Double(){
            this->floatingNo = 0.0;
        }
        Double(const double floatingNo){
            this->floatingNo = floatingNo;
        }
        ~Double(){}
        const int intValue(){
            return int (this->floatingNo);
        }
        const double doubleValue(){
            return this->floatingNo;
        }
        const void print(){
            cout << "Double: " << this->floatingNo << endl;
        }
};

class Numbers{
    private:
        Number **number;
        int noElements;
        void copy(const Numbers &orig){
            this->number = new Number * [orig.noElements];
            for(int i=0; i<orig.noElements; i++)
                this->number[i] = orig.number[i];
            this->noElements = orig.noElements;
        }
    public:
        Numbers(){
            this->number = new Number * [1];
            this->noElements = 0;
        }
        Numbers(const Number &orig){
            this->copy(orig);        
        }
        Numbers &operator=(const Numbers &orig){
            if(this != &orig){
                delete [] this->number;
                this->copy(orig);
            }
            return *this;
        }
        ~Numbers(){
            delete [] this->number;
        }
        Numbers &operator += (Number * orig){
            int flag = 1;
            
            for(int i=0; i<this->noElements; i++){
                if(orig->doubleValue() == this->number[i]->doubleValue())
                    flag = 0;  
            }
            
            if(flag){
                Number ** tmp = new Number * [this->noElements + 1];
                for(int i=0; i<this->noElements; i++)
                    tmp[i] = this->number[i];
                tmp[this->noElements++] = orig;
                delete [] this->number;
                this->number = tmp;
            }

            return *this;
        }
        const int intSum(){
            int sum = 0;
            Number * tmp;
            for(int i=0; i<this->noElements; i++){
                tmp = dynamic_cast<Integer *>(this->number[i]);
                if(tmp)
                    sum += tmp->intValue();
            }
            return sum;
        }
        const double doubleSum(){
            double sum = 0.0;
            Number * tmp;
            for(int i=0; i<this->noElements; i++){
                tmp = dynamic_cast<Double *>(this->number[i]);
                if(tmp)
                    sum += tmp->doubleValue();
            }
            return sum;
        }
        const int intCount(){
            int count = 0;
            Number * tmp;
            for(int i=0; i<this->noElements; i++){
                tmp = dynamic_cast<Integer *>(this->number[i]);
                if(tmp)
                    count++;
            }
            return count;
        }
        const int doubleCount(){
            int count = 0;
            Number * tmp;
            for(int i=0; i<this->noElements; i++){
                tmp = dynamic_cast<Double *>(this->number[i]);
                if(tmp)
                    count++;
            }
            return count;
        }
        const void statistics(){
            cout << "Count of numbers: " << this->noElements << endl;
            cout << "Sum of all numbers: " << this->doubleSum() + double (this->intSum()) << endl;
            cout << "Count of integer numbers: " << this->intCount() << endl;
            cout << "Sum of integer numbers: " << this->intSum() << endl;
            cout << "Count of double numbers: " << this->doubleCount() << endl;
            cout << "Sum of double numbers: " << this->doubleSum() << endl;
        }
        const void integersLessThan(Integer n){
            int count = 0;
            for(int i=0; i<this->noElements; i++){
                Integer * tmp = dynamic_cast<Integer *>(this->number[i]);
                if(tmp){
                    if(this->number[i]->intValue() < n.intValue()){
                        this->number[i]->print();
                        count++;
                    }
                }
            }
            if(count == 0)
                cout << "None" << endl;
        }
        const void doublesBiggerThan(Double n){
            int count = 0;
            for(int i=0; i<this->noElements; i++){
                Double * tmp = dynamic_cast<Double *>(this->number[i]);
                if(tmp){
                    if(this->number[i]->intValue() > n.doubleValue()){
                        this->number[i]->print();
                        count++;
                    }
                }
            }
            if(count == 0)
                cout << "None" << endl;
        }
};

int main() {
	
	int n;
	cin>>n;
	Numbers numbers;
	for (int i=0;i<n;i++){
		int type;
		double number;
		cin>>type>>number;
		if (type==0){//Integer object
			Integer * integer = new Integer((int) number);
			numbers+=integer;
		}
		else {
			Double * doublee = new Double(number);
			numbers+=doublee;
		}
	}
	
	int lessThan;
	double biggerThan;
	
	cin>>lessThan;
	cin>>biggerThan;		
	
	cout<<"STATISTICS FOR THE NUMBERS\n";
	numbers.statistics();
	cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
	numbers.integersLessThan(Integer(lessThan));
	cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
	numbers.doublesBiggerThan(Double(biggerThan));
	
	return 0;
}