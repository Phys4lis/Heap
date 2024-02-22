#include <iostream>
#include <cstring>
#include <math.h>

using namespace std;

int correctInput();
void add (int (&heapArray)[101], int &inputTotal);
void sortArray(int (&heapArray)[101], int value, int index);
void print(int (&heapArray)[101], int index, int level, int end);

int main() {
  int heapArray[101];
  heapArray[0] = 1;
  /*for (int i = 0; i < 101; i++) {
    heapArray[i] = NULL;
    }*/
  int inputTotal = 0;
  bool beenCookingWithThatSauceBoi = true;
  while (beenCookingWithThatSauceBoi == true) {
    int option = correctInput();
    // Add values to the heap
    if (option == 1) {
      add(heapArray, inputTotal);
    }
    // Print out the heap
    else if (option == 2) {
      int index;
      int level;
      int end;
      print(heapArray, index, level, end);
    }
    // Remove the root (highest value)
    else if (option == 3) {
      
    }
    // Remove all 
    else if (option == 4) {
      
    }
    // Quit the program
    else if (option == 5) {
      beenCookingWithThatSauceBoi = false;
    }
  }
}

int correctInput() {
  bool leaveLoop = false;
  cout << "Enter one of the following options: ADD, PRINT, REMOVE, REMOVEALL, or QUIT (uppercase)" << endl;
  while (leaveLoop == false) {
    char input[15];
    cin.get(input, 15);
    cin.ignore(15, '\n');
    if (strcmp(input, "ADD") == 0) {
      return 1;
    }
    else if (strcmp(input, "PRINT") == 0) {
      return 2;
    }
    else if (strcmp(input, "REMOVE") == 0) {
      return 3;
    }
    else if (strcmp(input, "REMOVEALL") == 0) {
      return 4;
    }
    else if (strcmp(input, "QUIT") == 0) {
      return 5;
    }
    else {
      cout << "Please enter a valid option." << endl;
    }
  }
  return -1;
}

void add (int (&heapArray)[101], int &inputTotal) {
  cout << "CONSOLE or FILE? (uppercase)" << endl;
  char input[10];
  cin.get(input, 10);
  cin.get();
  // Input through console
  if (strcmp(input, "CONSOLE") == 0) {
    int inputNums;
    bool sizeCheck = true;
    while (sizeCheck == true) {
      cout << "How many numbers are you adding?" << endl;
      cin >> inputNums;
      cin.get();
      if (inputTotal + inputNums > 100) {
	cout << "There isn't enough space to add that many numbers!" << endl;
      }
      else {
	sizeCheck = false;
      }
    }
    int values[101];
    for (int i = inputTotal; i < (inputTotal + inputNums); i++) {
      cin >> values[i+1];
      cin.get();
    }
    inputTotal+= inputNums;
    for (int i = 1; i < inputTotal+1; i++) {
      heapArray[i] = values[i];
      sortArray(heapArray, values[i], i);
    }
    cout << "here" << endl;
  }
  else if (strcmp(input, "FILE") == 0) {
    
  }
  else {
    cout << "That is not one of the two options!" << endl;
  }
}

void sortArray(int (&heapArray)[101], int value, int index) {
  int parentIndex = floor(index/2);
  if (value > heapArray[parentIndex] && parentIndex != 0) {
    int temp = heapArray[parentIndex];
    heapArray[parentIndex] = value;
    heapArray[index] = temp;
    sortArray(heapArray, value, parentIndex);
  }
}

void print(int (&heapArray)[101], int index, int level, int end) {
  if ((index*2) + 1 < end) {
    print(heapArray, (index*2) + 1, level + 1, end);
  }
  for (int i = 0; i < level; i++) {
    cout << '\t';
  }
  cout << heapArray[index] << endl;
  if ((index*2) < end) {
    print(heapArray, (index*2), level + 1, end);
  }
}
