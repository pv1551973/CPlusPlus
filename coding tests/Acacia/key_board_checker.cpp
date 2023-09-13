#include "key_board_checker.h"

#include <iostream>
#include <set>
#include <iterator>
#include <cctype>
#include <algorithm>
#include <utility>

using std::set;
using std::advance;
using std::cout;
using std::endl;
using std::for_each;
using std::as_const;

//const unsigned short key_board_checker::maxletters = 52;
array<bool,key_board_checker::maxletters> key_board_checker::alphabet{};

//const unsigned short key_board_checker::numalnumidx = 18;
array<char,key_board_checker::numalnumidx> key_board_checker::alnum = {'1', '2', '3', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};

key_board_checker::key_board_checker(const key_board& rkb):rkb(rkb){

 initialize_vowels();
 check_keyboard();
}

void key_board_checker::initialize_vowels (){
  alphabet['A'] = true;
  alphabet['a'] = true;
 
  alphabet['E'] = true;
  alphabet['e'] = true;

  alphabet['I'] = true;
  alphabet['i'] = true;

  alphabet['O'] = true;
  alphabet['o'] = true;

  alphabet['U'] = true;
  alphabet['u'] = true;

 return;
}

//void key_board_checker::check_keyboard(){
void key_board_checker::check_keyboard () const{
    cout << "Checking this key board for valid key sequences..." << endl; 
    step1();
 return;
}

void key_board_checker::step1()const {
  using nonconst_type_kbmatrix = map<char,vector<vector<string>>>;
  const auto& kbmatrix = rkb.keyboardPtr->matrix;
  auto curralnumidxnum = 0;
  string seq = "";

   while (curralnumidxnum < numalnumidx){
     auto idxkbmatrix = alnum[curralnumidxnum];
     const auto& vvs = const_cast<nonconst_type_kbmatrix&>(kbmatrix)[idxkbmatrix];
     auto szvvs = vvs.size();
     decltype(szvvs) curvvsidxnum = 0;

     while(curvvsidxnum < szvvs){
      const auto& vs = vvs[curvvsidxnum];
      step2(vs);
      const auto& v = final[vs[0]];
      step3(v, seq); 
      step4(seq,vs);
      ++curvvsidxnum;
     } 
   ++curralnumidxnum;
  }
 return;
}

void key_board_checker::step2(const vector<string>& vs)const {
  using nonconst_type_ksqmatrix = map<string,set<string>>;
  const auto& ksqmatrix = rkb.keysqPtr->matrix;
  auto& v = final[vs[0]];
  auto last = vs.size(); 
  decltype(last) first = 0;

  while(first < last){
    auto idxksqm = vs[first]; 
    const auto& pack = const_cast<nonconst_type_ksqmatrix&>(ksqmatrix)[idxksqm];
    auto szpk = pack.size();
    decltype(szpk) count = 0;
    auto piter = pack.begin();
    
    while(count < szpk){
      advance(piter,count);
      v.push_back(*piter);
      ++count;
      //only take into consideration the 
      //first of multiple sequences 
      //a present design constraint
      if(1 == count){break;}
    }
   ++first; 
  }
 return;
}

void key_board_checker::step3(const vector<string>& v, string& seq)const {

  seq.clear();
  auto last = v.size();
  decltype(last) first = 0;

  while(first < last){
    seq += v[first];
    ++first;
  }

 return;
}

void key_board_checker::step4 (const string& s, const vector<string>& vs)const {

     auto vowelcount = 0;

    for(auto c : s){
      if(!isdigit(c)){
        if(check_if_vowel(c))
         {
           ++vowelcount;
         }
     }
     if(2 < vowelcount){break;}
  }
  
  if(2 >= vowelcount){
       for(const auto& s : vs){
          cout << s << " ";
       }
    cout << endl;
  }

 return;
} 

bool key_board_checker::check_if_vowel(char c) const{
   return alphabet[c];
}

//debugging helper methods
#ifdef DBG_TRACE

void key_board_checker::print_vs(const vector<string>& vs) const{ 
  static auto invocation_count = 0;
  cout << "invocation count:" << invocation_count++ <<endl;
  cout << "size of vector:" << vs.size() << endl;
  for(const auto& s : vs){
   cout << s << " ";
  }
  cout << endl;

 return;
}


void key_board_checker::print_strset(const set<string>& ss) const{ 
  
   auto static invocation_count = 0;
   const auto space = " ";
   cout << "invocation count:" << invocation_count++ <<endl;
   for_each(ss.begin(),ss.end(),[&](const auto& s){cout << s << space;});
   cout << endl;

 return;
}

void key_board_checker::print_str(const string& s) const{ 

   auto static invocation_count = 0;
   const auto space = " ";

   cout << "invocation count:" << invocation_count++ <<endl;
   cout << s << space;
   cout << endl;

 return;
}

void key_board_checker::print_idx_str(unsigned short idx, const string& s) const{ 

   auto static invocation_count = 0;
   const auto space = " ";

   cout << "invocation count:" << invocation_count++ <<endl;
   cout << idx << space;
   if(!s.empty()){cout << s << space;}
   else{cout << "empty string!!!" << space;}
   cout << endl;

 return;
}

#endif
