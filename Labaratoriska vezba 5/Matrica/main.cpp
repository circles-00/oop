#include <iostream>
#include <cstring>

using namespace std;

//vashiot kod ovde
class Matrica{
    private:
        float mat[10][10];
        int red;
        int kol;
    public:
        Matrica(){
            this->red = 0;
            this->kol = 0;
            for(int i=0; i<10; i++){
                for(int j=0; j<10; j++){
                    this->mat[i][j] = 0;
                }
            }
        }

        friend istream & operator >> (istream &input,  Matrica &m){
            input >> m.red;
            input >> m.kol;
            for(int i=0; i<m.red; i++){
                for(int j=0; j<m.kol; j++){
                   input >> m.mat[i][j];
                }    
            }
            return input;
        }

        friend ostream & operator << (ostream &output, Matrica &m){
            for(int i=0; i<m.red; i++){
                for(int j=0; j<m.kol; j++){
                   cout << m.mat[i][j] << " ";
                }
                cout << "\n";
            }
            return output;
        }

        Matrica operator+(const int n){
            for(int i=0; i<this->red; i++){
                for(int j=0; j<this->kol; j++){
                    this->mat[i][j] += n;
                }
            }
            return *this;
        }

        Matrica operator-(const Matrica &m){
            for(int i=0; i<this->red; i++){
                for(int j=0; j<this->kol; j++){
                    this->mat[i][j] -= m.mat[i][j];
                }
            }
            return *this;
        }

        Matrica operator*(const Matrica &m){
            Matrica temp;
            for(int i=0; i<this->red; i++){
                for(int j=0; j<this->kol; j++){
                    for(int k=0; k<this->red; k++)
                        temp.mat[i][j]+= this->mat[i][k] * m.mat[k][j];
                }
            }
            return temp;
        }
};

//main
int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;
    cout<<R;
}