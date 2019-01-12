#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cctype>
#include <cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::getline;
using std::stringstream;
using std::pair;
using std::make_pair;
using std::for_each;
using std::remove_if;
using std::exit;

void print(int, vector<pair<int,string>>&);
void find_max_sum(int, vector<pair<int,string>>&);

#define PRNT_LN_NUM (cout << "At line " << __LINE__ << endl);

int main (void){

   string input;
   vector<pair<int,string>> aggregate_input ;

   cout << "Enter number of test cases: ";
   getline(cin, input);
   auto p = make_pair(0,input);
   aggregate_input.push_back(p);
   stringstream ss (input);
   int num_test_cases = 0;
   ss >> num_test_cases;

   int count = 0;

   while(count < num_test_cases){
      cout << "Enter array " << count + 1 << " size: " ;
      getline(cin, input);
      p = make_pair(count + 1, input);
      aggregate_input.push_back(p);

      //cout << "p.second (size): " << p.second << endl;

      cout << "Enter array " << count + 1 << ": " ;
      getline(cin, input);
      ss.clear();
      ss.str(p.second);
      auto usr_input_sz = 0;
      ss >> usr_input_sz;
      auto array_sz_no_spaces = 0;
      auto itr = input.begin();
      //loop required to account for '-' character in input
      //need to revisit for a better algorithm
      while(itr != input.end()){
         if(*itr == '-'){
            ++itr;
            if(isdigit(*itr)){
               while(isdigit(*(++itr))){
               //to account for integers with multiple digits
                  continue;
               }
               ++array_sz_no_spaces;
            }
         }
         else if(isspace(*itr)){
            ++itr;
            continue;
         }
         else if(isdigit(*itr)){
            while(isdigit(*(++itr))){
              //to account for integers with multiple digits
                 continue;
              }
            ++array_sz_no_spaces;
         }
      }
      if(usr_input_sz != array_sz_no_spaces){
         //cout << "usr_input_sz: " << usr_input_sz << endl;
         //cout << "array_sz_no_spaces: " << array_sz_no_spaces << endl;
         cout << "insufficient number of input integers" << endl;
         exit(0);
      }
      //cout << "input.size(): " << input.size() << endl;
      p = make_pair(count + 1, input);
      aggregate_input.push_back(p);

      ++count;
   }
   //for_each(aggregate_input.begin(), aggregate_input.end(), [](pair<int,string>& p){cout << p.first << " " << p.second << endl;});

   //print(num_test_cases, aggregate_input);
   find_max_sum(num_test_cases, aggregate_input);

   return 0;
}

void print(int num_test_cases, vector<pair<int,string>>& r){

   auto count = 1;
   auto it = r.begin();
   //skip the number of test cases
   ++it;
   while(it != r.end()){
      while(count <= num_test_cases){
         auto p = *it;
         if(p.first == count){
            stringstream ss(p.second);
            int sz = 0;
            ss >> sz;
            ++it;
            p = *it;
            if(p.first == count){
               cout << "array" << count << ":";
               string s = p.second;
               s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
               cout << s;
               cout << endl;
               for(auto i = 0; i < sz; ++i){
                  int val = s[i] - '0';
                  cout << val;
                  cout << " ";
               }
               cout << endl;
               ++count;
               break;
            }
            else{
               ++count;
               break;
            }
         }
         else{
            ++count;
            break;
         }
      }
      ++it;
   }

   return;
}

void find_max_sum(int num_test_cases, vector<pair<int, string>>& r){

   auto iter = r.begin();
   auto count = 1;
   vector<int> v;

   auto do_sum = [&](){

      for_each(v.begin(), v.end(), [](int& k){cout << k << " ";});
      cout << endl;

      auto sz = v.size(); 
      auto i = 0;
      auto sum = 0;
      auto max = 0;
      auto it = v.begin();
      //loop to check if all the array elements are negative numbers
      //for_each(v.begin(), v.end(), [](int& k){if(k >= 0) break; ++i;});
      while( i < sz){
         if(v[i] >= 0)
            break;
         ++i;
      }
      //cout << "i: " << i << endl;
      //cout << "sz: " << sz << endl;
      if(i == sz)
         goto LOOP2;
      else
         goto LOOP1;

LOOP1:
      //need this assignment here due to the possibility of temporary break
      //from the loop because of a -ve value
      sum = 0;
      //PRNT_LN_NUM
      while(it != v.end()){
         if(*it >= 0){
            sum += *it;
            if(sum > max){
               max = sum;
            }
         }
         else{
            break;
         }
         ++it;
      }
      if(it != v.end()){
         ++it;
         goto LOOP1;
      }
      else{
         goto FINAL;
      }
LOOP2:
      //PRNT_LN_NUM
      while(it != v.end()){
        sum = *it;
        if(0 == max){
         if(sum < max){
            //cout << "sum: " << sum << endl;
            max = sum;
         }
        }
        else{
            if(sum > max){
               //cout << "sum: " << sum << endl;
               max = sum;
            }
        }
        ++it;
      }
      
FINAL:
      cout << "Max sum of subarray in array" << count << " = " << max << endl;

      return;
   };
   
   while(iter != r.end()){
      auto p = *iter;
      if(p.first == 0){
         ++iter;
         continue;
      }
      auto sz = 0;
      stringstream ss(p.second);
      ss >> sz;
       ++iter;
       p = *iter;
       //cout << "p.second: " << p.second << endl;
       //string s = p.second;
       //s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
       //cout << "s: " << s << endl;
      //for(auto i = 0; i < sz; ++i){
         //int val = s[i] - '0';
         //cout << "val: " << val << endl;
         //v.push_back(val);
      //}
      //for_each(v.begin(), v.end(), [](int& i){cout << i;});
      //cout << endl;
      //ss = p.second;
      ss.clear();
      ss.str(p.second);
      //cout << "ss.str(): " << ss.str() << endl;
      int val = 0;
      int i = 0;
      do{
         ss >> val;
         //cout << "val: " << val << endl;
         v.push_back(val);
      }while(++i < sz);
      
      do_sum();
      v.clear();
      ++count;
      ++iter;
   }

   return;
}
