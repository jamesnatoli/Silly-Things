// Do calculations for F20 EP2 Exam 5
#include <cmath>
#include <iostream>

int main() {
  float l1, l2, th, dellamb;
  dellamb = 0.01;
  while (1) {
    std::cout << "******** NEW CALCULATION ********" << std::endl;
    // Get values
    std::cout << "What is lambda 1 (nm)" << std::endl;
    std::cin >> l1;
    std::cout << "What is lambda 2? (nm)" << std::endl;
    std::cin >> l2;
    std::cout << "What is theta? (degrees)" << std::endl;
    std::cin >> th;
    
    // Constants
    // float c = 3 * pow(10, 8);;
    // float mu0 = 1.256 * pow( 10, -6);
    float pi = 3.141592;

    // Shift to radians
    th = th * pi / 180;

    std::cout << sin(th) << std::endl;
    std::cout << sin(pi/2) << std::endl;
    
    std::cout << "Part (1): Min # Lines =  " << 100*l1 << " lines \n" << std::endl;
    std::cout << "Part (2): Smalles Grating Spacing =  " << l1/sin(th) << " nm \n" << std::endl;
    std::cout << "Part (3): Min Width =  " << 100*l1*l1/sin(th) << " nm \n" << std::endl;
    std::cout << "Part (4): Resolving Power =  " << (l1+l2)*50 << " \n" << std::endl;
  }
  
  return 0;
}
