/*Автомобил Problem 5 (0 / 0)

Во оваа задача треба да се внесат и испечатат податоци за автомобили.

За еден автомобил (објект од класата Car) се чуваат следниве податоци:

    сопственик (објект од класата Person)
    датум на купување (објект од класата Date)
    цена (float price), предодредена вредност 0

За класата Car потребно е да се напише метод за печатење print() и метод за добивање на цената getPrice().
--
Класата Date содржи три цели броеви (int year, month, day) кои претставуваат датум.
За неа треба да се напише метод за печатење print(),
предодреден (default) конструктор, конструктор со параметри и конструктор за копирање.
--
Класата Person содржи име и презиме (низи од максимум 20 знаци, со предодредени вредности not specified), 
предодреден конструктор, конструктор со параметри и метод за печатење print().
--
Методот за печатење кај класата Person изгледа вака: [name] [lastName].

Методот за печатење кај класата Date изгледа вака: [year].[month].[day].

Методот за печатење кај класата Car изгледа вака:

owner.print()

date.print()

Price: [price]

Покрај тоа, потребно е да се напише метод cheaperThan(Car* cars, int numCars, float price) 
zкој ќе ги испечати сите објекти Car од низата cars со големина numCars чија цена е помала од price.
*/

#include<iostream>
#include<cstring>
using namespace std;

//class Date
class Date{
    private:
        int year;
        int month;
        int day;
    public:
        Date(){}
        Date(int god, int mesec, int den);
        Date(const Date &orig);
        void print();
};

Date::Date(int god, int mesec, int den){
    this->year=god;
    this->month=mesec;
    this->day=den;
}
Date::Date(const Date &orig){
    this->year=orig.year;
    this->month=orig.month;
    this->day=orig.day;
}
void Date::print(){
    cout << this->year <<"." << this->month << "." << this->day << endl;
}
//class Person
class Person {
    private:
        char name[20];
        char surname[20];
    public:
        Person();
        Person(const char * ime, const char * prezime);
        void print();
};

Person::Person(){
    strcpy(this->name,"not specified");
    strcpy(this->surname, "not specified");
}
Person::Person(const char * ime, const char * prezime){
    strcpy(this->name, ime);
    strcpy(this->surname, prezime);
}
void Person::print(){
    cout << this->name <<" " << this->surname << endl;
}

//class Car
class Car{
    private:
        Person owner;
        Date dateOfPurchase;
        float price;
    public:
        Car();
        Car(const Person lik, const Date date, float cena);
        void print();
        float getPrice();
};
Car::Car(){
    this->price=0.0;
}
Car::Car(const Person lik, const Date date, float cena){
    this->owner=lik;
    this->dateOfPurchase=date;
    this->price=cena;
}
void Car::print(){
    owner.print();
    dateOfPurchase.print();
    cout << "Price: " << this->price << endl;
}
float Car::getPrice(){
    return this->price;
}

//cheaperThan
void cheaperThan(Car * cars, int numCars, float price){
    for(int i=0; i<numCars; i++){
        if(cars[i].getPrice() < price)
            cars[i].print();
    }
} 

//main
int main() {
	char name[20];
	char lastName[20];
	int year;
	int month;
	int day;
	float price;

	int testCase;
	cin >> testCase;

	if (testCase == 1) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(year, month, day);

		cin >> price;
		Car car(lik, date,  price);

		car.print();
	}
	else if (testCase == 2) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(Date(year, month, day));

		cin >> price;
		Car car(lik, date,  price);
		car.print();
	}
	else {
		int numCars;
		cin >> numCars;

		Car cars[10];
		for (int i = 0; i < numCars; i++) {
			cin >> name;
			cin >> lastName;
			Person lik(name, lastName);

			cin >> year;
			cin >> month;
			cin >> day;
			Date date(year, month, day);

			cin >> price;
			cars[i] = Car(lik, date,  price);
		}
        float priceLimit;
        cin >> priceLimit;
		cheaperThan(cars, numCars, priceLimit);
	}


	return 0;
}