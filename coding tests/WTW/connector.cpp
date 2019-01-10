#include "connector.hpp"
#include "file_io.hpp"
#include "data.hpp"
#include "externs.hpp"
#include<algorithm>
#include<iterator>
using std::sort;
using std::unique;
using std::stoi;
using std::stod;
using std::to_string;
using std::advance;

void connector::extract_key(array<char,MAX_BUFFER>& A){
        auto iter = A.begin();
        string key;
        char delim = ',';
        while(*iter != delim){
                key += *iter++;
        }
        keys.push_back(key);

        return;
}

void connector::extract_year_values(array<char,MAX_BUFFER>& A, string& from, string& to){
        auto iter = A.begin();
        char delim = ',';

        from.clear();
        to.clear();

        while(*iter != delim){
                ++iter;
        }
        advance(iter,2);
        while(*iter != delim){
                from += *iter++;
        }
        advance(iter,2);
        while(*iter != delim){
                to += *iter++;
        }

        return;
}

void connector::adjust_duration(array<char,MAX_BUFFER>& A){
        auto from = ZERO_STRING;
        auto to = ZERO_STRING;

        extract_year_values(A,from,to);

       if((from_to.from == ZERO_STRING) && (from_to.to == ZERO_STRING)){
               from_to.from = from;
               from_to.to = to;
     }
     else{
                if(stoi(from) < stoi(from_to.from)){
                                from_to.from = from;
                 }
                 if(stoi(to) > stoi(from_to.to)){
                                from_to.to = to;
                 }
          }

     return;
}

void connector::rem_dup_keys(){
       sort(keys.begin(),keys.end());
       auto last = unique(keys.begin(),keys.end());
       keys.erase(last,keys.end());

        return;
}

void connector::write_fromfile_todb(){

        for(auto A : file_io::input){
                extract_key(A);
                adjust_duration(A);

                if(!string(A.data()).empty()){
                        obj_udata.construct(string(&A[0]));
                }
                obj_data.insert(obj_udata);
        }

        rem_dup_keys();

        return;
}

void connector::sort_data(string& key){
        auto v = obj_data[key];
        auto i = 0;
        auto limit = v.size();

        while(i < limit - 2){
                auto j = i + 1;
                if(stoi(v[i].get_year_orig()) > stoi(v[j].get_year_orig())){
                        obj_udata = v[i];
                        v[i] = v[j];
                        v[j] = obj_udata;
                        while(j < limit - 1){
                                if(
                                    stoi(v[i].get_year_orig()) == stoi(v[j].get_year_orig()) 
                                                                        && 
                                    stoi(v[i].get_year_dev()) > stoi(v[j].get_year_dev()) 
                                   ){
                                        obj_udata = v[i];
                                        v[i] = v[j];
                                        v[j] = obj_udata;
                                     }
                                ++j;
                      }
               }
           ++i;
       }

        return;
}

void connector::create_output_string(string& key, string& s){
        auto v = obj_data[key];
        char delim = ',';
        double sum = 0;
        auto current_orig_year = 0;
        auto current_dev_year = 0;
        string zero = to_string(double(0));
        auto y_from = stoi(from_to.from); 
        auto y_to = stoi(from_to.to); 
        auto interval = y_to - y_from + 1; 

        s.clear();

        s += v[0].get_prod();
        s += delim;

       for(auto u : v){
               auto y_o = stoi(u.get_year_orig());
               auto y_d = stoi(u.get_year_dev());
               auto temp = y_from;

               if(0 == current_orig_year){
                if(y_o > temp){
                       while(temp < y_o){
                               auto y = 0;
                               while(y < interval){
                                       s += zero;
                                       s += delim;
                                       ++y;
                                }
                         ++temp;
                       }
               }
               if(temp == y_o){
                                sum += stod(u.get_val());
                                s += to_string(sum);
                                s += delim;
                       }
                  current_orig_year = temp;
                  current_dev_year = y_d;
               }//end of condition 0 == current_orig_year
               else{
                    if(y_o == current_orig_year){
                            if(y_d - current_dev_year > 1){
                                    auto diff = y_d - current_dev_year - 1;
                                    auto y = 0;
                                    while(y < diff){
                                          s += zero;
                                          s += delim;
                                          ++y;
                                    }
                                    sum += stod(u.get_val());
                                    s += to_string(sum);
                                    s += delim;

                                    current_dev_year = y_d;
                            }
                            else{
                                    sum += stod(u.get_val());
                                    s += to_string(sum);
                                    s += delim;

                                    current_dev_year = y_d;
                            }
                            if(y_d == y_to){
                                    current_orig_year++;
                                    current_dev_year = current_orig_year;
                            }
                    }//end of condition y_o == current_orig_year
                    else{
                            if(y_o > current_orig_year){
                                    if(y_d < current_dev_year){
                                            temp = current_orig_year;
                                            auto diff = y_to - current_dev_year + 1;
                                            bool flag = false;
                                            auto y = 0;
                                            while(temp < y_o){
                                                if(!flag){
                                                      while(y < diff){
                                                         s += zero;
                                                         s += delim;
                                                         ++y;
                                                        }
                                                      current_dev_year = y_d;
                                                      flag = true;
                                                }
                                                else{
                                                        if(y_o > temp){
                                                                y = 0;
                                                                while(y < interval){
                                                                        s += zero;
                                                                        s += delim;
                                                                        ++y;
                                                                }
                                                        }
                                                }
                                                 ++temp;
                                             }//end of while loop temp < y_o
                                             if(temp == y_o){
                                                                if(y_o < y_d){
                                                                        diff = y_d - y_o + 1;
                                                                        while(y < diff){
                                                                                 s += zero;
                                                                                 s += delim;
                                                                                 ++y;
                                                                         }
                                                                }
                                                                sum += stod(u.get_val());
                                                                s += to_string(sum);
                                                                s += delim;
                                                        }
                                                current_orig_year = temp;
                                    }//end of condition y_d < current_dev_year
                                    else{
                                             sum += stod(u.get_val());
                                             s += to_string(sum);
                                             s += delim;

                                             current_dev_year = y_d;
                                    }
                            }//end of condition y_o > current_orig_year
                            if(current_dev_year == y_to){
                                    current_orig_year++;
                                    current_dev_year = current_orig_year;
                            }
                    }//end of else for y_o == current_orig_year
                }//end of else for 0 == current_orig_year
       }//end of for loop

        return;
}

void connector::write_fromdb_tofile(){
        auto interval = stoi(from_to.to) - stoi(from_to.from) + 1;
        string s;
        char delim = ',';

        s.clear();

        s += from_to.from;
        s += delim;
        s += to_string(interval);

        write_output_to_memory(s);

        s.clear();

        for(auto key : keys){
                sort_data(key);
                create_output_string(key,s);
                write_output_to_memory(s);
        }

        file_io::write();
        s.clear();

        return;
}

void connector::write_output_to_memory(string& s){

        file_io::output.push_back(s);

        return;
}
