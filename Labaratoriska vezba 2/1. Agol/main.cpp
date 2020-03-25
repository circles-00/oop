#include <iostream>
using namespace std;

class Agol {
    private:
        int deg, min, sec;
    public:
        void set_stepeni(int degs);
        void set_minuti(int mins);
        void set_sekundi(int secs);
        int getSekundi();
        int to_sekundi();
};

void Agol::set_stepeni(int degs) {
            deg=degs;
}
void Agol::set_minuti(int mins) {
            min=mins;
}
void Agol::set_sekundi(int secs) { 
            sec=secs;
}
int Agol::getSekundi() {
            return sec;
}
int Agol::to_sekundi() {
            return (deg*60*60) + (min*60) + sec;
}

bool proveri(int deg, int min, int sec) {
    if(deg >=0 &&deg < 360 && min >=0 && min < 60 && sec >= 0 && sec < 60)
        return true;
    else 
        return false;
}

bool changeOfSeconds(Agol a, int sec){
	return a.getSekundi()!=sec;
}

int main() {
    
    //da se instancira objekt od klasata Agol
    Agol a1;
    int deg, min, sec;
    cin >> deg >> min >> sec;
    
    if (proveri(deg, min, sec)) {
    	a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
			cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;
    } else 
        cout << "Nevalidni vrednosti za agol" << endl;
    return 0;
}