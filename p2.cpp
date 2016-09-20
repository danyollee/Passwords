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
void setup_password(string, char[], int[], char[][26], char[][26], char[][10]);
char upper_grid(int, int, char[][26]);
char lower_grid(int, int, char[][26]);
char number_grid(int, int, char[][10]);

int main(){
  string username, password;
  char coder_a[26][26], coder_A[26][26], coder_num[10][10], *login_password;
  int key[4]={4, 15, 6, 5};

  fill_coders(coder_a, coder_A, coder_num);
  username=set_username(username);
  password=set_password(password);
  setup_password(password, login_password, key, coder_A, coder_a, coder_num);

  // delete [] login_password;

  // for(int i=0; i<26; i++){
  //   for(int j=0; j<26; j++){
  //     cout << coder_a[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  //
  // for(int i=0; i<26; i++){
  //   for(int j=0; j<26; j++){
  //     cout << coder_A[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  //
  // for(int i=0; i<10; i++){
  //   for(int j=0; j<10; j++){
  //     cout << coder_num[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  return 0;
}

void fill_coders(char coder_a[][26], char coder_A[][26], char coder_num[][10]){
  char alpha[25], Alpha[25], Num[9]; //alpha is the lowercase grid, Alpha is the uppercase grid, and Num is the number grid
  string al, au, num;
  int length, counter=0;

  al="abcdefghijklmnopqrstuvwxyz";
  au="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  num="0123456789";

  strcpy(alpha, al.c_str());
  strcpy(Alpha, au.c_str());
  strcpy(Num, num.c_str());

  //Creates the lowercase grid
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

  //Creates the uppercase grid
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

  //Creates the number grid
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

void setup_password(string password, char login_password[], int key[], char coder_A[][26], char coder_a[][26], char coder_num[][10]){
  int length, counter=0, num_counter=3, rando, key_rando; //rando is for the array element when sent
  char *temp;

  length=password.length();
  login_password=new char[length];

  cout << endl;

  temp=new char[length];
  strcpy(temp, password.c_str());

  for(int i=0; i<length; i++){
    if(counter>2){
      counter=0;
    }
    if(temp[i]>=65 && temp[i]<=90){
      key_rando=key[counter];
      rando=temp[i]-65;
      login_password[i]=upper_grid(rando, key_rando, coder_A);
    }
    if(temp[i]>=97 && temp[i]<=122){
      key_rando=key[counter];
      rando=temp[i]-97;
      login_password[i]=lower_grid(rando, key_rando, coder_a);
    }
    if(temp[i]>=48 && temp[i]<=57){
      key_rando=key[counter];
      rando=temp[i]-48;
      login_password[i]=number_grid(num_counter, key_rando, coder_num);
    }
    counter++;
  }

  for(int i=0; i<length; i++){
    cout << login_password[i];
  }
  cout << endl;

  delete [] temp;

}

char upper_grid(int rando, int key_rando, char coder_A[][26]){
  char pw=coder_A[rando][key_rando];

  return pw;
}

char lower_grid(int rando, int key_rando, char coder_a[][26]){
  char pw=coder_a[rando][key_rando];

  return pw;
}

char number_grid(int rando, int key_rando, char coder_num[][10]){
  char pw=coder_num[rando][key_rando];

  return pw;
}
