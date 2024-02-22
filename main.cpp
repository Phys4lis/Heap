#include <iostream>
#include <cstring>
#include <math.h>

using namespace std;

int correctInput();
void add (int (&heapArray)[101], int &inputTotal);
void sortArray(int (&heapArray)[101], int value, int index);
void print(int (&heapArray)[101], int index, int level, int inputTotal);
void remove(int (&heapArray)[101], int value, int index);

int main() {
  int heapArray[101];
  heapArray[0] = 1;
  
  int inputTotal = 0;
  int index;
  int level;
  
  bool beenCookingWithThatSauceBoi = true;
  while (beenCookingWithThatSauceBoi == true) {
    int option = correctInput();
    // Add values to the heap
    if (option == 1) {
      add(heapArray, inputTotal);
    }
    // Print out the heap
    else if (option == 2) {
      index = 1;
      level = 0;
      print(heapArray, index, level, inputTotal+1);
    }
    // Remove the root (highest value)
    else if (option == 3) {
      cout << heapArray[1] << endl;
      heapArray[1] = heapArray[inputTotal + 1];
      inputTotal--;
      remove(heapArray, heapArray[1], 1);
      cout << "Successfully deleted root of tree" << endl << endl;
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
  // Input through console
  bool inputMethodLoop = true;
  while (inputMethodLoop == true) {
    cout << "CONSOLE or FILE? (uppercase)" << endl;
    char input[10];
    cin.get(input, 10);
    cin.get();
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
      for (int i = inputTotal; i < (inputTotal + inputNums); i++) {
	cin >> heapArray[i+1];
	cin.get();
	sortArray(heapArray, heapArray[i+1], i+1);
      }
      inputTotal+= inputNums;
      /*for (int i = 0; i < inputTotal; i++) {
	cout << heapArray[i+1];
      }*/
      inputMethodLoop = false;
    }
    else if (strcmp(input, "FILE") == 0) {
      inputMethodLoop = false;
    }
    else {
      cout << "That is not one of the two options!" << endl << endl;
    }
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

void print(int (&heapArray)[101], int index, int level, int inputTotal) {
  if ((index*2) + 1 < inputTotal) {
    print(heapArray, (index*2) + 1, level + 1, inputTotal);
  }
  for (int i = 0; i < level; i++) {
    cout << '\t';
  }
  cout << heapArray[index] << endl;
  if ((index*2) < inputTotal) {
    print(heapArray, (index*2), level + 1,  inputTotal);
  }
}

void remove(int (&heapArray)[101], int value, int index) {
  if (heapArray[index*2] > value && heapArray[index*2+1] > value) {
    int temp;
    if (heapArray[index*2] > heapArray[index*2+1]) {
      temp = 1;
    }
    else if (heapArray[index*2] < heapArray[index*2+1]) {
      temp = 2;
    }
    else {
      temp = 1;
    }
    if (temp == 1) {
      int swapTemp = heapArray[index];
      heapArray[index] = heapArray[index*2];
      heapArray[index*2] = swapTemp;
      remove(heapArray, heapArray[index*2], index*2);
    }
    else if (temp == 2) {
      int swapTemp = heapArray[index];
      heapArray[index] = heapArray[index*2+1];
      heapArray[index*2+1] = swapTemp;
      remove(heapArray, heapArray[index*2+1], index*2+1);
    }
  }
  else if (heapArray[index/2] > value && heapArray[(index-1)/2] <= value) {
    int swapTemp = heapArray[index];
    heapArray[index] = heapArray[index*2];
    heapArray[index*2] = swapTemp;
    remove(heapArray, heapArray[index*2], index*2);  
  }
  else if (heapArray[(index-1)/2] > value && heapArray[index/2] <= value) {
    int swapTemp = heapArray[index];
    heapArray[index] = heapArray[index*2+1];
    heapArray[index*2+1] = swapTemp;
    remove(heapArray, heapArray[index*2+1], index*2+1);
  }
}
