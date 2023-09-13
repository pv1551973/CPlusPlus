#include "key_board.h"

#include <iostream>
#include <cctype>


using std::make_unique;
using std::cout;
using std::endl;


bool key_board::has_instance;
unique_ptr<key_board> key_board::keyboardPtr;

const key_board& key_board::get_instance(){
 if(!has_instance){
  keyboardPtr = make_unique<key_board>(PrivateTag{});
  has_instance = true; 
 }
 return *keyboardPtr;
}

key_board::key_board(PrivateTag){
 keymPtr = make_unique<key_map>(); 
 keysqPtr = make_unique<key_sequences>();

 ticker = 0; 
 initialize_matrix();
}

void key_board::initialize_matrix(){

     for(auto iter = keysqPtr->indices.begin(); iter != keysqPtr->indices.end(); ++iter){
     currIter = iter;
     loop(iter, iter->second.begin(), iter->second.end());
   } 
  return;
 }
 
void key_board::loop (mapIter mit, setIter bsit, setIter esit){
  while(bsit != esit){
    if(ticker){ticker = 0;}
    loop_again(mit, bsit);
    ++bsit;
  } 
 return;
}

void key_board::loop_again (mapIter mit, setIter sit){
  static vector<string>v;
  auto c = mit->first;
  //so that we don't go from AH to HA to AH
  static auto pre = '\0'; 

  while(ticker < 10){
  auto str = *sit;
  if(pre == str.back()){
   if(isdigit(pre)){
     if('2' == pre && str == "O2"){
       //based on debugging, since O2 got skipped and not returned to,
       //so adding the check 
     }
     //going out on a limb that we won't fall over
     //the edge of the set here (that is we are not
     //already at the last element in the set; need
    //to revisit this logic
     ++sit;
     loop_again(mit,sit);
   }
  }
  v.push_back(str);
  auto ch =  str.back();
  pre = str.at(0);
  auto ahead  = ch > c;
   if(ahead){
     while(mit->first != ch){++mit;}
      ++ticker;
      sit = mit->second.begin();
      loop_again(mit, sit);
  }
  else{
    while(mit->first != ch){--mit;}
     ++ticker;
     sit = mit->second.begin();
     loop_again(mit, sit);
  }
}
  //a temporary workaround to push back only 
  //vectors that have 10 elements in them
  //there is a bug in the code that ends up
  //with diminutive vectors, perhaps a logical
  //error in the looping; need to investigate
  //this
 if(10 == v.size()){
  matrix[currIter->first].push_back(v);
 }
 v.clear();        
 return;
}

void key_board::display() const{

 for(auto const& item : matrix){
  for(auto const& vs : item.second){
    for(auto const& s : vs){
      cout << s << endl;
    }
  }
 }
 cout << endl;
 return;
}

void key_board::alternate_display() const{
 for(auto iter = matrix.begin(); iter != matrix.end(); ++iter){
   auto vec_vec_strs = iter->second;
   for(auto iter = vec_vec_strs.begin(); iter != vec_vec_strs.end(); ++iter)   {
     auto vec_strs = *iter;
     cout << "size of this vector:" << vec_strs.size() << endl;
     cout << "contents of this vector:" << endl;
     for(auto iter = vec_strs.begin(); iter != vec_strs.end(); ++iter){
       cout << *iter << endl;
     }
  }
 }
 return;
}

#ifdef DBG_TRACE

void key_board::print_string(const string& str){
  static auto invocation = 0;
  cout << "str at " << invocation << ":" << endl;
  cout << str << endl;
  ++invocation;
 return;
}

void key_board::print_vector_of_strings(const vector<string>& v){
  static auto invocation = 0;
  if(!v.empty() && 1 < v.size()){
    cout << "Contents of v at " << invocation << ":" << endl;
    for(auto const& s : v){
      cout << s << endl;
    }
  }
  ++invocation;
 return;
}

void key_board::print_map_of_set_of_strings(const map<char,set<string>>& matrix){

 cout << "Contents of indices before construction of key_board " << ":" << endl;
 for(auto const& ss : matrix){
   cout << ss.first << endl;
  for(auto const& s : ss.second){
      cout << s << endl;
    }
  }
return;
}


void key_board::print_set_iterator_dereference(setIter sit){
 cout << "The dereferenced value of the set iterator is " << *sit << endl;
return;
}

#endif
