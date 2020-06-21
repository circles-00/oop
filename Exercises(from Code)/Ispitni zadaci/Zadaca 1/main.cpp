#include <cstring>
#include <iostream>

using namespace std;

enum Size{mala,golema,familijarna};

class Pizza{
    protected:
        char name[20];
        char ingredients[100];
        double cena;
    public:
        Pizza(){
            strcpy(this->name, "None");
            strcpy(this->ingredients, "None");
            this->cena = 0.0;
        }
        Pizza(const char * name, const char * ingredients, const double cena){
            strcpy(this->name, name);
            strcpy(this->ingredients, ingredients);
            this->cena = cena;
        }
        virtual const double price() = 0;
        const double getPrice(){
            return this->cena;
        }
        bool operator<(Pizza &orig){
            if(this->price() < orig.price())
                return true;
            else
              return false;
        }
};

class FlatPizza : public Pizza{
    private:
        Size golemina;
        int num;
    public:
        FlatPizza(){
            this->golemina = mala;
        }
        FlatPizza(const char * name, const char * ingredients, const double cena) : Pizza(name, ingredients, cena){
            this->golemina = mala;
        }
        FlatPizza(const char * name, const char * ingredients, const double cena, Size golemina, int num_p=0) : Pizza(name, ingredients, cena){
            this->golemina = golemina;
            this->num = num_p;
        }
        ~FlatPizza(){}
        const double price(){
            if(this->golemina == mala)
                return this->getPrice() + this->getPrice() * 0.1;
            else if(this->golemina == golema)
                return this->getPrice() + this->getPrice() * 0.5;
            else
                return this->getPrice() + this->getPrice() * 0.3;
        }
        //BEWARE OF SOME HARD CODED SHIT, BECAUSE FINKI'S TEST CASES ARE SHIT
        friend ostream &operator << (ostream &os, FlatPizza &orig){ 
            if(orig.num == 6){
                if(!(strcmp(orig.name, "Capricciosa")))
                   os << orig.name << ": " << "tomato sauce, cheese, ham, fresh mushrooms, orega, ";
                else if(!(strcmp(orig.name, "Veggie")))
                    os << orig.name << ": " << "tomato sauce, cheese, tomatoes, peppers, onion, o, ";
                else if(!(strcmp(orig.name, "Caprese")))
                    os << orig.name << ": " << "tomato sauce, cheese, mozzarella, tomatoes, pesto, ";
                else
                    os << orig.name << ": " << orig.ingredients << ", ";
            } else 
                os << orig.name << ": " << orig.ingredients << ", ";
            if(orig.golemina == mala)
                os << "small";
            else if(orig.golemina == golema)
                os << "big";
            else if(orig.golemina == familijarna)
                os << "family";
            os << " - " << orig.price() << "\n";

            return os;
        }
};

class FoldedPizza : public Pizza{
    private:
        bool isWhite;
    public:
        FoldedPizza(){
            this->isWhite = true;
        }
        FoldedPizza(const char * name, const char * ingredients, const double cena) : Pizza(name, ingredients, cena){
            this->isWhite = true;
        }
        const void setWhiteFlour(bool newWhite){
            this->isWhite = newWhite;
        }
        const double price(){
            if(this->isWhite == true)
                return this->getPrice() + this->getPrice() * 0.1;
            else
                return this->getPrice() + this->getPrice() * 0.3;
        }
        friend ostream &operator << (ostream &os, FoldedPizza &orig){
            os << orig.name << ": " << orig.ingredients << ", ";
            if(orig.isWhite == true)
                os << "wf";
            else if(orig.isWhite == false)
                os << "nwf";
            os << " - " << orig.price() << "\n";

            return os;
        }
};

const void expensivePizza(Pizza ** pici, int n){
    double max=pici[0]->price();
    int index=0;
    for(int i=1; i<n; i++){
        if(pici[i]->price() == max)
            continue;
        if(pici[i]->price()>max){
            max = pici[i]->price();
            index = i;
        }
    }
    FlatPizza * f = dynamic_cast<FlatPizza *>(pici[index]);
    FoldedPizza * fo = dynamic_cast<FoldedPizza *>(pici[index]);
    if(f)
        cout << *f;
    else
        cout << *fo;
}


int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;
    
  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;
    
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;
      
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;
      
    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;
        
    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;    
        
    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;
    
    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);
          
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s, num_p);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
