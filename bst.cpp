#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
  bool choice = false;
  char input[9];
  int randomnumbers[100];
  for(int i = 0; i < 9; i++) {
    input[i] = '?';
  }
  while(!choice) {
    cout << "type \"file\" to read from file." << endl;
    cout << "type \"type\" to input numbers by hand." << endl;
    cout << "type \"generate\" to generate a text file with 100 random numbers" << endl;
    cin.getline(input, 5);
    if(strcmp(input, "file") == 0) {
      choice = true;
    }
    if(strcmp(input, "type") == 0) {
      choice = true;
    }
    if(strcmp(input, "generate") == 0) {
      int random = 0;
      for (int i = 0; i < 100; i++) { // 100 random numbers
	random = rand() % 1000 + 1; // from 1 - 1000
	randomnumbers[i] = random;
      }
      ofstream randomfile;
      randomfile.open("generated.txt");
      for(int i = 0; i < 100; i++) {
	randomfile << randomnumbers[i] << "\n";
      }
      randomfile.close();
      cout << "generated \"generated.txt\"" << endl;
    }
  }
  return 0;
}
