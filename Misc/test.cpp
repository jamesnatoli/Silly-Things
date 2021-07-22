#include <iostream>
#include <string>
#include <set>

class Tester {
public:
  int val;
  int getVal();
  void setVal(int in);
  bool operator< (const Tester &right);
};

void Tester::setVal( int in){
  val = in;
}

int Tester::getVal () {
  return val;
}

// Overload the "<" operator
bool Tester::operator<(const Tester &right){
  return val < right.val;
}

    int main()
{
  bool whip = true;
  whip = 0;
  char b = 'P';
  std::string c = "Hello World";
  double d = 5.378;
  int a = 9/4;
  a = 78;
  a = 54;
  int e = a;
  e = 14;
  std::cout << "a = " << a << std::endl
	    << "b = " << b << std::endl
	    << "c = " << c << std::endl
	    << "d = " << d << std::endl
	    << "whip = " << whip << std::endl
	    << "e = " << e << std::endl
	    << std::endl;

  std::set<Tester*> container;
  Tester* wow = new Tester();
  Tester* cool = new Tester();
  Tester* nice = new Tester();

  container.insert(wow);
  container.insert(cool);
  container.insert(nice);
 
  for (std::set<Tester*>::iterator iter = container.begin(); iter != container.end(); iter++)
    std::cout << iter -> getVal() << std::endl;
}
