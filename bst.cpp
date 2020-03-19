#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "node.h"
#include "math.h"

using namespace std;

int* sort(int* numbers, int size);
void buildtree(int* numbers, int size);
int char2int(char character);
void recursion(Node* root, int size, int* numbers);

int main() { 
    bool choice = false;
    char input[9];
    char currentnumber[4];
    for (int i = 0; i < 4; i++) {
        currentnumber[i] = '?';
    }
    char numberinput[500];
    for (int i = 0; i < 500; i++) {
        numberinput[i] = '?';
    }
    char removeinput[3];
    for (int i = 0; i < 3; i++) {
        removeinput[i] = '?';
    }
    int numbers = 0;
    int randomnumbers[100];
    int* intarray = new int[100];
    for (int i = 0; i < 9; i++) {
        input[i] = '?';
    }
    while (!choice) {
        cout << "type \"file\" to read from file." << endl;
        cout << "type \"type\" to input numbers by hand." << endl;
        cout << "type \"generate\" to generate a text file with 100 random numbers" << endl;
        cin.getline(input, 9);
        if (strcmp(input, "file") == 0) { // from file
            choice = true;
            ifstream inputfile;
            int count = 0;
            int x;
            inputfile.open("generated.txt"); // try to open file
            if (inputfile.is_open()) {
                while (inputfile >> x) {
                    intarray[count++] = x;
                    numbers++;
                }
                inputfile.close();
                //sort(intarray, numbers);
            }
            else {
                cout << "Cannot open file." << endl;
            }
        }
        if (strcmp(input, "type") == 0) { // from keyboard
            cout << "Input numbers seperated by a space, and type a period after the last number to indicate the end." << endl;
            cout << "Ex: \"1 2 3 4.\"" << endl;
            char currentchar;
            int counter = 0;
            int counter2 = 0;
            int newnumber2 = 0;
            int newnumber = 0;
            int numbersize = 0;
            choice = true;
            cin.getline(numberinput, 500);
            bool escape = false;
           // while (numberinput[counter] != '?') {
            while (!escape) {
                if (numberinput[counter] > 47 && numberinput[counter] < 58) { // if number
                    newnumber = char2int(numberinput[counter]);
                    if (numbersize < 5) {
                        currentnumber[numbersize] = newnumber;
                        numbersize++;
                    }
                    counter++;
                }
                else if (numberinput[counter] == ' ') { // if space         
                    if (numbersize == 3) {
                        newnumber2 += (100 * currentnumber[0]);
                        newnumber2 += (10 * currentnumber[1]);
                        newnumber2 += currentnumber[2];
                    }
                    else if (numbersize == 2) {
                        newnumber2 += (10 * currentnumber[0]);
                        newnumber2 += currentnumber[1];
                    }
                    else if (numbersize == 1) {
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
                else if (numberinput[counter] == '.') { // deal with last number
                    int  backup = 1;
                    bool escape2 = false;
                    while (!escape2) { // how far back to we have to go to find the start of the last number
                        if (numberinput[counter - backup] > 47 && numberinput[counter - backup] < 58) {
                            backup++;
                        }
                        else if (numberinput[counter - backup] == ' ') {
                            newnumber2 = 0;
                            if ((backup - 1) == 3) {
                                newnumber2 += (100 * char2int(numberinput[counter - backup +1]));
                                newnumber2 += (10 * char2int(numberinput[counter - backup + 2]));
                                newnumber2 += char2int(numberinput[counter - backup + 3]);
                            }
                            else if ((backup - 1) == 2) {
                                newnumber2 += 10 * char2int(numberinput[counter - backup + 1]);
                                newnumber2 += char2int(numberinput[counter - backup + 2]);
                            }
                            else if ((backup - 1) == 1) {
                                newnumber2 += char2int(numberinput[counter - backup +1]);
                            }
                            else {
                                cout << "Invalid input." << endl;
                            }
                            escape2 = true;
                        }
                    }
                    //newnumber2 = char2int(numberinput[counter - 1]);
                    intarray[counter2] = newnumber2;
                    counter++;
                    counter2++;
                    escape = true;
                }
                else { // anything else
                    cout << "invalid character ignored" << endl;
                    counter++;
                }
            }
            ofstream outputfile;
            outputfile.open("output.txt");
            int x;
            if (outputfile.is_open()) {
                for (int i = 0; i < counter2; i++) {
                    outputfile << intarray[i] << "\n";
                }
                outputfile.close();  
            }
            else {
                cout << "Could not open output.txt." << endl;
            }
            buildtree(intarray, counter2);
        }
        if (strcmp(input, "generate") == 0) { // generate .txt with 100 random numbers
            int random = 0;
            for (int i = 0; i < 100; i++) { // 100 random numbers
                random = rand() % 1000 + 1; // from 1 - 1000
                randomnumbers[i] = random;
            }
            ofstream randomfile;
            randomfile.open("generated.txt");
            for (int i = 0; i < 100; i++) {
                randomfile << randomnumbers[i] << "\n";
            }
            randomfile.close();
            cout << "generated \"generated.txt\"" << endl;
        }
        if (strcmp(input, "remove") == 0) {
            cin.getline(removeinput, 3);
            if (removeinput[2] > 47 && removeinput[2] < 58) {

            }
        }
    }
    return 0;
}

int* sort(int* numbers, int size) { // didnt need this
    int* sorted = new int[100];
    int highest = 0;
    int highestindex;
    ofstream output;
    output.open("sorted.txt");
    for (int i = 0; i < size; i++) {
        highest = 0;
        for (int i = 0; i < size; i++) {
            if (numbers[i] > highest) {
                highest = numbers[i];
                highestindex = i;
            }
        }
        numbers[highestindex] = 0;
        sorted[i] = highest;
        output << sorted[i] << " ";
    }
    output.close();
    return sorted;
}

int char2int(char character) { // subtract 48 from ascii calue to get int
    int output = 0;
    if (character < 58 && character > 47) {
        output = character - 48;
        return output;
    }
}

void buildtree(int* numbers, int size) {
    Node* root = new Node();
    root->setData(numbers[0]);
    ofstream tree;
    tree.open("tree.txt");
    if (tree.is_open()) {
        bool escape = false;
        int tmp = 2;
        int count = 0;
        while (!escape) {
            if (tmp < size) {
                count++;
                tmp = pow(2, count);
            }
            else {
                escape = true;
            }
        }
        cout << "tmp " << tmp << endl; // # of tabs before the root?
        cout << "count " << count << endl; // tmp = # of rows/tabs between children of the root
        for (int i = 0; i < tmp; i++) {
            tree << "\t";
        }
        int index = 1;
        tree << root->getData() << "\n";
        recursion(root, size, numbers);
        /*int numberoftabs = tmp / 2;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < numberoftabs; j++) {
                tree << "\t";
            }

        }*/
        tree.close();
    }
    else {
        cout << "for some reason the file cannot be opened?" << endl;
    }
}

void recursion(Node* root, int size, int* numbers) {
    for (int i = 0; i < size; i++) {
        Node* child = new Node();
        if (root->getLeft() == 0) {
            root->setLeft(child);
        }
        if (root->getRight() == 0) {
            root->setRight(child);
        }
    }
}