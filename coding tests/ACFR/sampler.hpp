#ifndef SAMPLER_H
#define SAMPLER_H
#include "func_objs.hpp"

//template declaration
template <typename T>
class sampler{
public:
sampler(const T&, double);
double get_sampling_rate();
void set_sampling_rate(double);
void generate_sample();
private:
const T& db;
double sampling_rate;
};//end class template sampler

//template definition
template <typename T>
sampler<T>::sampler(const T& dbref, double frequency):db(dbref),sampling_rate(frequency) { }//end of constructor defintion

template <typename T> 
double sampler<T>::get_sampling_rate(){
return sampling_rate;
}//end of definiton for get_sampling_rate

template <typename T>
void sampler<T>::set_sampling_rate(double rate){
if(0 > rate || rate > 1.0){//if block 1 
error e(error_code::out_of_bound_index);
throw e;
}//end of if block 1 
sampling_rate = rate;
}//end of definition for set_sampling_rate

template <typename T>
void sampler<T>::generate_sample(){
using fobj_print = func_objs::print; 
using fobj_increment = func_objs::increment; 
using fobj_limit = func_objs::limit; 

int total = db.get_num_elems();
int count = 0;
double rate = sampling_rate;
while(fobj_limit()(count,total)){
fobj_increment()(rate,count);
//need to break here if 
//the value of count equals or
//exceeds the DB size
if(count >= total)
break;
fobj_print()(db.get_data(count));
}//end of while
}//end of definition for generate_sample
#endif
