// Do calculations for F20 EP2 Exam 3
#include <cmath>
#include <iostream>

int main() {
  float r1 = 0, r2 = 0, curr = 0;
  while (1) {
    std::cout << "******** NEW CALCULATION ********" << std::endl;
    // Get values
    std::cout << "What is radius 1? (mm)" << std::endl;
    std::cin >> r1;
    // std::cout << "What is radius 2? (mm)" << std::endl;
    // std::cin >> r2;
    std::cout << "What is current? (A)" << std::endl;
    std::cin >> curr;

    // Constants
    float pi = 3.14159;
    float mu0 = 1.256 * pow( 10, -6);

    // Shift to SI
    r1 = r1 / 1000;
    // r2 = r2 / 1000;

    float B1 = 0, B2 = 0;
    B1 = mu0*curr / (6*pi*r1);
    B2 = mu0*curr / (2*pi*r1);
    std::cout << "Part (1): B =  " << B1 << " T\n" << std::endl;
    std::cout << "Part (2): B =  " << B2 << " T\n"<< std::endl;
    std::cout << "Part (3): B = 0 T\n" << std::endl;
  }
  
  return 0;
}
