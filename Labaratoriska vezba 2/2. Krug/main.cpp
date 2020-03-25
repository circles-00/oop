/* Круг Problem 2 (0 / 0)

Да се дефинира класа Krug, во која се чуваат информации за:

    *радиус float
    *бројот π const float.

Во класата да се реализираат:

    default конструктор и конструктор со аргументи
    метод за пресметување плоштина
    метод за пресметување периметар
    метод кој кажува дали плоштината и периметарот на даден круг се еднакви
    Test Case:
    5
    Expected Output:
    31.4
    78.5
    0
 */

#include <iostream>
using namespace std;

class Krug {
    private:
        float rad;
        const float pi = 3.14;
    public:
        Krug () {
            rad = 0;
        }
        Krug(int radius) {
            rad = radius;
        }
        float perimetar();
        float plostina();
        int ednakvi();
};

float Krug::perimetar() {
    return 2*rad*pi;
}
float Krug::plostina() {
    return rad*rad*pi;
}
int Krug::ednakvi() {
    if(plostina()==perimetar())
        return 1;
    else
        return 0;
}

int main() {
	float r;
	cin >> r;
	//instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
    Krug k(r);
	cout << k.perimetar() << endl;
	cout << k.plostina() << endl;
	cout << k.ednakvi() <<endl;
    //instanciraj objekt od klasata Krug cij radius ne e definiran
	return 0;
}