#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h> //Includes the "getpass" function. This lets the user type without it actually being displayed on screen.
#include <fstream>
#include <ctime> //Includes time

using namespace std;

//prototypes
string set_username(string);
string set_password(string, char*, int);
int* scramble_password(string, char*, int, int*);
void login(string, int*, char*);
void login_success(string);
void read_file();
void decrypt_file();
void write_to_file();

int main(){
  string username, password;
  char *pw;
  int length=0, *scrambled_pw;

  username=set_username(username);
  password=set_password(password, pw, length);
  scrambled_pw=scramble_password(password, pw, length, scrambled_pw);

  for(int i=0; i<50; i++){
    cout << endl;
  }

  cout << "Login:\n";

  // cout << "The password is " << password << endl;
  login(username, scrambled_pw, pw);

  return 0;
}

string set_username(string username){
  cout << "Enter a username: ";
  cin >> username;
  return username;
}

string set_password(string password, char* pw, int length){
  int leg_trig=0, num_trig=0, cap_trig=0;
  bool valid=false;

  while(valid==false){
    password=getpass("Enter a password\n(Password must be at least 6 characters long, contain a number, and a capital letter)\n");

    length=password.length();

    pw=new char[length];

    strcpy(pw, password.c_str()); //Copies the password into a character array for review

    for(int i=0; i<length; i++){ //Checks for the length of the password
      if(length>6){
        leg_trig++;
      }
      for(int j=48; j<58; j++){ //Checks for a number
        if(pw[i]==j){
          num_trig++;
        }
      }
      for(int k=65; k<91; k++){ //Checks for a capital letter
        if(pw[i]==k){
          cap_trig++;
        }
      }
    }

    if(leg_trig==0 || num_trig==0 || cap_trig==0){
      cout << "Error, not a valid password. Try again.\n";
      valid=false;
    }
    else{
      valid=true;
    }
  }

  return password;
}

int* scramble_password(string password, char* pw, int length, int* scrambled_pw){
  length=password.length();
  pw=new char[length];
  scrambled_pw=new int[length]; //Password becomes an int array
  strcpy(pw, password.c_str());

  for(int i=0; i<length; i++){
    scrambled_pw[i]=(((pw[i]*6)+19)/2)*16; //This is the algorithm to "encrypt" the password. Take the ASCII Dec. value of each value of the password, and then multiply it by 6, then add 19, then divide by 2, then multiply that number by 16. It's my birth day and month and then this year. 06192016.
  }


  return scrambled_pw;
}

void login(string username, int* scrambled_pw, char* pw){
  int counter=0, length=0, *login_pw_compare;
  string login_user, login_pass;
  bool user_match=false, pw_match=false;

  while(user_match==false){
    cout << "Enter your username: ";
    cin >> login_user;

    if(login_user==username){
      user_match=true;
    }
    else{
      cout << "Incorrect username. ";
      user_match=false;
    }
  }

  while(pw_match==false){
    login_pass=getpass("Enter your password: ");
    length=login_pass.length();
    pw=new char[length];
    login_pw_compare=new int[length];
    strcpy(pw, login_pass.c_str());

    for(int i=0; i<length; i++){
      login_pw_compare[i]=(((pw[i]*6)+19)/2)*16; //Converts the login password to a scrambled password using the same algorithm.
    }

    for(int i=0; i<length; i++){
      if(login_pw_compare[i]==scrambled_pw[i]){
        counter++;
      }
    }

    if(counter==length){
      pw_match=true;
    }
    else{
      cout << "Invalid. ";
      delete [] login_pw_compare;
      delete [] pw;
      pw_match=false;
    }
  }

  if(user_match==true && pw_match==true){
    login_success(login_pass);
  }
}

void login_success(string login_pass){
  time_t now = time(0); //Gets the current time
  int choice;
  bool in=true, dc_wall=false;
  string dc_pass; //decrypt_password

  cout << "\nLOGIN SUCCESS\n\nThe time is " << asctime(localtime(&now)) << endl;

  while(in==true){
    cout << "1. Read a file\n2. Decrypt a file\n3. Write to a file\n4. Logout\n";
    cin >> choice;

    if(choice==1){
      read_file();
      in=true;
    }

    if(choice==2){
      while(dc_wall==false){
        dc_pass=getpass("Re-enter your password: ");
        if(dc_pass!=login_pass){
          dc_wall=false;
        }else{
          dc_wall=true;
        }
      }
      decrypt_file();
      in=true;
    }

    if(choice==3){
      write_to_file();
      in=true;
    }

    if(choice==4){
      cout << "\nLOGOUT SUCCESS\n";
      in=false;
    }
  }

}

void read_file(){
  ifstream file;
  string file_name, line;

  cout << "Enter a file to read: ";
  cin >> file_name;
  file.open(file_name.c_str());
  while(!file.eof()){
    getline(file, line);

    cout << line;
  }

  cout << endl;
}

void decrypt_file(){
  ifstream file;
  string file_name, line, temp;
  char* decrypt;
  int length;

  cout << "\nSuccess\n";

  cout << "Enter a file to decrypt: ";
  cin >> file_name;
  file.open(file_name.c_str()); //Opens the file
  while(!file.eof()){ //Reads the file until the end
    getline(file, line); //Inputs the scanned line into a string
    length=line.length();

    decrypt = new char[length];
    strcpy(decrypt, line.c_str());

    for(int i=0; i<length; i++){ //Decrypts the string. It is the opposite of the encryption
      if(decrypt[i]==' '){
        decrypt[i]=decrypt[i]-10;
      }else{
        decrypt[i]=decrypt[i]+10;
      }
    }

    temp=decrypt; //Puts the decrypted thing into the string

    cout << temp << endl;
  }

  file.close();
}

void write_to_file(){
  ofstream file;
  string file_name, frame;
  int length;
  char* encrypt;

  cout << "Enter a file to write to: ";
  cin >> file_name;
  file.open(file_name.c_str(), ios_base::app); //ios_base::app makes it append to whatever is on the file so it doesn't clear the entire file each time you open it.

  cin.ignore(); //Clears the cin buffer which allows getline
  cout << "What do you want to output?: ";
  getline(cin, frame);

  length=frame.length(); //This gets the length for the character array used to encrypt

  encrypt = new char[length];

  strcpy(encrypt, frame.c_str()); //Copies the string into the character array

  for(int i=0; i<length; i++){ //Scans through the inputted string
    if(encrypt[i]==' '){ //If scanned element is a space, then add 10 to the ASCII value
      encrypt[i]=encrypt[i]+10;
    }else{
      encrypt[i]=encrypt[i]-10; //Else, subtract 10 from the ASCII value
    }
  }

  frame=encrypt; //Copies the array into a string

  file << frame << endl; //Appends it to the file

  file.close();
}
