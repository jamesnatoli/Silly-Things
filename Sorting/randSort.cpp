// Sorting algorithm that works by generating a random list
// Functionality:
// 1) generate a random list and randomly shuffle until sorted
// 2) generate a random, unique, list and randomly shuffle until sorted
// 3) *TO-DO* take a user-inputted list and randomly shuffle until sorted
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>

#define SIZE 45

// int bucket[SIZE];
// std::vector<int> pail;

void UniqueRandomArray( int pail[], int len = SIZE){
  // Create and fill an array with numbers 1 to num
  std::vector<int> temp;
  for (unsigned int i = 0; i < len; i++)
    temp.push_back( i + 1);
  // This will be the element of temp we pull from
  int element;
  for (unsigned int i = len; i > 0; i--){
    element = (rand()%i);
    // I'm picky, so I want to fill from left -> right
    pail[len - i] = temp.at(element);
    // Now remove that element from the temporary array
    temp.erase(temp.begin() + element);
  }
}

void RandomArray( int pail[], int len = SIZE){
  for (unsigned int i = 0; i < len; i++)
    pail[i] = (rand() % len) + 1;
}

bool isSorted( int pail[], int len = SIZE) {
  for (unsigned int i = 0; i < (len - 1); i++)
    if (pail[i] > pail[i+1])
      return false;
  return true;
}

void arrayPrint( int a[], int len = SIZE){
  std::cout << "Printing array of size " << len << std::endl;
  std::cout << "{ ";
  for (unsigned int i = 0; i < len; i++)
    if (i == (len - 1))
      std::cout << a[i] << "}" << std::endl;
    else
      std::cout << a[i] << ", ";
}

int main() {
  srand(time(NULL));
  std::cout << "Size is " << SIZE << std::endl;
  int bucket1[SIZE] = {0};
  int bucket2[SIZE] = {0};

  int iter = 1;
  do {
    UniqueRandomArray( bucket1);
    iter++;
    if ((iter % (100 * SIZE)) == 0)
      std::cout << iter << std::endl;
  }
  while( !isSorted( bucket1));
  std::cout << "Sorted After " << iter << " Iterations" << std::endl;
  arrayPrint( bucket1);

  // iter = 1;
  // do {
  //   RandomArray( bucket2);
  //   iter++;
  //   if ((iter % 100) == 0)
  //     std::cout << iter << std::endl;
  // }
  // while( !isSorted( bucket2));
  // std::cout << "Sorted After " << iter << " Iterations" << std::endl;
  // arrayPrint( bucket2);
  
  return 0;
}
