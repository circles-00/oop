#include <iostream>
#include <cstring>

using namespace std;

class Book{
    protected:
        char ISBN[20];
        char title[50];
        char author[30];
        double price;
    public:
        Book(){
            strcpy(this->ISBN, "None");
            strcpy(this->title, "Uknown");
            strcpy(this->author, "No Author");
            this->price = 0.0;
        }
        Book(const char * ISBN, const char * title, const char * author, const double price){
            strcpy(this->ISBN, ISBN);
            strcpy(this->title, title);
            strcpy(this->author, author);
            this->price = price;
        }
        virtual ~Book(){}
        virtual const double bookPrice() = 0;
        bool operator>(Book &orig){
            return this->price > orig.price;
        }
        friend ostream &operator <<(ostream &os, Book &orig){
            os << orig.ISBN <<": " << orig.title << ", " << orig.author << " " << orig.bookPrice() << "\n";
            return os;
        }
};

class OnlineBook : public Book{
    private:
        char * url;
        int size;
        const void copy_obj(const OnlineBook &orig){
            strcpy(this->ISBN, orig.ISBN);
            strcpy(this->title, orig.title);
            strcpy(this->author, orig.author);
            this->price = orig.price;
            this->url = new char[strlen(orig.url)+1];
            strcpy(this->url, orig.url);
            this->size = orig.size;
        }
    public:
        OnlineBook(){
            this->url = new char[0];
            this->size = 0;
        }
        OnlineBook(const char * ISBN, const char * title, const char * author, const double price, const char * url, const int size) : Book(ISBN, title, author, price){
            this->url = new char[strlen(url)+1];
            strcpy(this->url, url);
            this->size = size;
        }
        OnlineBook(const OnlineBook &orig){
            this->copy_obj(orig);
        }
        OnlineBook &operator=(const OnlineBook &orig){
            if(this != &orig){
                delete [] this->url;
                this->copy_obj(orig);
            }
            return *this;
        }
        ~OnlineBook(){
            delete [] this->url;
        }
        const double bookPrice(){
            if(this->size>20)
                return this->price + this->price * 0.2;
            return this->price;
        }
        const void setISBN(const char * newISBN){
            strcpy(this->ISBN, newISBN);
        }
};

class PrintBook : public Book{
    private:
        double mass;
        bool isAvailable;
    public:
        PrintBook(){
            this->mass = 0.0;
            this->isAvailable = false;
        }
        PrintBook(const char * ISBN, const char * title, const char * author, const double price, const double mass, const bool isAvailable) : Book(ISBN, title, author, price){
            this->mass = mass;
            this->isAvailable = isAvailable;
        }
        ~PrintBook(){}
        const double bookPrice(){
            if(this->mass > 0.7)
                return this->price + this->price * 0.15;
            return this->price;
        }
};

void mostExpensiveBook (Book** books, int n){
    int obcount = 0; int pbcount = 0;
    Book * max = books[0];
    for(int i=0; i<n; i++){
        OnlineBook *ob = dynamic_cast<OnlineBook *>(books[i]);
        PrintBook *pb = dynamic_cast<PrintBook *>(books[i]);
        if(ob)
            obcount++;
        if(pb)
            pbcount++;
        if(*books[i] > *max)
            max = books[i];
    }
    cout << "FINKI-Education\n";
    cout << "Total number of online books: " << obcount << "\n";
    cout << "Total number of print books: " << pbcount << "\n";
    cout << "The most expensive book is: \n";
    cout << *max;
}

int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
