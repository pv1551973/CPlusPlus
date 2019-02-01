#ifndef CODE_HPP
#define CODE_HPP
#include "error.hpp"
#ifdef DBG
#include "debug.hpp"
#endif
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <utility>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ios>
#include <algorithm>
using std::string;
using std::getline;
using std::ifstream;
using std::istringstream;
using std::isdigit;
using std::isalpha;
using std::pair;
using std::make_pair;
using std::for_each;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::boolalpha;
using std::fill_n;
using std::find;

template<typename T>
class cache{
public:
   cache(string,T&);
   ~cache();
private:
   void parse_input_file (string&);
private:
   T& impl;
};

template<typename T> cache<T>::cache(string filename, T& rc):impl(rc){//rc is abbreviation for reference to container
   parse_input_file(filename);
}

template<typename T> cache<T>::cache::~cache(){}

template<typename T> void cache<T>::parse_input_file (string& filename){

auto parse_query = [](const string& s)->string{
   //sample query
   //SET 1 2 GET 1
   string refined_query;
   auto it = s.begin();
   while(it != s.end()){
      if(isalpha(*it)){
         if('S' == *it){
            refined_query.push_back(*it);
            while(!isdigit(*++it)){}
            refined_query.push_back(*it);
            while(!isdigit(*++it)){}
            refined_query.push_back(*it);
         }
         else if('G' == *it){
            refined_query.push_back(*it);
            while(!isdigit(*++it)){}
            refined_query.push_back(*it);
         }
         else{
            error e(error_code::BAD_QUERY, "Query should have the pattern \"SET<SINGLE WS><NUMBER><SINGLE WS><NUMBER><SINGLE WS>GET<SINGLE WS><NUMBER>\"");
            throw e;
         }
      }
         ++it;
   }
   return refined_query;
};

auto process_query = [](const string& s, T& rc, int limit)->string{
   string result;
   string sws = " "; //single white space
   //used to store the index value in the query
   auto index = 0;
   //used to both index into the array and the vector
   auto count = 0;
   //p.first -> index of the array where the data is stored
   //p.second -> index in the query corresponding to the stored data
   auto p = make_pair(-1,-1);
   vector<decltype(p)>v_indices(limit,p);
   //a flag for conditional processing
   bool found = false;
   //flag used for flushing containters
   //as well as facilitating a certain
   //part of the processing logic
   bool first_invocation = true;
   //for impelementing the condition of
   //"invalidating the least recently used item"
   //in the problem statement
   vector<int>v_lui;//lui stands for least updated indices
   auto v_lui_idx = 0;//current least updated index position in v_lui

   //clear the contents of the container
   if(first_invocation){
      //for(auto i : rc){i = -1;}
     fill_n(rc.begin(), rc.max_size(), -1);
      v_lui.clear();
   }

   auto it = s.begin();

   while(it != s.end()){
      if('S' == *it){
         ++it;
         index = *it - '0';
         ++it;
         if(!found){
         //try find and replace value corresponding to index 
            for(auto k : v_indices){
               if(k.second == index){
                  rc[k.first] = *it - '0';
                  //set flag to true
                  found = true;
                  //update v_lui accordingly
                    auto it = find(v_lui.begin(), v_lui.end(), k.first);
                    if(it != v_lui.end()){
                      v_lui.erase(it);
                      //recently updated index in v_lui should be the last entry
                      v_lui.push_back(k.first);
                }
                  break;
               }//end of if(k.second == index)
            }//end of for loop
         }//end of if(!found)
         //this and the above conditional statement blocks
         //are mutually exclusive if index is located above
         if(!found){
            if(index < limit && count < limit)
            {
               if(count == index){
                if(-1 == rc[count]){
                 rc[count] = *it - '0';
                 p.first = count;
                 p.second = index;
                 v_indices[count] = p;
                 if(first_invocation){
                   v_lui.push_back(count);
                   first_invocation = false;
                 }
                 else{
                   v_lui.push_back(count);
                 }
                 ++count;
             }//end of if(-1 == rc[count])
             else{
               //existing data needs to be overwritten
                rc[count] = *it - '0';
                p.first = count;
                p.second = index;
                v_indices[count] = p;
                //do not increment count as it is a substitution
               //update v_lui accordingly
                auto it = find(v_lui.begin(), v_lui.end(), count);
                if(it != v_lui.end()){
                  v_lui.erase(it);
                  //recently updated count should be the last entry
                  v_lui.push_back(count);
                }
            }//end of else for if(-1 == rc[count])
           }//end of if(count == index)
           else{
              rc[index] = *it - '0';
              //in this instance, only the index variable
              //is used for indexing
              //count should reach the value of index at a
              //later time during program execution
              p.first = index;
              p.second = index;
              v_indices[index] = p;
              //do not increment count as index was used here
              if(first_invocation){
                 v_lui.push_back(index);
                 first_invocation = false;
              }
              else{
                 v_lui.push_back(index);
                }//end of else for if(first_invocation)
           }//end of else for if(count == index)
         }//end of if(index < limit && count < limit)
         else if(index >= limit && count < limit){
            if(-1 == rc[count]){
               rc[count] = *it - '0';
               p.first = count;
               p.second = index;
               //count should always be less than limit 
               v_indices[count] = p;
              if(first_invocation){
                 v_lui.push_back(count);
                 first_invocation = false;
              }
              else{
                v_lui.push_back(count);
              }//end of else for if(first_invocation)
               ++count;
            }//end of if(-1 == rc[count)
            else{
                  auto i = count;
                  //find if there is a vacant slot in the array
                  for(; i < limit ; ++i){
                  if(-1 == rc[i]){break;}
                  }
                  if(i < limit){
                  //found an empty slot
                  //use i instead of count for indexing into
                  //the vector
                  rc[i] = *it - '0';
                  p.first = i;
                  p.second = index;
                  v_indices[i] = p;
                  //do not increment count here
                  //count should eventually catch up with i
                  if(first_invocation){
                     v_lui.push_back(i);
                     first_invocation = false;
                  }//end of if(first_invocation)
                  else{
                      v_lui.push_back(i);
                     }//end of else for if(first_invocation)
               }//end of if(i < limit)
               else{
                  //no vacant slot
                  //rewrite the slot that had been written to first 
                  //in this series ("least recently used item in the problem")
                 rc[v_lui[v_lui_idx]] = *it - '0';
                    //update the corresponding index value in v_indices
                    v_indices[v_lui[v_lui_idx]].second = index;
                    //update v_lui accordingly
                    auto temp_val = v_lui[v_lui_idx];
                    v_lui.erase(v_lui.begin() + v_lui_idx);
                    //recently updated index into rc should be the last
                    //entry in v_lui
                    v_lui.push_back(temp_val);
               }//end of else for if(i < limit)
            }//end of else for if(-1 == rc[count])
         }//end of else if(index >= limit && count < limit)
         else if((index < limit && count == limit) || (index >= limit && count == limit)){
            auto i = v_lui[v_lui_idx];
            rc[i] = *it - '0';
            p.first = i; 
            p.second = index; 
            //i should always be less than limit 
            v_indices[i] = p;
            //update v_lui
            v_lui.erase(v_lui.begin() + v_lui_idx);
            if(v_lui.empty()){
              //should not get to this processing logic
              error e(error_code::BAD_PROCESSING_LOGIC, "The vector of replacement indices has been exhausted.");
              throw e;
            }
         }//end of else if((index < limit && count == limit) || (index >= limit && count == limit))
       }//end of if(!found)
     }//end of if('S' == *it)
     else if('G' == *it){
         ++it;
         index = *it - '0';
         auto iter = v_indices.begin();
         while(iter != v_indices.end()){
            if((*iter).second == index){
             result += to_string(rc[(*iter).first]);
             result += sws; 
             break;
            }
            ++iter;
       }
         if(iter == v_indices.end()){
           result += "-1";
           result += sws; 
         }
     }//end of else if('G' == *it)
      ++it;
      //reset the flag found here
      found = false;
#ifdef DBG
      ++loop_count;
#endif
   }//end of while(it != s.end()
   //remove the last sws
   auto pos = result.find_last_of(sws);
   result.erase(pos,result.size() - 1);

   //reset loop count here
   loop_count = 0;

   return result;
};

auto print = [] (const string& s){
   cout << "Program output: " << s << endl;

   return;
};

   string s;
   auto count = 0;
   //not used
   auto num_test_cases = 0;
   //used for limiting container indexing
   auto cache_capacity = 0;
   //not used
   auto num_queries = 0;

   ifstream file_handle(filename);
   if(!file_handle){
      //error e (error_code::BAD_FILE_NAME, "Can't open file %s", filename);
      error e (error_code::BAD_FILE_NAME, "Can't open file on disk.");
      throw e;
   }
   while(!file_handle.eof()){
      getline(file_handle, s);
      if( 0 == count){
         for(auto i = 0; i < s.length(); ++i){
            if(!isdigit(s[i])){
               error e (error_code::BAD_FILE_INPUT, "First line of input should contain the number of test cases.");
               throw e;
              }
         }
         istringstream iss(s);
         iss >> num_test_cases;
         ++count;
         continue;
      }
      else if(1 == count){
         for(auto i = 0; i < s.length(); ++i){
            if(!isdigit(s[i])){
               error e (error_code::BAD_FILE_INPUT, "Second line of input should contain the cache capacity.");
               throw e;
              }
         }
          istringstream iss(s);
          iss >> cache_capacity;
          if(!(cache_capacity < impl.max_size())){
             error e (error_code::BAD_CACHE_CAPACITY, "Specified cache capacity is larger than the permissible cap value.");
             throw e;
          }
          ++count;
          continue;
      }
      else if(2 == count){
         for(auto i = 0; i < s.length(); ++i){
            if(!isdigit(s[i])){
               error e (error_code::BAD_FILE_INPUT, "Third line of input should contain the number of queries.");
               throw e;
              }
          istringstream iss(s);
          iss >> num_queries;
          ++count;
          continue;
      }
    }
      else{
         auto s1 = parse_query(s);
         s1 = process_query(s1, impl, cache_capacity);
         print(s1);
         //reset count to 1 for the processing of remaining test cases
         count = 1;

      }
   }
   
   return;
}
#endif
