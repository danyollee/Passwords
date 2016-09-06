#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h> //Includes the "getpass" function. This lets the user type without it actually being displayed on screen.
#include <fstream>
#include <ctime> //Includes time

using namespace std;

//prototypes
void fill_coders(char[][26], char[][10]);
string set_username(string);
string set_password(string);

int main(){
  string username, password;
  char *key, codera[26][26], codernum[10][10];

  fill_coders(codera, codernum);
  username=set_username(username);
  password=set_password(password);

  return 0;
}

void fill_coders(char codera[][26], char codernum[][10]){
  char *alpha;
  string al;
  int length, counter=0;

  al="abcdefghijklmnopqrstuvwxyz";
  length=al.length();

  strcpy(alpha, al.c_str());

  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      if(i+j>25){
        codera[i][j]=alpha[counter];
        counter++;
      }else{
        codera[i][j]=alpha[j+i];
      }
    }
    counter=0;
  }

  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      cout << codera[i][j] << " ";
    }
    cout << endl;
  }
}

string set_username(string username){
  cout << "Enter a username: ";
  cin >> username;
  return username;
}

string set_password(string password){
  cout << "Enter a password: ";
  cin >> password;
  return password;
}
