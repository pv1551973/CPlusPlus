#include "code.hpp"

#ifndef DBG
#include <iostream>
using std::cout;
using std::endl;
#endif

int main (void)
{
  array<int, 14> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; 
  list<int,decltype(a)> l(a);

  auto r = l.get_middle_node();
  cout << r.get_data() << endl;

  return 0;
}
