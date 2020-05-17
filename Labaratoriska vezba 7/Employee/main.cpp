/*Employee Problem 6 (1 / 7)

Да се дефинира апстрактна класа Employee којашто ќе содржи име на вработениот, години и работно искуство во години (integer). Да се дефинираат чисти виртуелни функции plata() и bonus() (double).

Од класата Employee да се изведе класа SalaryEmployee која покрај основните информации содржи и информација за основната плата. Бонусот на овие работници се пресметува како процент од основната плата, а процентот е бројот на години со работно искуство. На пример ако работеле 10 години, бонусот е 10 проценти од основната плата. Вкупната плата се пресметува како основната плата плус бонусот.

Од класата Employee исто така да се изведе класа HourlyEmployee која покрај основните информации содржи информација и за вкупниот број на часови кои ги одработил работникот и платата по час. Вкупната плата се пресметува како бројот на часови помножен со платата по час плус бонусот, додека бонусот се пресметува на следниот начин: За секој час над 320-тиот се добива 50 проценти од платата по час.

Од класата Employee на крај се изведува класата Freelancer која покрај основните информации содржи и број на проекти на кои работел вработениет и низа со суми кои ги добил за тие проекти (double). По направени 5 проекти, за секој нареден вработените добиваат бонус од 1000 денари. Вкупната плата на овој тип на вработени изнесува вкупната сума добиена од сите проекти плус бонусот.

Да се преоптовари операторот == кој ќе прима два објекти од класата Employee и ќе ги споредува според тоа дали имаат ист број на години и дали добиваат ист бонус.

Да се дефинира класа Company која ќе содржи информации за името на компанијата, бројот на вработени, и динамична низа од покажувачи од класата Employee или Employee **. За потребите на оваа класа треба да се дефинира конструктор кој прима само еден аргумент - името на компанијата, да се преоптовари операторот += и да се дефинираат следните методи:

    double vkupnaPlata() - метод којшто ја враќа вкупната плата на сите вработени во компанијата
    double filtriranaPlata(Employee * emp) - метод којшто ја враќа платата само на работниците кои се еднакви со дадениот вработен (според оператор ==)
    void pecatiRabotnici() - метод којшто печати по колку вработени има од секој тип на работници во компанијата, а форматот на печатење можете да го видите од тест примерите

Hint: За потребите на последниот метод можете да искористите статички членови и статички функции во секоја од класата, dynamic_cast, виртуелна функција која ќе ја преоптоварите во секоја од класите или нешто друго по ваша желба.
*/
#include <iostream>
#include <cstring>

using namespace std;

//abstract Employee
class Employee{
    protected:
        char name[50];
        int age;
        int exp;
    public:
        Employee(){
            strcpy(this->name, "None");
            this->age = 0;
            this->exp = 0;
        }
        Employee(const char * name, const int age, const int exp){
            strcpy(this->name, name);
            this->age = age;
            this->exp = exp;
        }
        virtual ~Employee(){}
        virtual const double bonus() = 0;
        virtual const double plata() = 0;
        const int getAge(){
            return this->age;
        }
};

//Derived classes
class SalaryEmployee : public Employee{
    private:
        double baseSalary;
    public:
        SalaryEmployee(){
            this->baseSalary = 0.0;
        }
        SalaryEmployee(const char * name, const int age, const int exp, const double baseSalary) : Employee(name, age, exp){
            this->baseSalary = baseSalary;
        }
        ~SalaryEmployee(){}
        const double bonus(){
            return (this->baseSalary * this->exp) / 100;
        }
        const double plata(){
            return this->baseSalary + this->bonus();
        }
};

class HourlyEmployee : public Employee{
    private:
        int totalHours;
        double salaryPerHour;
    public:
        HourlyEmployee(){
            this->totalHours = 0;
            this->salaryPerHour = 0.0;
        }
        HourlyEmployee(const char * name, const int age, const int exp, const int totalHours, const double salaryPerHour) : Employee(name, age, exp){
            this->totalHours = totalHours;
            this->salaryPerHour = salaryPerHour;
        }
        ~HourlyEmployee(){}
        const double bonus(){
            if(this->totalHours > 320){
                return (this->totalHours - 320) * (this->salaryPerHour * 0.5);
            } else
                return 0.0;
        }
        const double plata(){
            return (this->totalHours * this->salaryPerHour) + this->bonus();
        }
};

class Freelancer  : public Employee{
    private:
        int doneProjects;
        double * money;
    public:
        Freelancer (){
            this->doneProjects = 0;
            this->money = new double[0];
        }
        Freelancer (const char * name, const int age, const int exp, const int doneProjects, const double * money) : Employee(name, age, exp){
            this->doneProjects = doneProjects;
            this->money = new double[this->doneProjects];
            for(int i=0; i<this->doneProjects; i++)
                this->money[i] = money[i];
        }
        ~Freelancer (){
            delete [] this->money;
        }
        const double bonus(){
            if(this->doneProjects > 5){
                return (this->doneProjects - 5) * 1000;
            } else
                return 0.0;
        }
        const double plata(){
            double totalSalary = 0.0;
            for(int i=0; i<this->doneProjects; i++)
                totalSalary += this->money[i];
            return totalSalary + this->bonus();
        }
};

bool operator==(Employee *left, Employee &right){
    if((left->getAge() == right.getAge()) && left->bonus() == right.bonus())
        return true;
    else
        return false;
}

//class Company
class Company{
    private:
        char name[50];
        int noEmployees;
        Employee ** emps;
    public:
        Company(){
            strcpy(this->name, "None");
            this->noEmployees = 0;
            this->emps = new Employee *[0];
        }
        Company(const char * name){
            strcpy(this->name, name);
            this->noEmployees = 0;
            this->emps = new Employee *[0];
        }
        ~Company(){
            //delete [] this->emps;
        }
        Company &operator += (Employee * orig){
            Employee ** tmp = new Employee *[this->noEmployees+1];
            for(int i=0; i<this->noEmployees; i++)
                tmp[i] = this->emps[i];
            
            tmp[this->noEmployees++] = orig;
            delete [] this->emps;
            this->emps = tmp;

            return *this;
        }
        double vkupnaPlata(){
            double totalSalary = 0.0;
            for(int i=0; i<this->noEmployees; i++)
                totalSalary += this->emps[i]->plata();
            return totalSalary;
        }
        double filtriranaPlata(Employee *emp){
            double totalFiltered = 0.0;
            for(int i=0; i<this->noEmployees; i++){
                if(this->emps[i] == *emp)
                    totalFiltered += this->emps[i]->plata();
            }
            return totalFiltered;
        }
        const void pecatiRabotnici(){
            int salaryEmps = 0; int hourlyEmps = 0; int freelancerEmps = 0;
            for(int i=0; i<this->noEmployees; i++){
                SalaryEmployee *a = dynamic_cast<SalaryEmployee *>(this->emps[i]);
                HourlyEmployee *b = dynamic_cast<HourlyEmployee *>(this->emps[i]);
                Freelancer *c = dynamic_cast<Freelancer *>(this->emps[i]);
                if(a)
                    salaryEmps++;
                else if(b)
                    hourlyEmps++;
                else if(c)
                    freelancerEmps++;
            }
            cout << "Vo kompanijata " << this->name << " rabotat:" << endl;
            cout << "Salary employees: " << salaryEmps << endl;
            cout << "Hourly employees: " << hourlyEmps << endl;
            cout << "Freelancers: " << freelancerEmps << endl;
        }
};

//main
int main() {

char name[50];
cin >> name;
Company c(name);

int n;
cin >> n;

char employeeName[50];
int age;
int experience;
int type;

for (int i=0; i <n; ++i) {
  cin >> type;
  cin >> employeeName >> age >> experience;

  if (type == 1) {
    int basicSalary;
    cin >> basicSalary;
    c += new SalaryEmployee(employeeName, age, experience, basicSalary);
  }

  else if (type == 2) {
    int hoursWorked;
    int hourlyPay;
    cin >> hoursWorked >> hourlyPay;
    c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
  }

  else {
    int numProjects;
    cin >> numProjects;
    double projects[10];
    for (int i=0; i < numProjects; ++i) {
      cin >> projects[i];
    }
    c += new Freelancer(employeeName, age, experience, numProjects, projects);
  }
}

c.pecatiRabotnici();
cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

delete emp;
}