#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

//prototypes
string set_username(string);
string set_password(string, char*, int, int);
int* scramble_password(string, char*, int, int*);
void login(string, int*);

int main(){
  string username, password;
  char *pw;
  int length=0, trigger=0, *scrambled_pw;

  username=set_username(username);
  password=set_password(password, pw, length, trigger);
  scrambled_pw=scramble_password(password, pw, length, scrambled_pw);

  login(username, scrambled_pw);

  return 0;
}

string set_username(string username){
  cout << "Enter a username: ";
  cin >> username;
  return username;
}

string set_password(string password, char* pw, int length, int trigger){
  while(trigger<3){
    cout << "Enter a password\n(Password must be at least 6 characters long, contain a number, and a capital letter)\n";
    cin >> password;

    length = password.length();

    pw = new char[length];

    strcpy(pw, password.c_str());

    for(int i=0; i<length; i++){
      if(length>6){
        trigger++;
      }
      for(int j=48; j<58; j++){
        if(pw[i]==j){
          trigger++;
        }
      }
      for(int k=65; k<91; k++){
        if(pw[i]==k){
          trigger++;
        }
      }
    }

    if(trigger<3){
      cout << "Error, not a valid password. Try again.\n";
    }
  }
  return password;
}

int* scramble_password(string password, char* pw, int length, int* scrambled_pw){
  length = password.length();
  pw = new char[length];
  scrambled_pw = new int[length];
  strcpy(pw, password.c_str());

  for(int i=0; i<length; i++){
    scrambled_pw[i]=(((pw[i]*6)+19)/2)*16; //This is the algorithm to "encrypt" the password. Take the ASCII Dec. value of each value of the password, and then multiply it by 6, then add 19, then divide by 2, then multiply that number by 16. It's my birth day and month and then this year. 06192016.
  }


  return scrambled_pw;
}

void login(string username, int* scrambled_pw){
  string login_user, login_pass;

  cout << "What is your username?: ";
  cin >> login_user;

  cout << "What is your password?: ";
  cin >> login_pass;


}
