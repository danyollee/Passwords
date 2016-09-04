#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h> //Includes the "getpass" function. This lets the user type without it actually being displayed on screen.
#include <fstream>
#include <ctime> //Includes time

using namespace std;

//prototypes
string set_username(string);

int main(){
  string username, password;
  char *key;

  username=set_username(username);

  cout << username << endl;

  return 0;
}

string set_username(string username){
  cout << "Enter a username: ";
  cin >> username;
  return username;
}
