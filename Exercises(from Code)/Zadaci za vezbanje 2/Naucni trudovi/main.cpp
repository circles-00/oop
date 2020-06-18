#include <iostream>
#include <cstring>

using namespace std;

class Exception{
    private:
        char msg[256];
    public:
        Exception(const char * msg){
            strcpy(this->msg, msg);
        }
        ~Exception(){}
        const void print(){
            cout << this->msg << "\n";
        }
};


class Trud{
    private:
        char vid;
        int god;
        static int C;
        static int J;
    public:
        Trud(){
            this->vid = 'c';
            this->god = 1970;
        }
        Trud(const char vid, const int god){
            this->vid = vid;
            this->god = god;
        }
        ~Trud(){}
        friend istream &operator >> (istream &is, Trud &orig){
            is >> orig.vid >> orig.god;

            return is;
        }
        const char getVid(){
            return this->vid;
        }
        const int getGod(){
            return this->god;
        }
        static int getC(){
            return C;
        }
        static int getJ(){
            return J;
        }
        static void setC(int newC){
            C = newC;
        }
        static void setJ(int newJ){
            J = newJ;
        }
};
int Trud::C = 1;
int Trud::J = 3;

class Student{
    private:
        char ime[30];
        int index;
        int godUpis;
        int * polozeni;
        int brojPolozeni;
        const void copy_obj(const Student &orig){
            strcpy(this->ime, orig.ime);
            this->index = orig.index;
            this->godUpis = orig.godUpis;
            for(int i=0; i<orig.brojPolozeni; i++)
                this->polozeni[i] = orig.polozeni[i];
            this->brojPolozeni = orig.brojPolozeni;
        }
    public:
        Student(){
            strcpy(this->ime, "Nema Ime");
            this->index = 0;
            this->godUpis = 1970;
            this->polozeni = new int[0];
            this->brojPolozeni = 0;
        }
        Student(const char * ime, const int index, const int godUpis, const int * polozeni, const int brojPolozeni){
            strcpy(this->ime, ime);
            this->index = index;
            this->godUpis = godUpis;
            this->polozeni = new int[brojPolozeni + 1];
            for(int i=0; i<brojPolozeni; i++)
                this->polozeni[i] = polozeni[i];
            this->brojPolozeni = brojPolozeni;
        }
        Student(const Student &orig){
            this->copy_obj(orig);
        }
        Student &operator=(const Student &orig){
            if(this != &orig){
                delete [] this->polozeni;
                this->copy_obj(orig);
            }
            return *this;
        }
        ~Student(){
            delete [] this->polozeni;
        }
        virtual const double rang(){
            double sum = 0.0;
            for(int i=0; i<this->brojPolozeni; i++)
                sum += this->polozeni[i];
            return sum / this->brojPolozeni;
        }
        friend ostream &operator << (ostream &os, Student &orig){
            os << orig.index << " " << orig.ime << " " << orig.godUpis << " " << orig.rang() << "\n";

            return os;
        }
        const int getUpis(){
            return this->godUpis;
        }
        const int getIndex(){
            return this->index;
        }
};

class PhDStudent : public Student{
    private:
        Trud * ts;
        int brojTs;
        const void copy_obj(const PhDStudent &orig){
            for(int i=0; i<orig.brojTs; i++)
                this->ts[i] = orig.ts[i];
            this->brojTs = orig.brojTs;
        }
    public:
        PhDStudent(){
            this->ts = new Trud[0];
            this->brojTs = 0;
        }
        PhDStudent(const char * ime, const int index, const int godUpis, const int * polozeni, const int brojPolozeni, Trud * ts, const int brojTs) : Student(ime, index, godUpis, polozeni, brojPolozeni){
            this->ts = new Trud[brojTs + 1];
            for(int i=0; i<brojTs; i++){
                try{
                    if(ts[i].getGod() < this->getUpis())
                        throw Exception("Ne moze da se vnese dadeniot trud");
                    this->ts[i] = ts[i];
                }
                catch(Exception &ex){
                    ex.print();
                }       
            }
            this->brojTs = brojTs;   
        }
        PhDStudent(const PhDStudent &orig) : Student(orig){
            this->copy_obj(orig);
        }
        PhDStudent &operator=(const PhDStudent &orig){
            if(this != &orig){
                delete [] this->ts;
                Student::operator=(orig);
                this->copy_obj(orig);
            }
            return *this;
        }
        ~PhDStudent(){
            delete [] this->ts;
        }
        double const rang(){
            int poeni = 0;
            for(int i=0; i<this->brojTs; i++){
                if(this->ts[i].getVid() == 'c' || this->ts[i].getVid() == 'C')
                    poeni += ts[i].getC();
                else if(this->ts[i].getVid() == 'j' || this->ts[i].getVid() == 'J')
                    poeni += ts[i].getJ();
            }
            return Student::rang() + poeni;
        }
        PhDStudent &operator+=(Trud &orig){
            if(orig.getGod() < this->getUpis())
                throw Exception("Ne moze da se vnese dadeniot trud");

            Trud * tmp = new Trud[this->brojTs + 1];
            for(int i=0; i<this->brojTs; i++)
                tmp[i] = this->ts[i];
            tmp[this->brojTs++] = orig;
            delete [] this->ts;
            this->ts = tmp;

            return *this;
        }
};

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent 
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
        
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        for(int i=0; i<m; i++){
            PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
            if(tmp && tmp->getIndex() == indeks)
                try{
                    *tmp += t;
                }
            catch(Exception &ex){
                ex.print();
            }
        }
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
        
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for(int i=0; i<m; i++){
            PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
            if(tmp && tmp->getIndex() == indeks)
                try{
                    *tmp += t;
                }
            catch(Exception &ex){
                ex.print();
            }
        }

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
        
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        for(int i=0; i<m; i++){
            try{
                PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
                if(tmp && tmp->getIndex() == indeks)
                        *tmp += t;
            }
            catch(Exception &ex){
                ex.print();
            }
        }
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;
		
        //postavete gi soodvetnite vrednosti za statickite promenlivi 
        Trud::setC(conf);
        Trud::setJ(journal);
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}