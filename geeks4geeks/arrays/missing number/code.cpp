#include <iostream>
#include <vector>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::for_each;

void find_missing_num (vector<int>&);

int main (void){

   auto num_test_cases = 0;

   cout << "Enter the number of test cases: ";
   cin >> num_test_cases;
   cout << endl;

   auto count = 0;
   auto sz = 0;
   vector<int> v;

   while(count < num_test_cases){
      cout << "Enter array" << count + 1 << " size: ";
      cin >> sz;
      cout << endl;
      cout << "Enter array" << count + 1 << " : ";
      auto i = 0;
      auto x = 0;
      while(x < sz - 1){
         cin >> i;
         v.push_back(i);
         ++x;
      }
      cout << endl;
      find_missing_num(v);
      v.clear();
      ++count;
   }

#if 0
#ifdef DBG
   for_each(v.begin(), v.end(), [](int& i){cout << i << " ";}); 
   cout << endl;
#endif
#endif


   return 0;
}

void find_missing_num (vector<int>& r){
   
   auto it1 = r.begin();
#if 0
#ifdef DBG
   cout << "*it1: " << *it1 << endl;
#endif
#endif
   auto it2 = it1;
   ++it1;

   do{
#if 0
#ifdef DBG
      cout << "*it1: " << *it1 << endl;
      cout << "*it2: " << *it2 << endl;
#endif
#endif
      if(*it1 != (*it2 + 1)){
         break;
      }
      else{
         it2 = it1;
      }
   }while(it1++ != r.end());
   
   if(it1 != r.end()){
      cout << "Missing number is " << *it2 + 1 << endl;
   }
   else{
      cout << "No missing number!" << endl;
   }

   return;
}
