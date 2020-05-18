#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};

class Rectangle : public Shape{
	public:
	    void draw(){
			cout << "Drawing a rectangle.\n";
        }
};


int main() {
    Shape* shape;

   	shape = new Shape();
    shape->draw();

    shape = new Rectangle();
    shape->draw();

    return 0;
}