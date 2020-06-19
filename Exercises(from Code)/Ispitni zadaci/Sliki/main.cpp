#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image{
    protected:
        char * name;
        char userName[50];
        int width;
        int height;
        const void copy_obj(const Image &orig){
            this->name = new char[strlen(orig.name)+1];
            strcpy(this->name, orig.name);
            strcpy(this->userName, orig.userName);
            this->width = orig.width;
            this->height = orig.height;
        }
    public:
        Image(){
            this->name = new char[10];
            strcpy(this->name, "untitled");
            strcpy(this->userName, "unknown");
            this->width = 800;
            this->height = 800;
        }
        Image(const char * name){
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
            strcpy(this->userName, "unknown");
            this->width = 800;
            this->height = 800;
        }
        Image(const char * name, const char * userName){
            this->name = new char[strlen(name)+1];
            strcpy(this->name, name);
            strcpy(this->userName, userName);
            this->width = 800;
            this->height = 800;
        }
        Image(const char * name, const char * userName, const int width, const int height){
            this->name = new char[strlen(name)+1];
            strcpy(this->name, name);
            strcpy(this->userName, userName);
            this->width = width;
            this->height = height;
        }
        Image(const Image &orig){
            this->copy_obj(orig);
        }
        Image &operator=(const Image &orig){
            if(this != &orig){
                delete [] this->name;
                this->copy_obj(orig);
            }
            return *this;
        }
        ~Image(){
            delete [] this->name;
        }
        virtual const int fileSize(){
            return this->width * this->height * 3;
        }
        const int getTotalPixels(){
            return this->width * this->height;
        }
        friend ostream &operator <<(ostream &os, Image &orig){
            os << orig.name << " " << orig.userName << " " << orig.fileSize() << "\n";
            return os;
        }
        bool operator>(Image &orig){
            if(this->fileSize() > orig.fileSize())
                return true;
            else
                return false;
        }
};

class TransparentImage : public Image{
    private:
        bool isTransparent;
    public:
        TransparentImage(){
            this->isTransparent = true;
        }
        TransparentImage(const char * name, const char * userName, const int width, const int height, const bool isTransparent) : Image(name, userName, width, height){
            this->isTransparent = isTransparent;
        }
        const int fileSize(){
            if(this->isTransparent == true)
                return this->width * this->height * 4;
            else
                return this->width * this->height + this->getTotalPixels() / 8;
        }

};

class Folder{
    private:
        char name[255];
        char owner[50];
        Image ** img;
        int n;
        const void copy_obj(const Folder &orig){
            strcpy(this->name, orig.name);
            strcpy(this->owner, orig.owner);
            this->img = new Image*[orig.n + 1];
            for(int i=0; i<orig.n; i++)
                this->img[i] = orig.img[i];
            this->n = orig.n;
        }
    public:
        Folder(){
            strcpy(this->name, "untitled");
            strcpy(this->owner, "uknown");
            this->img = new Image*[0];
            this->n = 0;
        }
        Folder(const char * name, const char * owner){
            strcpy(this->name, name);
            strcpy(this->owner, owner);
            this->img = new Image*[0];
            this->n = 0;
        }
        Folder(const Folder &orig){
            this->copy_obj(orig);
        }
        Folder &operator=(const Folder &orig){
            if(this != &orig){
                delete [] this->img;
                this->copy_obj(orig);
            }
            return *this;
        }
        Folder &operator += (Image &orig){
            Image ** tmp = new Image*[this->n + 1];
            for(int i=0; i<this->n; i++)
                tmp[i] = this->img[i];
            tmp[this->n++] = &orig;
            delete [] this->img;
            this->img = tmp;

            return *this;
        }
        ~Folder(){
            delete [] this->img;
        }
        const int folderSize(){
            int sum=0;
            for(int i=0; i<this->n; i++)
                sum += this->img[i]->fileSize();
            return sum;
        }
        Image * getMaxFile(){
            int max = this->img[0]->fileSize();
            int index = 0;
            for(int i=1; i<this->n; i++){
                if(this->img[i]->fileSize() > max){
                    max = this->img[i]->fileSize();
                    index = i;
                }
            }
            return this->img[index];
        }
        
        friend ostream &operator <<(ostream &os, Folder &orig){
            os << orig.name << " " << orig.owner << "\n";
            os << "--\n";
            for(int i=0; i<orig.n; i++)
                os << *orig.img[i];
            os << "--\n" << "Folder size: " << orig.folderSize();
            return os;
        }
        Image * &operator[](int i){
            return this->img[i];
        }
};

void max_folder_size(Folder * fdl, int n){
    int max=fdl[0].folderSize();
    int index = 0;
    for(int i=1; i<n; i++){
        if(fdl[i].folderSize() > max){
            max = fdl[i].folderSize();
            index = i;
        }
    }
    cout << fdl[index];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
        
      }

    max_folder_size(dir_list, folders_num);

    }
    return 0;
};
