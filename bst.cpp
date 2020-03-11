#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

void sort(int* numbers, int size);
int char2int(char character);

int main() {
  bool choice = false;
  char input[9];
  char currentnumber[4];
  for(int i = 0; i < 4; i++) {
    currentnumber[i] = '?';
  }
  char numberinput[500];
  for(int i = 0; i < 500; i++) {
    numberinput[i] = '?';
  }
  int numbers = 0;
  int randomnumbers[100];
  int *intarray = new int[100];
  for(int i = 0; i < 9; i++) {
    input[i] = '?';
  }
  while(!choice) {
    cout << "type \"file\" to read from file." << endl;
    cout << "type \"type\" to input numbers by hand." << endl;
    cout << "type \"generate\" to generate a text file with 100 random numbers" << endl;
    cin.getline(input, 9);
    if(strcmp(input, "file") == 0) { // from file
      choice = true;
      ifstream inputfile;
      int count = 0;
      int x;
      inputfile.open("generated.txt"); // try to open file
      if(inputfile.is_open()) {
	while (inputfile >> x) {
	  intarray[count++] = x;
	  numbers++;
	}
	inputfile.close();
	sort(intarray, numbers);
      }
      else {
	cout << "Cannot open file." << endl;
      }
    }
    if(strcmp(input, "type") == 0) { // from keyboard
      char currentchar;
      int counter = 0;
      int counter2 = 0;
      int newnumber2 = 0;
      int newnumber = 0;
      int numbersize = 0;
      choice = true;
      cin.getline(numberinput, 500);
      while(numberinput[counter] != '?') {
	if(numberinput[counter] > 47 && numberinput[counter] < 58) { // if number
	  newnumber = char2int(numberinput[counter]);
			       if(numbersize < 5) {
				 currentnumber[numbersize] = newnumber;
				 numbersize++;
			       }
			       counter++;
	}
	else if(numberinput[counter] == ' ') { // if space
	  if(numbersize == 4) {
	    newnumber2 += 1000; // all 4 digit numbers will turn into 1000.
	  }
	  else if(numbersize == 3) {
	    newnumber2 += (100 * currentnumber[0]);
	    newnumber2 += (10 * currentnumber[1]);
	    newnumber2 += currentnumber[2];
	  }
	  else if(numbersize == 2) {
	    newnumber2 += (10 * currentnumber[0]);
	    newnumber2 += currentnumber[1];
	  }
	  else if(numbersize == 1) {
	    newnumber2 += currentnumber[0];
	  }
	  else {
	    cout << "Invalid input." << endl;
	  }
	  intarray[counter2] = newnumber2;
	  newnumber2 = 0;
	  counter2++;
	  counter++;
	  numbersize = 0;
	}
	else { // anything else
	  cout << "invalid character ignored" << endl;
	  counter++;
	}
      }
    }
    if(strcmp(input, "generate") == 0) { // generate .txt with 100 random numbers
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

void sort(int* numbers, int size) {
  
}

int char2int(char character) { // subtract 48 from ascii calue to get int
  int output = 0;
  if(character < 58 && character > 47) {
    output = character - 48;
    return output;
  }
}
