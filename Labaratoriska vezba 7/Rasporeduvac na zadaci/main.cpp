/*Распоредувач на задачи Problem 2 (0 / 0)

Да се дефинира апстрактна класата Task во која што се чува информација за:

    ID (низа од максимум 5 знаци)

Дополнително апстрактната класа содржи два чисто виртуелни методи:

    int getOrder() којшто го враќа редниот број (редот) на извршување на задачата (Task-oт).
    void print() којшто печати информации за задачата (види тест примери) (1 поен)

Постојат два вида на таскови (задачи):

    TimedTask во којшто се чува информација за:
        потребното време за извршување на задачата time (цел број)
    PriorityTask во којшто се чува информација за:
        степенот на приоритет priority (цел број)

Редниот број на извршувањe на TimedTask e дефиниран со времето на извршување, додека пак на PriorityTask со степенот на приоритет. (1 поен)

За двата типа на таскови да се имплементираат:

    оператор за споредба == којшто ги споредува според нивниот ID и според нивното време/степен на приоритетност. (2 поени)
    препокриени функции од класата Task (2 поени)

Дополнително, да се имплементираат следните надворешни методи:

    void scheduleTimedTasks (Task ** tasks, int n, int t)- метод којшто ќе ги распореди сите задачи од тип TimedTask со време на извршување помало од t (ќе испечати информации за нив), сортирани во растечки редослед според времето на извршување. Методот прима три аргументи (низа од покажувачи кон Task, бројот на елементи во низата и времетот t) (2 поени)
    void schedulePrioritryTask(Task ** tasks, int n, int p) - метод којшто ќе ги распореди сите задачи од тип PriorityTask со степен на приоритет помал од p (ќе испечати информации за нив), сортирани во растечки редослед според степенот на приоритетност. Методот прима три аргументи (низа од покажувачи кон Task, бројот на елементи во низата и степенот на приоритетност p) (2 поени)

Напомена: Двете функции може да ги имплементирате и без сортирање, но во тој пример ќе ви излезат 80% тест примери точни.
*/
#include<iostream>
#include<cstring>

using namespace std;

class Task{
    protected:
        char id[5];
    public:
    Task();
    Task (const char * id);
    ~Task();
    virtual int getOrder() = 0;
    virtual void print() = 0;
    const char * getID();
};

Task::Task(){
    strcpy(this->id, "None");
}
Task::Task(const char * id){
    strcpy(this-> id, id);
}
Task::~Task(){}
const char * Task::getID(){
    return this->id;
}
//Preoptovaruvanje na operatorot za sporedba == (prima 2 argumenti bidejki se definira nadvor od klasata Task)
bool operator==(Task *left, Task &right){
    if(!strcmp(left->getID(), right.getID()) && (left->getOrder() == right.getOrder()))
        return true;
    else
        return false;
}
class TimedTask : public Task{
    private:
       int time; 
    public:
        TimedTask();
        TimedTask(const char * id, const int time) : Task(id){
            this->time = time;
        }
        ~TimedTask();
        int getOrder();
        void print();
};

TimedTask::TimedTask(){
    this->time = 0;
}
TimedTask::~TimedTask(){}
int TimedTask::getOrder(){
    return this->time;
}
void TimedTask::print(){
    cout << "TT->" << this->id << ":" << this->time << endl; 
}

class PriorityTask : public Task {
    private:
        int priority;
    public:
        PriorityTask();
        PriorityTask(const char * id, const int priority) : Task (id){
            this->priority = priority;
        }
        ~PriorityTask();
        int getOrder();
        void print();
};

PriorityTask::PriorityTask(){
    this->priority = 0;
}
PriorityTask::~PriorityTask(){}
int PriorityTask::getOrder(){
    return this->priority;
}
void PriorityTask::print(){
    cout << "PT->" << this->id << ":" << this->priority << endl; 
}

//void scheduleTimedTasks(Task ** tasks, int n, int t) {}
void scheduleTimedTasks(Task ** tasks, int n, int t){
    for (int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(tasks[i]->getOrder() > tasks[j]->getOrder()){
                Task *tmp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = tmp;
            }
        }
    }
    for(int i = 0; i < n; i++){
    	TimedTask *pt = dynamic_cast<TimedTask *>(tasks[i]);
        if(pt){
        	if(tasks[i]->getOrder() < t)
                tasks[i]->print();
        }
    }
}
//void schedulePriorityTasks(Task ** tasks, int n, int p) {}
void schedulePriorityTasks(Task ** tasks, int n, int p){
    for (int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(tasks[i]->getOrder() > tasks[j]->getOrder()){
                Task *tmp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = tmp;
            }
        }
    }

    for(int i = 0; i < n; i++){
    	PriorityTask *pt = dynamic_cast<PriorityTask *>(tasks[i]);
        if(pt){
        	if(tasks[i]->getOrder() < p)
                tasks[i]->print();
        }
    }
} 

//main
int main () {
    int testCase;
    int n;
    cin>>testCase;
    
    if (testCase==0){
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
        //tasks[i]->print();
    	}
        
    	cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
    	schedulePriorityTasks(tasks,n,10);
        
    }
    else if (testCase==1) {
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
        //tasks[i]->print();
    	}
        
    	
        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);
        
        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }
    
	return 0;
}