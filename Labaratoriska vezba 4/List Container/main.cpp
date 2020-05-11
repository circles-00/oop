/*
ListContainer Problem 5 (1 / 1)

Да се имплементира класа List во којашто ќе се чуваат информации за:

    броеви што се дел од листата (динамички алоцирана низа од цели броеви)
    бројот на броеви што се дел од листата

За класата да се дефинираат следните методи:

    конструктор (со аргументи), copy-конструктор, деструктор, оператор =
    void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
    int sum() метод што ја враќа сумата на елементите во листата
    double average() метод што ќе го враќа просекот на броевите во листата

Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

    низа од листи (динамички алоцирана низа од објекти од класата List)
    број на елементи во низата од листи (цел број)
    број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)

За класата потребно е да ги дефинирате следните методи:

    конструктор (default), copy-конструктор, деструктор, оператор =
    void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
        доколку контејнерот е празен се печати само порака The list is empty.
    void addNewList(List l) метод со којшто се додава листа во контејнерот
        Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
    int sum() метод што ја враќа сумата на сите елементи во сите листи
    double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот


5
5
1 2 3 4 5   
2
10 5      
3
1 2 3     
6
1 4 5 6 7 10 
3
10 10 13
0*/
#include <iostream>
#include <cstring>

using namespace std;

class List{
    private:
        int * listElements;
        int noElements;
        void copy(const List &orig){
            this->listElements = new int[orig.noElements];
            for(int i=0; i<orig.noElements; i++)
                this->listElements[i] = orig.listElements[i];
            this->noElements = orig.noElements;
        }
    public:
        List();
        List(const int * niza, const int brojNiza);
        List(const List &orig);
        List &operator=(const List &orig);
        ~List();
        int sum();
        double average();
        void pecati();
        const int getNoElements();
};

List::List(){
    this->listElements = new int[0];
    this->noElements = 0;
}
List::List(const int * niza, const int brojNiza){
    this->listElements = new int[brojNiza];
    for(int i=0; i<brojNiza; i++)
        this->listElements[i] = niza[i];
    this->noElements = brojNiza;
}
List::List(const List &orig){
    copy(orig);
}
List &List::operator=(const List &orig){
    if(this != &orig){
        delete [] this->listElements;
        copy(orig);
    }
    return *this;
}
List::~List(){
    delete [] this->listElements;
}
int List::sum(){
    int sum=0;
    for(int i=0; i<this->noElements; i++)
        sum += this->listElements[i];
    return sum;
}
double List::average(){
    return this->sum()*1.0/this->noElements;
}
void List::pecati(){
    cout << this->noElements << ": ";
    for(int i=0; i<this->noElements; i++)
        cout << this->listElements[i] << " ";
    cout << "sum: " << this->sum() << " average: " << this->average() << endl;
}
const int List::getNoElements(){
    return this->noElements;
}
//ListContainer
class ListContainer{
    private:
        List * lists;
        int noLists;
        int attempts;
        void copy(const ListContainer &orig){
            this->lists = new List[orig.noLists];
            for(int i=0; i<orig.noLists; i++)
                this->lists[i] = orig.lists[i];
            this->noLists = orig.noLists;
            this->attempts = orig.attempts;
        }
    public:
        ListContainer();
        ListContainer(const ListContainer &orig);
        ListContainer &operator=(const ListContainer &orig);
        ~ListContainer();
        void addNewList(List l);
        int sum();
        double average();
        void print();
};

ListContainer::ListContainer(){
    this->lists = new List[0];
    this->noLists = 0;
    this->attempts = 0;
}
ListContainer::ListContainer(const ListContainer &orig){
    this->copy(orig);
}
ListContainer &ListContainer::operator=(const ListContainer &orig){
    if(this != &orig){
        delete [] this->lists;
        this->copy(orig);
    }
    return *this;
}
ListContainer::~ListContainer(){
    delete [] this->lists;
}
void ListContainer::addNewList(List l){
    ++this->attempts;
        for(int i=0;i<this->noLists;i++){
            if(l.sum()==this->lists[i].sum())
                return;
        }
        List* tmp=new List[this->noLists+1];
        for(int i=0;i<this->noLists;i++){
            tmp[i]=this->lists[i];
        }
        tmp[this->noLists++]=l;
        delete [] this->lists;
        this->lists=tmp;
}
int ListContainer::sum(){
    int sum=0;
    for(int i=0; i<this->noLists; i++)
        sum += this->lists[i].sum();
    return sum;
}
double ListContainer::average(){
    int sum=0;
    int elements=0;
    for(int i=0; i<this->noLists; i++){
        sum += this->lists[i].sum();
        elements += this->lists[i].getNoElements();
    }
    return float (sum) / elements;
}
void ListContainer::print(){
    if(this->noLists == 0){
        cout << "The list is empty" << endl;
        return ;
    }
    else {
        for(int i=0; i<this->noLists; i++){
            cout << "List number: " << i+1 << " List info: ";
            this->lists[i].pecati();
        }
    }
    cout << "Sum: " << this->sum();
    cout << " Average: " << this->average() << endl;
    cout << "Successful attempts: " << this->noLists << " Failed attempts: " << this->attempts - this->noLists << endl;
}


//main
int main() {
	
	ListContainer lc;
	int N;	
	cin>>N;	
    
	for (int i=0;i<N;i++) {
		int n;
		int niza[100];
		
		cin>>n;
       
		for (int j=0;j<n;j++){
			cin>>niza[j];
            
		}
       
		List l=List(niza,n);
	
		lc.addNewList(l);
	}	
	
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
        
    }
    else {
        lc.print();
    }
}