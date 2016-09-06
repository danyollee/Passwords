#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h> //Includes the "getpass" function. This lets the user type without it actually being displayed on screen.
#include <fstream>
#include <ctime> //Includes time

using namespace std;

//prototypes
void fill_coders(char[][26], char[][26], char[][10]);
string set_username(string);
string set_password(string);

int main(){
  string username, password;
  char *key, coder_a[26][26], coder_A[26][26], coder_num[10][10];

  fill_coders(coder_a, coder_A, coder_num);
  username=set_username(username);
  password=set_password(password);

  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      cout << coder_a[i][j] << " ";
    }
    cout << endl;
  }

  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      cout << coder_A[i][j] << " ";
    }
    cout << endl;
  }

  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      cout << coder_num[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}

void fill_coders(char coder_a[][26], char coder_A[][26], char coder_num[][10]){
  char alpha[25], Alpha[25], Num[9];
  string al, au, num;
  int length, counter=0;

  al="abcdefghijklmnopqrstuvwxyz";
  au="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  num="0123456789";

  strcpy(alpha, al.c_str());
  strcpy(Alpha, au.c_str());
  strcpy(Num, num.c_str());

  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      if(i+j>25){
        coder_a[i][j]=alpha[counter];
        counter++;
      }else{
        coder_a[i][j]=alpha[j+i];
      }
    }
    counter=0;
  }

  counter=0;
  for(int i=0; i<26; i++){
    for(int j=0; j<26; j++){
      if(i+j>25){
        coder_A[i][j]=Alpha[counter];
        counter++;
      }else{
        coder_A[i][j]=Alpha[j+i];
      }
    }
    counter=0;
  }

  counter=0;
  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      if(i+j>9){
        coder_num[i][j]=Num[counter];
        counter++;
      }else{
        coder_num[i][j]=Num[i+j];
      }
    }
    counter=0;
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
