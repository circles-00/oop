/*NBA Problem 3 (0 / 0)
NBAPlayer

Да се дефинира класа NBAPlayer за која ќе се чуваат:

    динамички алоцирана низа од карактери за името на играчот
    низа од максимум 40 карактери за тимот во кој играчот моментално настапува
    просечен број на поени на играчот оваа сезона (double)
    просечен број на асистенции на играчот оваа сезона (double)
    просечен број на скокови на играчот оваа сезона (double)

За потребите на класата да се дефинираат:

    default конструктор и конструктор со аргументи
    copy constructor и оператор =
    деструктор

    метод rating() кој го враќа рејтингот на кошаркарот кој се пресметува како:

    45% од поените + 30% од асистенциите + 25% од скоковите

    метод print() кој го печати играчот во следниот формат:

    Име - тим

    Points: поени

    Assists: асистенции

    Rebounds: скокови

    Rating: рејтинг

AllStarPlayer

Од претходната класа NBAPlayer да се изведе класата AllStarPlayer за која дополнително ќе се чуваат и:

    просечен број на поени на играчот од All Star натпреварите (double)
    просечен број на асистенции на играчот од All Star натпреварите (double)
    просечен број на скокови на играчот од All Star натпреварите (double)

За потребите на класата да се дефинираат:

    default конструктор
    конструктор кој прима објект од NBAPlayer и плус додатните информации (погледни main)
    конструктор кој ги прима сите аргументи (погледни main)
    copy constructor, оператор =, деструктор

    метод allStarRating() кој го враќа рејтингот на кошаркарот од All Star натпреварите и кој се пресметува како:

    30% од поените + 40% од асистенциите + 30% од скоковите

Да се препокријат методите:

    rating() кој го враќа просекот од обичниот рејтинг на кошаркарот и неговиот All Star рејтинг

    print() кој покрај основните информации за кошаркарот печати и:

    All Star Rating: рејтингот од All Star натпреварите

    New Rating: просечниот рејтинг

*/

#include <iostream>
#include <cstring>

using namespace std;

class NBAPlayer{
    protected:
        char * name;
        char team[40];
        double avgPoints;
        double avgAssists;
        double avgJumps;
        void copy(const NBAPlayer &orig){
            this->name = new char[strlen(orig.name)+1];
            strcpy(this->name, orig.name);
            strcpy(this->team, orig.team);
            this->avgPoints = orig.avgPoints;
            this->avgAssists = orig.avgAssists;
            this->avgJumps = orig.avgJumps;
        }
    public:
        NBAPlayer();
        NBAPlayer(const char * name, const char * team, const double avgPoints, const double avgAssists, const double avgJumps);
        NBAPlayer(const NBAPlayer &orig);
        NBAPlayer &operator=(const NBAPlayer &orig);
        ~NBAPlayer();
        const double rating();
        void print();
};

NBAPlayer::NBAPlayer(){
    this->name = new char[0];
    strcpy(this->name, "");
    strcpy(this->team, "");
    this->avgPoints = 0;
    this->avgAssists = 0;
    this->avgAssists = 0;
}
NBAPlayer::NBAPlayer(const char * name, const char * team, const double avgPoints, const double avgAssists, const double avgJumps){
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    strcpy(this->team, team);
    this->avgPoints = avgPoints;
    this->avgAssists = avgAssists;
    this->avgJumps = avgJumps;
}
NBAPlayer::NBAPlayer(const NBAPlayer &orig){
    this->copy(orig);
}
NBAPlayer &NBAPlayer::operator=(const NBAPlayer &orig){
    if(this != &orig){
        delete [] this->name;
        this->copy(orig);
    }
    return *this;
}
NBAPlayer::~NBAPlayer(){
    delete [] this->name;
}
const double NBAPlayer::rating(){
    return ((this->avgPoints * 0.45) + (this->avgAssists * 0.3) + (this->avgJumps * 0.25));
}
void NBAPlayer::print(){
    cout << this->name << " - " << this->team << endl;
    cout << "Points: " << this->avgPoints << endl;
    cout << "Assists: " << this->avgAssists << endl;
    cout << "Rebounds: " << this->avgJumps << endl;
    cout << "Rating: " << this->rating() << endl;
}

//class AllStarPlayer
class AllStarPlayer : public NBAPlayer{
    private:
        double avgAllStarPoints;
        double avgAllStarAssists;
        double avgAllStarJumps;
        void copy(const AllStarPlayer &orig){
            this->name = new char[strlen(orig.name)+1];
            strcpy(this->name, orig.name);
            strcpy(this->team, orig.team);
            this->avgPoints = orig.avgPoints;
            this->avgAllStarJumps = orig.avgAssists;
            this->avgJumps = orig.avgJumps;
            this->avgAllStarPoints = orig.avgAllStarPoints;
            this->avgAllStarAssists = orig.avgAllStarAssists;
            this->avgAllStarJumps = orig.avgAllStarJumps;
        }
    public:
        AllStarPlayer();
        AllStarPlayer(const NBAPlayer &orig, const double avgAllStarPoints, const double avgAllStarAssists, const double avgAllStarJumps) : NBAPlayer(orig){
            this->avgAllStarPoints = avgAllStarPoints;
            this->avgAllStarAssists = avgAllStarAssists;
            this->avgAllStarJumps = avgAllStarJumps;
        }
        AllStarPlayer(const char * name, const char * team, const double avgPoints, const double avgAssists, const double avgJumps, const double avgAllStarPoints, const double avgAllStarAssists, const double avgAllStarJumps) : NBAPlayer(name, team, avgPoints, avgAssists, avgJumps){
            this->avgAllStarPoints = avgAllStarPoints;
            this->avgAllStarAssists = avgAllStarAssists;
            this->avgAllStarJumps = avgAllStarJumps;
        }
        AllStarPlayer(const AllStarPlayer &orig);
        AllStarPlayer &operator=(const AllStarPlayer &orig);
        ~AllStarPlayer();
        const double allStarRating();
        const double rating();
        void print();
};

AllStarPlayer::AllStarPlayer(){
    this->avgAllStarPoints = 0;
    this->avgAllStarAssists = 0;
    this->avgAllStarJumps = 0;
}
AllStarPlayer::AllStarPlayer(const AllStarPlayer &orig){
    this->copy(orig);
}
AllStarPlayer &AllStarPlayer::operator=(const AllStarPlayer &orig){
    if(this != &orig){
        delete [] this->name;
        this->copy(orig);
    }
    return *this;
}
AllStarPlayer::~AllStarPlayer(){}
const double AllStarPlayer::allStarRating(){
    return ((this->avgAllStarPoints * 0.3) + (this->avgAllStarAssists * 0.4) + (this->avgAllStarJumps * 0.3));
}
const double AllStarPlayer::rating(){
    return ((NBAPlayer::rating() + this->allStarRating())/2.0);
}
void AllStarPlayer::print(){
    NBAPlayer::print();
    cout << "All Star Rating: " << this->allStarRating() << endl;
    cout << "New Rating: " << this->rating() << endl;
}

//main
int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }
    
    delete [] players;
    delete [] asPlayers;
}
