#include "code.hpp"
#include "error.hpp"
#include <iostream>
#include <exception>
using std::cout;
using std::endl;
using std::exception;

int main (void){

  vector<string> v;

  v.push_back("5");
  v.push_back("7");
  v.push_back("2 6 1 9 4 5 3");
  v.push_back("7");
  v.push_back("1 9 3 10 4 20 2");
  v.push_back("7");
  v.push_back("1 9 18 10 4 20 19");
  v.push_back("11");
  v.push_back("23 104 47 101 4 48 5 6 100 99 102");
  v.push_back("11");
  v.push_back("13 18 16 11 88 12 100 17 14 19 125");

  try{
    find_lcs(v);
  }
  catch(exception& e){
    cout << "Runtime error: " << e.what() << endl;
  }
  catch(error& e){
    cout << "Runtime error: " << e.what() << endl;
  }
  catch(...){
    cout << "Unknown error" << endl;
  }

  return 0;
}
    
