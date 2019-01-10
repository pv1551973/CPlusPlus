#ifndef FUNCOBJ_H
#define FUNCOBJ_H
#include "error.hpp"
#include<iostream>
#include<fstream>
#include<string>

using std::ifstream;
using std::string;
using std::cin;
using std::cout;

//template declaration
namespace func_objs{
template <typename T>
class create_db_from_file{
public:
create_db_from_file(T&);
void operator()(const std::string&);
private:
T& db;
};//end class template create_db_from_file 

struct print{
void operator()(const string& s)const{
cout << s << " ";
}
}; 

struct increment{
void operator()(const double& d, int& i){
double sum = 0.0;
do{
sum += d;
++i;
}while(sum < 1.0);
}
};

struct limit{
bool operator()(double a, double b){
return (a < b);
} 
};
}//end namespace

//template definition

template <typename T>
func_objs::create_db_from_file<T>::create_db_from_file(T& dbref):db(dbref){}//end of constructor defintion

template <typename T>
void func_objs::create_db_from_file<T>::operator()(const string& s){
string read;
auto mode = ifstream::in;

ifstream ifs(s,mode);
while(ifs >> read){
db.v.push_back(read);
}//end of while
ifs.close();
}//end of operator() definition
#endif
