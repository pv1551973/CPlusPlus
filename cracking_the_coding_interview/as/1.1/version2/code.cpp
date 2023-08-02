#ifndef CODE_H
#define CODE_H
#include "code.h"
#endif

int main (){
 
 string input_string;

 cout << "enter string: ";
 cin >> input_string;
 
 auto result = chk_if_uniq(input_string);
 
 if(result){
   cout << input_string << " contains unique characters." << endl; 
 }
else{
   cout << input_string << " contains non-unique characters." << endl; 
}

return 0;
}

bool chk_if_uniq (string s){ 
  
  auto bIter = s.begin();
  auto eIter = s.end();
  bool iterPos = (bIter != eIter);
  auto flag = true;

  while(iterPos){
   flag = per_scan(bIter,eIter);
   if(!flag){
     break;
   }
   advance(bIter,1);
   iterPos = (bIter != eIter);
  }

 return flag;
}

