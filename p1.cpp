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
void login(string, int*, char*, ofstream&);
void  login_success(ofstream&);

int main(){
  string username, password;
  char *pw;
  int length=0, *scrambled_pw;
  ofstream file;

  username=set_username(username);
  password=set_password(password, pw, length);
  scrambled_pw=scramble_password(password, pw, length, scrambled_pw);

  for(int i=0; i<50; i++){
    cout << endl;
  }

  cout << "Login:\n";

  // cout << "The password is " << password << endl;
  login(username, scrambled_pw, pw, file);

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

void login(string username, int* scrambled_pw, char* pw, ofstream& file){
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
    // cout << "the login_pass is " << login_pass << endl;
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
    login_success(file);
  }
}

void login_success(ofstream& file){
  string file_name, frame;
  time_t now = time(0);

  cout << "You've logged in successfully!\n\nThe time is " << asctime(localtime(&now)) << endl;
  cout << "Enter a file to write to: ";
  cin >> file_name;
  file.open(file_name.c_str());
  while(!file){
    cout << "Invalid. File doesn't exist. Try again: ";
    cin >> file_name;
    file.open(file_name.c_str());
    getline(cin, file_name);
  }

  cin.ignore(); //Clears the cin buffer which allows getline
  cout << "What do you want to output?: ";
  getline(cin, frame);

  file << frame << endl;

  file.close();

}
