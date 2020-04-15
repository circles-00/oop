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

//List
class List{
    private:
        int * numbers;
        int countnumbers;
    public:
        List(const int * broevi, const int bbroevi);
        List(const List &orig);
        List &operator=(const List &orig);
        ~List();
        void pecati();
        int sum();
        double average();
};

List::List(const int * broevi = NULL, const int bbroevi = 0){
    this->countnumbers = bbroevi;
    this->numbers = new int[bbroevi + 1];
    for(int i=0; i<bbroevi; i++)
        this->numbers[i] = broevi[i];
}
List::List(const List &orig){
    delete [] this->numbers;
    this->countnumbers = orig.countnumbers;
    this->numbers = new int[orig.countnumbers + 1];
    for(int i=0; i<orig.countnumbers; i++)
        this->numbers[i] = orig.numbers[i];
}
List &List::operator=(const List &orig){
    if(this != &orig){
        delete [] this->numbers;
        this->countnumbers = orig.countnumbers;
        this->numbers = new int[orig.countnumbers + 1];
        for(int i=0; i<orig.countnumbers; i++)
            this->numbers[i] = orig.numbers[i];
    }
    return *this;
}
List::~List(){
    delete [] this->numbers;
}
int List::sum(){
    int sum=0;
    for(int i=0; i<countnumbers; i++)
        sum += this->numbers[i];
    return sum;
}
double List::average(){
    return this->sum()/this->countnumbers;
}
void List::pecati(){
    cout << this->countnumbers << ": ";
    for(int i=0; i<countnumbers; i++)
        cout << this->numbers[i] << " ";
    cout << "sum: " << this->sum() << "average: " << this->average() << endl; 
}

//ListContainer
class ListContainer{
    private:
        List * lists;
        int countbr;
        int tries;
    public:
        ListContainer();
        ListContainer(const ListContainer &orig);
        ListContainer &operator=(const ListContainer &orig);
        ~ListContainer();
        void pecati();
        void addNewList(List l);
        int sum();
        double average();
};

ListContainer::ListContainer(){
    this->lists = new List[0];
    this->countbr = 0;
    this->tries = 0;
}
ListContainer::ListContainer(const ListContainer &orig){
    delete [] this->lists;
    this->countbr = orig.countbr;
    this->tries = orig.tries;
    for(int i=0; i<orig.countbr; i++)
        this->lists[i] = orig.lists;
}
ListContainer &ListContainer::operator=(const ListContainer &orig){
    if(this != &orig){
        delete [] this->lists;
        this->countbr = orig.countbr;
        this->tries = orig.tries;
        for(int i=0; i<orig.countbr; i++)
            this->lists[i] = orig.lists[i];
    }
    return *this;
}
void ListContainer::pecati(){
    for(int i=0; i<this->countbr; i++){
        cout << "List number: " << i << "List info: "; this->lists[i].pecati();
        cout << endl;
    }
}
void ListContainer::addNewList(List l){

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