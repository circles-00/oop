#include <iostream>
#include <cstring>

using namespace std;

class ArithmeticException{
    public:
        const void message(){
            cout << "Division by zero is not allowed" << endl;
        }
};
class NumbersNotDivisibleException{
    private:
        int delenik;
    public:
        NumbersNotDivisibleException(const int delenik){
            this->delenik = delenik;
        }
        const void message(){
            cout << "Division by " << this->delenik << " is not supported" << endl;
        }
};
class ArrayFullException {
    public:
        const void message(){
            cout << "The array is full. Increase the capacity" << endl;
        }
};
class IndexOutOfBoundsException{
    private:
        int index;
    public:
        IndexOutOfBoundsException(const int index){
            this->index = index;
        }
        const void message(){
            cout << "Index " << this->index << " is out of bounds" << endl;
        }
};
class NumberIsNotPositiveException{
    private:
        int number;
    public:
        NumberIsNotPositiveException(const int number){
            this->number = number;
        }
        const void message(){
            cout << "Number " << this->number << " is not positive integer" << endl;
        }
};


class PositiveIntegers{
    private:
        int * integers;
        int noEl;
        int maxSize;
        void copy(const PositiveIntegers &orig){
            this->noEl = orig.noEl;
            this->maxSize = orig.maxSize;
            this->integers = new int[orig.noEl + 1];
            for(int i=0; i<this->noEl; i++)
                this->integers[i] = orig.integers[i];
        }
    public:
        PositiveIntegers(){
            this->integers = new int[1];
            this->noEl = 0;
            this->maxSize = 0;
        }
        PositiveIntegers(const int maxSize){
            this->integers = new int[maxSize];
            this->noEl = 0;
            this->maxSize = maxSize;
        }
        PositiveIntegers(const PositiveIntegers &orig){
            this->copy(orig);
        }
        PositiveIntegers &operator=(const PositiveIntegers &orig){
            if(this != &orig){
                delete [] this->integers;
                this->copy(orig);
            }
            return *this;
        }
        ~PositiveIntegers(){
            
            //delete [] this->integers;
        }
        const void increaseCapacity(const int c){
            int * tmp = new int[this->maxSize + c];
            for(int i=0; i<this->noEl; i++)
                tmp[i] = this->integers[i];
            delete [] this->integers;
            this->integers = tmp;
            this->maxSize += c;
        }
        PositiveIntegers &operator +=(int newInt){
            if(this->noEl >= this->maxSize)
                throw ArrayFullException();
            if(newInt <= 0)
                throw NumberIsNotPositiveException(newInt);

            this->integers[this->noEl++] = newInt; 
            return *this;
        }
        PositiveIntegers operator*(int orig){
           PositiveIntegers pi (*this);
            for (int i=0;i<pi.noEl;i++)
                pi.integers[i]*=orig;
       
            return pi;
        }
        PositiveIntegers operator/(int orig){
            if(orig == 0)
                throw ArithmeticException();
            for(int i=0; i<this->noEl; i++){
                if(this->integers[i] % orig != 0)
                    throw NumbersNotDivisibleException(orig);
            }

            PositiveIntegers pi (*this);
            for (int i=0;i<pi.noEl;i++)
                pi.integers[i]/=orig;
       
            return pi; 
        }
        int &operator[] (int i){
            if((i < 0) || i > this->noEl)
                throw IndexOutOfBoundsException(i);
            return this->integers[i];
        }
        const void print(){
            cout << "Size: " << this->noEl << " Capacity: " << this->maxSize << " Numbers: ";
            for(int i=0; i<this->noEl; i++)
                cout << this->integers[i] << " ";
            cout << endl;
        }
};

int main() {
	
	int n,capacity;
	cin >> n >> capacity;
	PositiveIntegers pi (capacity);
	for (int i=0;i<n;i++){
		int number;
		cin>>number;
        try{
		    pi+=number;  
        }
        catch (ArrayFullException &ex){
            ex.message();
        }
        catch (NumberIsNotPositiveException &ex){
            ex.message();
        }
	}
	cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	int incCapacity;
	cin>>incCapacity;
	pi.increaseCapacity(incCapacity);
	cout<<"===INCREASING CAPACITY==="<<endl;
	pi.print();
	
	int n1;
	cin>>n1;
	for (int i=0;i<n1;i++){
		int number;
		cin>>number;
		try{
            pi+=number;    
        }
        catch (ArrayFullException &ex){
            ex.message();
        }
        catch (NumberIsNotPositiveException &ex){
            ex.message();
        }
	}
	cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;
	
    pi.print();	
	PositiveIntegers pi1;
	
	cout<<"===TESTING DIVISION==="<<endl;	
	
	try{
        pi1 = pi/0;
        pi1.print();
    }
    catch(ArithmeticException &ex){
        ex.message();
    }
    catch(NumbersNotDivisibleException &ex){
        ex.message();
    }

	try{
        pi1 = pi/1;
        pi1.print();	
    }
    catch(ArithmeticException &ex){
        ex.message();
    }
    catch(NumbersNotDivisibleException &ex){
        ex.message();
    }
	
    try{
	    pi1 = pi/2;
        pi1.print();
    }
    catch(ArithmeticException &ex){
        ex.message();
    }
    catch(NumbersNotDivisibleException &ex){
        ex.message();
    }
	
	cout<<"===TESTING MULTIPLICATION==="<<endl;
	pi1 = pi*3;
	pi1.print();
	
	
	cout<<"===TESTING [] ==="<<endl;	
	
    try{
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;	
    }
    catch(IndexOutOfBoundsException &ex){
        ex.message();
    }
	try{
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch(IndexOutOfBoundsException &ex){
        ex.message();
    }
	try{
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;	
    }
    catch(IndexOutOfBoundsException &ex){
        ex.message();
    }
	try{
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch(IndexOutOfBoundsException &ex){
        ex.message();
    }

	return 0;
}