#include "data.hpp"
#include "error.hpp"
#include "constants.hpp"
#include<sstream>
#include<algorithm>
using std::stringstream;
using std::getline;
using std::find;

void unit_data::construct(string&& input_line){

        auto parse_input_line = [&](){

               vector<string> tokens;
               stringstream ss(input_line);
               string token;
               char delim = ',';
               char ws = ' ';
               size_t count = 0;
               bool flag = false;

               while(getline(ss,token,delim)){
                       if(!flag){
                               tokens.push_back(token);
                               flag = true;
                       }
                       else{
                               token.erase(find(token.begin(), token.end(), ws));
                               tokens.push_back(token);
                       }
               }

              if(4 != (count = tokens.size())){
                      throw(Error_Code::BAD_INPUT);
              }
              while(count > 0){
                      if(4 == count){
                              val = tokens[count - 1];
                              --count;
                      }
                      else if(3 == count){
                              year_dev = tokens[count - 1];
                              --count;
                      }
                      else if(2 == count){
                              year_orig = tokens[count - 1];
                              --count;
                      }
                      else if(1 == count){
                              prod = tokens[count - 1];
                              --count;
                      }
              }
              
              return;
        };

        parse_input_line();

        return;
}

void unit_data::operator = (unit_data& rhs){
        this->prod = rhs.get_prod();
        this->year_orig = rhs.get_year_orig();
        this->year_dev = rhs.get_year_dev();
        this->val = rhs.get_val();

        return;
}

string& unit_data::get_prod(){
        return prod;
}

string& unit_data::get_year_orig(){
        return year_orig;
}

string& unit_data::get_year_dev(){
        return year_dev;
}

string& unit_data::get_val(){
        return val;
}

void data::insert(unit_data& entry){

        auto iter = repo.find(entry.get_prod());

        if(iter == repo.end()){
                vector<unit_data> v{entry};
                repo[entry.get_prod()] = v;
        }
        else{
                iter->second.push_back(entry);
        }

        return;
}

vector<unit_data>& data::operator [] (const string& key){

        return(repo[key]);
}
