#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdlib.h>
#include <math.h>

int main() {
  int N;
  std::cout << "How big is the list (powers of 2 only)" << std::endl;
  std::cin >> N;
  srand(time(NULL));
  std::vector<int> vals;
  for (unsigned int i = 0; i < N; i++) {
    vals.push_back( rand() % 1000);
    std::cout << vals[i] << " ";
  }
  std::cout << std::endl;
  
  unsigned int log_2N = log2(N);
  unsigned int inc = 0, j = 0;
  int p1 = 0, p2 = 0, extra = 0;
  for (unsigned int i = 0; i < log_2N; i++) {
    j = pow( 2, i);
    inc = pow( 2, i+1);
    while (j < N) {
      p1 = j - 1;
      p2 = (j - 1) + inc/2;
      std::cout << "comparing " << vals[p1] << " and " << vals[p2] << std::endl;
      if ( vals[p1] > vals[ p2]) {
	extra = vals[p1];
	vals[p1] = vals[p2];
	vals[p2] = extra;
      }
      j = j + inc;
    }
    std::cout << std::endl;
  }
  std::cout << "Largest Value = " << vals[N - 1] << std::endl;
}
