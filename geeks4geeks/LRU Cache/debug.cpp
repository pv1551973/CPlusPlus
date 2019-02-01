#include "debug.hpp"
#include <iostream>
using std::cout;
using std::endl;

int loop_count = 0;

void report (){
  cout << "Program terminated by choice as part of debugging." << endl;
  return;
}

