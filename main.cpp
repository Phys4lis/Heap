#include <iostream>
#include <cstring>
#include <math.h>
#include "fstream"

using namespace std;

int correctInput();
void add (int (&heapArray)[101], int &inputTotal);
void sortArray(int (&heapArray)[101], int value, int index);
void print(int (&heapArray)[101], int index, int level, int inputTotal);
void remove(int (&heapArray)[101], int value, int index, int &inputTotal);
void removeAll(int (&heapArray)[101], int &inputTotal); 

int main() {
  // Initialize the array with zeros
  int heapArray[101];
  for (int i = 0; i < 100; i++) {
    heapArray[i] = 0;
  }  
  int inputTotal = 0;
  int index;
  int level;

  srand(time(NULL));
  
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
      // Print out the root, then replace it with the bottom row's rightmost child
      cout << heapArray[1] << endl;
      heapArray[1] = heapArray[inputTotal];
      heapArray[inputTotal] = 0;
      inputTotal--;
      remove(heapArray, heapArray[1], 1, inputTotal);
      cout << "Successfully deleted root of tree" << endl << endl;
    }
    // Remove all 
    else if (option == 4) {
      removeAll(heapArray, inputTotal);
    }
    // Quit the program
    else if (option == 5) {
      beenCookingWithThatSauceBoi = false;
    }
  }
}

// Make sure that the user inputs a valid function
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
	// Make sure the user doesn't exceed the maximum allowed numbers in the tree 
	if (inputTotal + inputNums > 100) {
	  cout << "There isn't enough space to add that many numbers!" << endl;
	}
	else {
	  sizeCheck = false;
	}
      }
      // Add the inputted numbers into an array
      for (int i = inputTotal; i < (inputTotal + inputNums); i++) {
	cin >> heapArray[i+1];
	cin.get();
	sortArray(heapArray, heapArray[i+1], i+1);
      }
      inputTotal+= inputNums;
      inputMethodLoop = false;
    }
    // Input through File
    else if (strcmp(input, "FILE") == 0) {
      int inputNums;
      bool sizeCheck = true;
      while (sizeCheck == true) {
	cout << "How many numbers are you adding?" << endl;
	cin >> inputNums;
	cin.get();
	// Make sure the user doesn't exceed the maximum allowed numbers in the tree
	if (inputTotal + inputNums > 100) {
	  cout << "There isn't enough space to add that many numbers!" << endl;
	}
	else {
	  sizeCheck = false;
	}
      }
      // Add to array through file
      ifstream numbers("testNumbers.txt");
      int oneNumber;
      for (int i = inputTotal; i < (inputTotal + inputNums); i++) {
	numbers >> heapArray[i+1];
	sortArray(heapArray, heapArray[i+1], i+1);
      }
      inputTotal+= inputNums;
      inputMethodLoop = false;
    }
    else {
      cout << "That is not one of the two options!" << endl << endl;
    }
  }
}
void sortArray(int (&heapArray)[101], int value, int index) {
  int parentIndex = floor(index/2);
  // If the child is larger than its parent, swap
  if (value > heapArray[parentIndex] && parentIndex != 0) {
    int temp = heapArray[parentIndex];
    heapArray[parentIndex] = value;
    heapArray[index] = temp;
    // Recursion
    sortArray(heapArray, value, parentIndex);
  }
}

void print(int (&heapArray)[101], int index, int level, int inputTotal) {
  if (inputTotal == 1) {
    cout << "The tree is empty!" << endl << endl;
  }
  // Go through the right side of tree, finding where the tree stops, and indenting appropriately
  else if (inputTotal != 1) {
    if ((index*2) + 1 < inputTotal) {
      print(heapArray, (index*2) + 1, level + 1, inputTotal);
    }
    // Indent values
    for (int i = 0; i < level; i++) {
      cout << '\t';
    }
    cout << heapArray[index] << endl;
    // Left side
    if ((index*2) < inputTotal) {
      print(heapArray, (index*2), level + 1,  inputTotal);
    }
  }
}

void remove(int (&heapArray)[101], int value, int index, int &inputTotal) {
  int temp;
  int swapTemp = value;
  // Check to see if the parent has any children or if it's a leaf
  if (heapArray[index*2] != 0 || heapArray[index*2+1] != 0) {
    // If both children are larger than parent, choose the larger child
    if (heapArray[index*2] > value && heapArray[index*2+1] > value) {
      if (heapArray[index*2] > heapArray[index*2+1]) {
	temp = 1;
      }
      else if (heapArray[index*2] < heapArray[index*2+1]) {
	temp = 2;
      }
      else {
	temp = 1;
      }
      // Left child was larger than right
      if (temp == 1) {
	heapArray[index] = heapArray[index*2];
	heapArray[index*2] = swapTemp;
	remove(heapArray, heapArray[index*2], index*2, inputTotal);
      }
      // Right child was larger than left
      else if (temp == 2) {
	heapArray[index] = heapArray[index*2+1];
	heapArray[index*2+1] = swapTemp;
	remove(heapArray, heapArray[index*2+1], index*2+1, inputTotal);
      }
    }
    // Swap with left child
    else if (heapArray[index*2] > value && heapArray[index*2+1] <= value) {
      heapArray[index] = heapArray[index*2];
      heapArray[index*2] = swapTemp;
      remove(heapArray, heapArray[index*2], index*2, inputTotal);  
    }
    // Swap with right child
    else if (heapArray[index*2+1] > value && heapArray[index*2] <= value) {
      heapArray[index] = heapArray[index*2+1];
      heapArray[index*2+1] = swapTemp;
      remove(heapArray, heapArray[index*2+1], index*2+1, inputTotal);
    }
  }
}
void removeAll(int (&heapArray)[101], int &inputTotal) {
  // Run through tree, removing every root, until the tree is empty
  while (inputTotal != 0) {
    cout << heapArray[1] << endl;
    heapArray[1] = heapArray[inputTotal];
    heapArray[inputTotal] = 0;
    inputTotal--;
    remove(heapArray, heapArray[1], 1, inputTotal);
  }
}
