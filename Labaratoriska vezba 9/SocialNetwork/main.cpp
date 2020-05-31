#include <iostream>
#include <cstring>

using namespace std;

class InvalidPassword{
    public:
        InvalidPassword(){}
        const void message(){
            cerr << "Password is too weak." << endl;
        }
};

class InvalidEmail{
    public:
        InvalidEmail(){}
        const void message(){
            cerr << "Mail is not valid." << endl;
        }
};

class MaximumSizeLimit{
    private:
        int maxSize;
    public:
        MaximumSizeLimit(){
            this->maxSize = 0;
        }
        MaximumSizeLimit(const int maxSize){
            this->maxSize = maxSize;
        }
        ~MaximumSizeLimit(){}
        const void message(){
            cerr << "You can't add more than " << this->maxSize << " users." << endl;
        }
};


class User{
    protected:
        char username[50];
        char password[50];
        char email [50];
        bool checkpw(const char * pw){
            int lower = 0; int upper = 0; int digits = 0;
            for(int i=0; i<strlen(pw); i++){
                if(isupper(pw[i]))
                    upper++;
                else if(islower(pw[i]))
                    lower++;
                else if(isdigit(pw[i]))
                    digits++;
            }
            if(lower < 1 || upper < 1 || digits < 1)
                return false;
            else
                return true;
        }
        bool checkmail(const char * mail){
            int at = 0;
            for(int i=0; i<strlen(mail); i++){
                if(mail[i] == 64)
                    at++;
            }
            if(at == 1)
                return true;
            else
                return false;
        }
    public:
        User(){
            strcpy(this->username, "Uknown UserName");
            strcpy(this->password, "Uknown Password");
            strcpy(this->email, "uknown email");
        }
        User(const char * username, const char * password, const char * email){
            if(checkpw(password) == false)
                throw InvalidPassword();
            if(checkmail(email) == false)
                throw InvalidEmail();
            strcpy(this->username, username);
            strcpy(this->password, password);
            strcpy(this->email, email);
        }
        ~User(){}
        virtual const double popularity() = 0;
};

class FacebookUser : public User{
    private:
        int friends;
        int likes;
        int comments;
    public:
        FacebookUser(){
            this->friends = 0;
            this->likes = 0;
            this->comments = 0;
        }
        FacebookUser(const char * username, const char * password, const char * email, const int friends, const int likes, const int comments) : User(username, password, email){
            this->friends = friends;
            this->likes = likes;
            this->comments = comments;
        }
        ~FacebookUser(){}
        const double popularity(){
            return this->friends + (this->likes * 0.1) + (this->comments * 0.5);
        }
};

class TwitterUser : public User{
    private:
        int followers;
        int tweets;
    public:
        TwitterUser(){
            this->followers = 0;
            this->tweets = 0;
        }
        TwitterUser(const char * username, const char * password, const char * email, const int followers, const int tweets) : User (username, password, email){
            this->followers = followers;
            this->tweets = tweets;
        }
        ~TwitterUser(){}
        const double popularity(){
            return this->followers + (this->tweets * 0.5);
        }
};

class SocialNetwork{
    private:
        User ** u;
        int noUsers;
        static int maxSize;
    public:
        SocialNetwork(){
            this->u = new User*[0];
            this->noUsers = 0;
        }
        ~SocialNetwork(){
            delete [] this->u;
        }
        static void changeMaximumSize(const int newMax){
            maxSize = newMax;
        }
        SocialNetwork &operator+=(User *orig){
            if(this->noUsers >= maxSize)
                throw MaximumSizeLimit(maxSize);
            
            User **tmp = new User*[this->noUsers + 1];
            for(int i=0; i<this->noUsers; i++)
                tmp[i] = this->u[i];
            tmp[this->noUsers++] = orig;
            delete [] this->u;
            this->u = tmp;

            return *this;
        }
        const double avgPopularity(){
            double sum = 0.0;
            for(int i=0; i<this->noUsers; i++)
                sum += this->u[i]->popularity();
            return sum / this->noUsers;
        }

};
int SocialNetwork::maxSize = 5;



int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;
          
        // TODO: Try-catch
        try{
            User * u = new FacebookUser(username,password,email,friends,likes,comments);
            network += u;
        }
        catch(InvalidPassword &pw){
            pw.message();
        }
        catch(InvalidEmail &mail){
            mail.message();
        }
        catch(MaximumSizeLimit &maxSize){
            maxSize.message();
        }
          
      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;
          
        // TODO: Try-catch  
        try{
            User * u= new TwitterUser(username,password,email,followers,tweets);
            network += u;
        }
        catch(InvalidPassword &pw){
            pw.message();
        }
        catch(InvalidEmail &mail){
            mail.message();
        }
        catch(MaximumSizeLimit &maxSize){
            maxSize.message();
        }
      }
    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;
    
    // TODO: Try-catch
    try{
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
    }
    
    catch(InvalidPassword &pw){
        pw.message();
    }
    catch(InvalidEmail &mail){
        mail.message();
    }
    catch(MaximumSizeLimit &maxSize){
        maxSize.message();
    }
    cout << network.avgPopularity();

}
