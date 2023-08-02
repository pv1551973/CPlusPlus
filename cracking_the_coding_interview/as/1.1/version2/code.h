#include<string>
#include<iterator>
#include<iostream>

using std::string;
using std::advance;
using std::iterator;
using std::cin;
using std::cout;
using std::endl;

bool chk_if_uniq (string); 

template<typename iter>
bool per_scan(iter it, iter eIter){

  auto nxIt = it;
  bool iterPos = (nxIt != eIter);
  auto flag = true;

  do{
      ++nxIt;
      iterPos = (nxIt != eIter);
      if(iterPos){
        if(*nxIt == *it){
          flag = false;
        }
      }
    }while(flag && iterPos);
  
 return flag;
}
