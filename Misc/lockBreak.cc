// Generate Codes for Lock
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  bool flag = true;
  std::string line = "", confirm = "";
  int max = 40, r1, r2, r3;
  ofstream used;
  srand(time(NULL));
  
  while (flag) {
    std::cout << "******** NEW CODE ********" << std::endl;
    r1 = rand() % 40 + 1;
    r2 = rand() % 40 + 1;
    r3 = rand() % 40 + 1;
    used.open("used.txt", ios::app);
    if (used.is_open()) {
      while (getline( used, line))
	
    used << ;
    used.close();
    
    // Ask for new one
    flag = true;
    std::cout << "Do you want a new code??" << std::endl;
    std::cin >> confirm;
    if (confirm.compare("no"))
      flag = false;
  }
  return 0;
}
