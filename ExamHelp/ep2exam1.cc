// Do calculations for F20 EP2 Exam 1
#include <cmath>
#include <iostream>

int main() {
  float lambda = 0, rin = 0, rout = 0, ppoint = 0;
  while (1) {
    std::cout << "******** NEW CALCULATION ********" << std::endl;
    // Get values
    std::cout << "What is Lambda? (nC/m)" << std::endl;
    std::cin >> lambda;
    std::cout << "What is inner radius? (mm)" << std::endl;
    std::cin >> rin;
    std::cout << "What is outer radius? (mm)" << std::endl;
    std::cin >> rout;
    std::cout << "Where is point p? (mm)" << std::endl;
    std::cin >> ppoint;

    // Calculation
    float sig_in = 0, sig_out = 0, Efield = 0;
    float pi = 3.14159;
    float ep0 = 8.854 * pow( 10, -12);
    std::cout << "ep0 = " << ep0 << std::endl;

    // Shift to SI
    rin = rin / 1000;
    rout = rout / 1000;
    ppoint = ppoint / 1000;
    
    sig_in = lambda / (2*pi*rin);
    std::cout << "\nInner Surface Charge = " << sig_in << " nC/m^2 \n" << std::endl;
    sig_out = lambda / (2*pi*rout);
    std::cout << "Outer Surface Charge = " << sig_out << " nC/m^2 \n" << std::endl;

    // nC -> C
    lambda = lambda / 1000000000;
    Efield = lambda / (2*pi*ppoint*ep0);
    std::cout << "Electric Field = " << Efield*ep0 << "*ep0 V/m \n"<< std::endl;
    std::cout << "Electric Field = " << Efield << " V/m \n"<< std::endl;
  }
  
  return 0;
}
