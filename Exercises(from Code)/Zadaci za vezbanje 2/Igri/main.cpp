#include <iostream>
#include <cstring>

using namespace std;
class ExistingGame{
    private:
        char msg[100];
    public:
        ExistingGame(const char * msg){
            strcpy(this->msg, msg);
        }
        const void message(){
            cout << this->msg << "\n";
        }
};

class Game{
    protected:
        char name[100];
        double price;
        bool onSale;
    public:
            Game(){
                strcpy(this->name, "None");
                this->price = 0.0;
                this->onSale = false;
            }
            Game(const char * name, const double price, const bool onSale){
                strcpy(this->name, name);
                this->price = price;
                this->onSale = onSale;
            }
            ~Game(){}
            friend istream &operator >>(istream &is, Game &orig){
                is.get();
                is.getline(orig.name,100);
                is >> orig.price;
                is >> orig.onSale;

                return is;
            }
            friend ostream &operator <<(ostream &os, Game &orig){
                os << "Game: " << orig.name << ", regular price: " << "$" << orig.price;
                if(orig.onSale)
                os << ", bought on sale";

                return os;
            }
            bool operator==(const Game &orig){
                if(!(strcmp(this->name, orig.name)))
                    return true;
                else
                    return false;
            }
            virtual const double getPrice(){
                if(this->onSale)
                    return this->price * 0.3;

                return this->price;
            }
            virtual const bool getSale(){
                return this->onSale;
            }
};

class SubscriptionGame : public Game {
    private:
        double monthlyFee;
        int month;
        int year;
    public:
        SubscriptionGame(){
            this->monthlyFee = 0.0;
            this->month = 0;
            this->year = 0;
        }
        SubscriptionGame(const char * name, const double price, const bool onSale, const double monthlyFee, const int month, const int year) : Game(name, price, onSale){
            this->monthlyFee = monthlyFee;
            this->month = month;
            this->year = year;
        }
        ~SubscriptionGame(){}
        friend istream &operator >>(istream &is, SubscriptionGame &orig){
                is.get();
                is.getline(orig.name,100);
                
                is >> orig.price;
                is >> orig.onSale;
                is >> orig.monthlyFee;
                is >> orig.month;
                is >> orig.year;

                return is;
            }
            friend ostream &operator <<(ostream &os, SubscriptionGame &orig){
                os << "Game: " << orig.name << ", regular price: " << "$" << orig.price;
                if(orig.onSale)
                    os << ", bought on sale";
                os << ", monthly fee: " << "$" << orig.monthlyFee << ", purchased: " << orig.month << "-" << orig.year << "\n";
                

                return os;
            }
            const double getMonthlyFee(){
                return this->monthlyFee;
            }
            const int getMonth(){
                return this->month;
            }
            const int getYear(){
                return this->year;
            }
            const double getPrice(){
                float price = Game::getPrice();

                int months = 0;
                if(year < 2018)
                    months = (12 - this->month) + (2017 - year) * 12 + 5;
                else
                    months = 5 - this->month;

                price += months * this->monthlyFee;
                
                return price;
            }
};

class User{
    private:
        char userName[100];
        Game ** games;
        int noGames;
        const void copy_obj(const User &orig){
            strcpy(this->userName, orig.userName);
            this->games = new Game *[orig.noGames + 1];
            for(int i=0; i<orig.noGames; i++)
                this->games[i] = orig.games[i];
            this->noGames = orig.noGames;
        }
    public:
        User(){
            strcpy(this->userName, "None");
            this->games = new Game*[0];
            this->noGames = 0;
        }
        User(const char * userName){
            strcpy(this->userName, userName);
            this->games = new Game*[0];
            this->noGames = 0;
        }
        User(const User &orig){
            this->copy_obj(orig);
        }

        User &operator=(const User &orig){
            if(this != &orig){
                delete [] this->games;
                this->copy_obj(orig);
            }
            return *this;
        }
        ~User(){
            delete [] this->games;
        }
        User &operator +=(Game &orig){
            for(int i=0; i<this->noGames; i++)
                if(*(this->games[i]) == orig)
                    throw ExistingGame("The game is already in the collection");
            
            Game ** tmp = new Game*[this->noGames + 1];
            for(int i=0; i<this->noGames; i++)
                tmp[i] = this->games[i];
            
            SubscriptionGame * sg = dynamic_cast<SubscriptionGame *>(&orig);
            if(sg)
                tmp[this->noGames++] = new SubscriptionGame(*sg);
            else
                tmp[this->noGames++] = new Game(orig);

            delete [] this->games;
            this->games = tmp;

            return *this;
        }

        const double total_spent(){
            double total = 0.0; 
            for(int i=0; i<this->noGames; i++)
                total += this->games[i]->getPrice();
            
            return total;
        }
        friend ostream & operator<<(ostream &o, const User &u){
            o<<"\nUser: "<<u.userName<<"\n";
 
            for (int i=0; i < u.noGames; ++i){
                Game * g;
                SubscriptionGame * sg;
                g = &(*u.games[i]);
                
                sg = dynamic_cast<SubscriptionGame *> (g);
                
                if (sg){
                    cout<<"- "<<(*sg);
                }
                else {
                    cout<<"- "<<(*g);
                }
                cout<<"\n";
            }
            return o;
        }   
};



int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}
