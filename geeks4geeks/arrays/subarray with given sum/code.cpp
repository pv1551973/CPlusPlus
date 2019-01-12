#include <iostream>
#include <vector>
#include<memory>
#include<utility>
#include<algorithm>
#include<iterator>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::make_unique;
using std::unique_ptr;
using std::move;
using std::for_each;
using std::advance;

#define glue(a,b) a##b
#ifdef DBG
#define PRNT_LN_NUM (cout << "At line " << __LINE__ << endl);
#endif

//void print(vector<unique_ptr<vector<int>>>&);
void find_idx_pos_sum(vector<unique_ptr<vector<int>>>&);

int main() {
       int num_test_cases;
          auto count = 0;
          vector<unique_ptr<vector<int>>>vec_up;

                   cout << "No: of test cases:";
                     cin >> num_test_cases;
                         cout << endl;
                            
                               while(count < num_test_cases){
                                       cout << "Array " << (count + 1) << " size and sum:";
                                       unique_ptr<vector<int>> glue(up,count) = make_unique<vector<int>>();
                                       auto i = 0;
                                       cin >> i;
                                       glue(up,count).get()->push_back(i);
                                       cin >> i;
                                       glue(up,count).get()->push_back(i);
                                       cout << endl;
                                       cout << "Array of integers:";
                                       auto index = 0;
                                       while(index++ < (*glue(up,count))[0]){
                                            cin >> i;
                                            glue(up,count).get()->push_back(i);
#if 0
#ifdef DBG
                                            PRNT_LN_NUM
                                            cout << "i: " << i << endl;
                                            cout << endl;
#endif
#endif
                                         }
                                         vec_up.push_back(move(glue(up,count)));
                                         ++count;
#if 0
#ifdef DBG
                                         PRNT_LN_NUM
                                         cout << "count: " << count << endl;
#endif
#endif
                                         
                                       }
                               count = 0;

                               //print(vec_up);
                               find_idx_pos_sum(vec_up);

                               return 0;
}

void print(vector<unique_ptr<vector<int>>>& r){

   //for_each(r.begin(), r.end(), [](unique_ptr<vector<int>>&& rr){for_each(rr.get()->begin(), rr.get()->end(), [](int& ri){cout << i << endl;});}); 
   auto it = r.begin();
   while(it != r.end()){
      unique_ptr<vector<int>>&& rr = move(*it);
      for_each(rr.get()->begin(), rr.get()->end(), [](int& i){cout << i << endl;});
      ++it;
   }
   
   return;
}

void find_idx_pos_sum(vector<unique_ptr<vector<int>>>& r){

   auto sum = [] (vector<int>& r1){   

#if 0
#ifdef DBG
      for_each(r1.begin(), r1.end(), [] (int& i){cout << i << endl;});
#endif
#endif

      auto it = r1.begin();
      advance(it, 2);
      auto it2 = it;
      auto sz = r1[0];
      auto sum = r1[1];
#if 0
#ifdef DBG
      PRNT_LN_NUM
      cout << "sz: " << sz << endl;
      cout << "sum: " << sum << endl;
#endif
#endif
      auto iteration = 0;
      auto first_index = 0;
      auto last_index = 0;
      auto total = 0;

      while(iteration < sz -1){
         total = 0;
         while(it != r1.end()){
            total += *it;
            if(total == sum || total > sum)
               break;
            ++it;
            ++last_index;
         }
         if(total == sum){
            break;
         }
         ++first_index;
         last_index = first_index;
         ++iteration;
         it = it2;
         advance(it, 1);
         it2 = it;
      }
      if(total == sum){
         cout << first_index << " " << last_index << endl;  
      }
      else{
            cout << "index range corresponding to sum not found" << endl;
         }
   };

   //for_each(move(r.begin()), move(r.end()), [&](unique_ptr<vector<int>>&& rr){sum(*rr.get())});
#if 0
#ifdef DBG
   PRNT_LN_NUM
   auto itr = r.begin();
   while(itr != r.end()){
       PRNT_LN_NUM
       auto itr1 = (*itr)->begin();
       while(itr1 != (*itr)->end()){
          PRNT_LN_NUM
          cout << "*itr1: " << *itr1 << " ";
          ++itr1;
          PRNT_LN_NUM
       }
       ++itr;
       PRNT_LN_NUM
   }
   cout << endl;
#endif
#endif
   auto it = r.begin();
     while(it != r.end()){
         unique_ptr<vector<int>>&& rr = move(*it);
         vector<int>& r2 = *rr;
         //PRNT_LN_NUM
         sum(r2);
         ++it;
     }
   return;
}
