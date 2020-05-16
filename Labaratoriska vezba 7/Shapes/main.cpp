/*Shapes Problem 7 (0 / 0)

--

Потребно е да конструирате абстракна класа Shape со само еден параметар:

    страна (int)

Конструктори:

    Shape()
    Shape(int a)

И виртуелните методи:

    double plostina()
    void pecati()
    int getType()

Од таа класа вие треба да конструирате 3 изведени класи:

    Square
    Circle
    Triangle

Изведените класи немаат дополнителни парамтери, туку ја наследуваат страната од Shape

Конструктори:

Конструкторот на изведените класи ќе зема еден аругмент, страната на фигурата.

При пишување на конструкторот на изведените класи да се искористи констукторот на родител класата

Методи:

Секоја од класите си има своја формула за plostina() соодветна за нивната геометриска фигура

    Формула за плоштина на квадрат а * a
    Формула за плоштина на круг 3.14 * a * a
    Формула за плоштина на триаголник (sqrt(3)/4) * side * side

За pecati() методот упатете се кон outputot за тест случајите.

getType() методот треба да враќа:

    1 за Square
    2 за Circle
    3 за Triangle

Поени: 5

--

Дефинирајте го методот void checkNumTypes(Shape** niza, int n) така што ќе испечати во три реда колку квадрати, кругови и триаголници има во низата.

Поени: 2

--

Покрај тоа треба да ја допишете Main класата така што ќе алоцирате динамичка низа од покажувачи кон класата Shape.

Потоа кај секој покажувач од низата зависно од дадениот input да алоцирате објект од една од трите изведени класи.

Input:

Прво се добива n - големината на динамичката низа. Потоа n пати се добиваат пар цели броеви t i a, каде што t е типот на објектот и а е страната на објектот.

Пример:

3

1 3 //квадрат со страна со должина 3

2 2 //круг со страна со должина 2

3 1 //триаголник со страна со должина 1

Поени: 3

--
*/
#include <iostream>
#include <cmath>

using namespace std;


//TODO: konstruiraj ja abstraknata klasa Shape
class Shape{
    protected:
        int strana;
    public:
        Shape(){
            this->strana = 0;
        }
        Shape(const int a){
            this->strana = a;
        }
        ~Shape(){}
        virtual const double plostina() = 0;
        virtual const void pecati() = 0;
        virtual const int getType() = 0;
};

//TODO: konstruiraj ja klasata Kvadrat
class Square : public Shape{
    public:
        Square(){}
        Square(const int a) : Shape(a){}
        ~Square();
        const double plostina(){
            return this->strana * this->strana;
        }
        const void pecati(){
            cout << "Kvadrat so plostina = " << this->plostina() << endl;
        }
        const int getType(){
            return 1;
        }
};
//TODO: konstruiraj ja klasata Krug
class Circle : public Shape{
    public:
        Circle(){}
        Circle(const int a) : Shape(a){}
        ~Circle();
        const double plostina(){
            return 3.14 * this->strana * this->strana;
        }
        const void pecati(){
            cout << "Krug so plostina = " << this->plostina() << endl;
        }
        const int getType(){
            return 2;
        }
};
//TODO: konstruiraj ja klasata Triagolnik
class Triangle : public Shape{
    public:
        Triangle(){}
        Triangle(const int a) : Shape(a){}
        ~Triangle();
        const double plostina(){
            return (sqrt(3)/4) * this->strana * this->strana;
        }
        const void pecati(){
            cout << "Triagolnik so plostina = " << this->plostina() << endl;
        }
        const int getType(){
            return 3;
        }
};

//TODO: definiraj go metodot void checkNumTypes(Shape** niza, int n)
void checkNumTypes(Shape ** niza, int n){
    int squares = 0; int circles = 0; int triangles = 0;
    for(int i=0; i<n; i++){
        if(niza[i]->getType() == 1)
            squares++;
        else if(niza[i]->getType() == 2)
            circles++;
        else if(niza[i]->getType() == 3)
            triangles++;
    }
    cout << "Broj na kvadrati vo nizata = " << squares << endl;
    cout << "Broj na krugovi vo nizata = " << circles << endl;
    cout << "Broj na triagolnici vo nizata = " << triangles << endl;
}
int main(){


	int n;
	cin >> n;

	//TODO: inicijaliziraj niza od pokazuvachi kon klasata Shape
    Shape ** niza = new Shape* [n];
	

	//TODO: alociraj memorija so golemina n za prethodno navedenata niza

	int classType;
	int side;

	//TODO: konstruiraj for ciklus so chija pomosh ke ja popolnish nizata
	for(int i = 0; i < n; ++i){
		cin >> classType;
		cin >> side;
        if(classType == 1)
            niza[i] = new Square(side);
        else if(classType == 2)
            niza[i] = new Circle(side);
        else if(classType == 3)
            niza[i] = new Triangle(side); 	
	}
    
    
	for(int i = 0; i < n; ++i){

		niza[i]->pecati();
	}

	checkNumTypes(niza, n);


	return 0;
}