#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

//prototypes
string set_username(string);
string set_password(string, char*, int, int);

int main(){
  string username, password;
  char *pw;
  int length=0, trigger=0;

  username=set_username(username);
  password=set_password(password, pw, length, trigger);

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
