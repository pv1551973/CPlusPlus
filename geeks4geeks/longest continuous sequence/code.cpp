#include "code.hpp"
#include "error.hpp"
#ifdef DBG
#include "debug.hpp"
#endif
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cmath>
#include <utility>
#include <functional>

using std::cout;
using std::endl;
using std::all_of;
using std::isdigit;
using std::remove_if;
using std::isspace;
using std::istringstream;
using std::swap;
using std::abs;
using std::pair;
using std::make_pair;
using std::function;

void find_lcs (vector<string>& rv){
  istringstream iss;
  auto count = 0;
  auto ntc = 0;//ntc stands for number of test cases
  auto buffer = 0;

  auto lcs_find = [&](const string& r, int buffer)->int{

    function<void(vector<pair<int,int>>::iterator&, vector<pair<int,int>>::iterator&)>sort_a = [&] (auto begin, auto end)->void{//sort_a stands for sort ascending

      //decrement end; first time end would point to to the element following the last element of the container.
      end -= 1;

      if(begin == end){
        return;
      }

      auto tmpb = begin;
      while(tmpb != end){
        if((*tmpb).second > (*end).second){
          swap(*tmpb,*end);
        }
        ++tmpb;
      }
      sort_a(begin, end);
    };
    
    auto comp_cs = [&](vector<pair<int,int>>& r)->int{
      auto begin = r.begin();
      auto end = r.end();
      auto count = 0;
      auto max_count = 0;

      //sort ascending
      //sort_a(r.begin(), r.end());
      sort_a(begin, end);

      auto prev = make_pair(-1,-1);
      for(auto p : r){
        if(-1 == prev.first){
          prev = p;
        }
        else{
          if(1 == p.second - prev.second){
            ++count;
            if(max_count < count){
              max_count = count;
            }
            prev = p;
          }
          else{
            prev = p;
            count = 0;
          }
        }//end of else for if(-1 == n)
      }//end of for loop

      return max_count;

    };//end of comp_cs

    vector<int>v(buffer,-1);//fill the vector with -1, an invalid value

    //vector holding values within a sequence range, while examining v
    vector<pair<int,int>>v_mcs;

    auto sws = " ";//single white space
    size_t pos = 0;
    size_t begin = 0;
    size_t end = 0;
    size_t len = 0;
    auto i = 0;
    auto cs = 0; //cs stands for continuous sequence
    auto mcs = 0; //mcs stands for maximum continuous sequence

    while(pos != string::npos){
        if(!pos){
         pos = r.find(sws, pos);
         len = pos - begin;
         auto tmp_str = r.substr(begin, len);
         iss.clear();
         iss.str(tmp_str);
         iss >> i;
         end = pos;
       }
       else{
         pos = r.find(sws, end + 1);
         if(string::npos == pos){
           begin = end + 1; 
           end = pos;
           break;
         }
         begin = end + 1;
         len = pos - begin;
         auto tmp_str = r.substr(begin, len);
         iss.clear();
         iss.str(tmp_str);
         iss >> i;
         end = pos;
      }//end of else for if(!pos)
      if(i < buffer){
        //need to make sure that the index is not already 
        //taken
        if(-1 == v[i]){
        v[i] = i;
        }
        else{
          auto j = v[i];
          v[i] = i;
          auto n = 0;
          for(auto m: v){
            if(-1 == m){
              v[n] = j;
              break;
            }
            ++n;
          }//end of for loop
        }//end of else for if(-1 == v[i])
      }//end of if(i < buffer)
      else{
        auto j = i % buffer;
        if(-1 == v[j]){
          v[j] = i;
        }
        else{
          auto n = 0;
          for(auto m : v){
            if(-1 == m){
              v[n] = i;
              break;
            }
            ++n;
          }
        }//end of else for if(-1 == v[j])
      }//end of else for if(i < buffer)
    }//end of while(pos != string::npos)
    if(string::npos == pos){
      len = end - begin;
      auto tmp_str = r.substr(begin, len);
      iss.clear();
      iss.str(tmp_str);
      iss >> i;
      if(i < buffer)
      {
        if(-1 == v[i]){
          v[i] = i;
        }
        else{
          auto j = v[i];
          v[i] = i;
          auto n = 0;
          for(auto m : v){
            if(-1 == m){
              v[n] = j;
              break;
            }
            ++n;
          }//end of for loop
        }//end of else for if(-1 == v[i])
      }//end of if(i < buffer)
      else{
        auto j = i % buffer;
        if(-1 == v[j]){
          v[j] = i;
        }
        else{
          auto n = 0;
          for(auto m : v){
            if(-1 == m){
              v[n] = i;
            }
            ++n;
          }//end of for loop
        }//end of else for if(-1 == v[j])
      }//end of else for if(i < buffer)
    }//end of if(npos == pos)

    auto n = 0;
    auto m = 0;
    i = -3;
    //this value determines the range of the sequence
    //searched for
    auto rng_cap = 10;
    //variable to keep track of updated size for v
    auto u_buffer = buffer;//u_buffer stands for updated buffer
    //boolean to indicate actual processing within the loop
    //for a given iteration
    //if the below boolean variable was not set to true within the loop,
    //implies that v was not resized within the loop
    bool flag = false;

    do{
        if(flag){
          if(u_buffer < buffer){
            //reset n to 0
            n = 0;
            //update buffer value
            buffer = u_buffer;
          }
          //reset flag
          flag = false;
        }
        
        if(0 == n){
          m = n + 1;
          while(m < v.size()){
            if(abs(v[n] - v[m]) <= rng_cap){
              if(v_mcs.empty()){
                if(v[n] != v[m]){
                  v_mcs.push_back(make_pair(n, v[n]));
                  v_mcs.push_back(make_pair(m, v[m]));
                }
                else{
                  v_mcs.push_back(make_pair(n, v[n]));
                }
              }//end of if(v_mcs.empty())
              else{
                v_mcs.push_back(make_pair(m, v[m]));
              }
            }//end of if(abs(v[n] - v[m]) <= rng_cap)
            ++m;
          }//end of while(m < v.size())
        }//end of if(0 == n)
        else{
          m = 0;
          while(m < v.size()){
            if(abs(v[n] - v[m]) <= rng_cap){
              if(v_mcs.empty()){
                if(v[m] != v[n]){
                  v_mcs.push_back(make_pair(n, v[n]));
                  v_mcs.push_back(make_pair(m, v[m]));
                }
                else{
                  v_mcs.push_back(make_pair(n, v[n]));
                }
              }//end of if(v_mcs.empty())
              else{
                v_mcs.push_back(make_pair(m, v[m]));
              }
            }//end of if(abs(v[n] - v[m]) <= rng_cap)
            ++m;
          }//end of while(m < v.size())
        }//end of else for if(0 == n)
        if(!v_mcs.empty()){
        cs = comp_cs(v_mcs);
        }
        if(cs > mcs){
          mcs = cs;
        }
        //shrink the vector v
        if(!v_mcs.empty()){
            if(!v.empty()){
              for(auto p : v_mcs){
                auto n = 0;
                for(auto k : v){
                  if(k == p.second){
                    v.erase(v.begin() + n);
                    break;
                  }
                  ++n;
                }
                 --u_buffer;
                 flag = true;
              }
            }//end of if(!v.empty())
          v_mcs.clear();
        }//end of if(!v_mcs.empty())
        else{
          //couldn't find any sequence for current index in v
          //so delete the index
          v.erase(v.begin() + n);
          --u_buffer;
          flag = true;
        }
    }while(++n < u_buffer);//end of do-while loop

    return mcs;
  };
  auto tmp_str = rv[0];
  if(!all_of(tmp_str.begin(),tmp_str.end(),[](auto c){return isdigit(c);})){
    throw error(error_code::BAD_INPUT, "First line of input should contain the number of test cases.");
  }
  iss.clear();
  iss.str(tmp_str);
  iss >> ntc;

  auto iter = rv.begin();
  ++iter;
  while(iter != rv.end() && count < ntc){
    tmp_str = *iter;
    if(!all_of(tmp_str.begin(), tmp_str.end(), [](auto c){return isdigit(c);})){
      throw error(error_code::BAD_INPUT, "First line of each test case should contain the size of the buffer.");
    }
    iss.clear();
    iss.str(tmp_str);
    iss >> buffer;

    ++iter;
    tmp_str = *iter;
    //remove ws
    tmp_str.erase(remove_if(tmp_str.begin(), tmp_str.end(), [](auto c){return isspace(c);}),tmp_str.end());

    if(!all_of(tmp_str.begin(),tmp_str.end(), [](auto c){return isdigit(c);})){
      throw error(error_code::BAD_INPUT, "Second line of each test case should contain the buffer containing only digits.");
    }
    auto lcs = lcs_find(*iter, buffer);
    //since count for lcs starts at 0 (see lcs_find() and nested function objects),
    //need to increment lcs by one before display to stdout
    cout << lcs + 1 << " ";

    ++iter;
    ++count;
  
  }//end of while(iter != rv.end())

  cout << endl;

  return;
}
