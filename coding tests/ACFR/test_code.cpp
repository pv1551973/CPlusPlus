#include "test_code.hpp"

xRan::xRan(){
vector<int>v(MAX_ELEMS);
mt19937 g(rd());
auto mode = ios::out | ios::trunc;
ofstream fs(FILENAME,mode);
if(fs.good()){
iota(v.begin(),v.end(),1);
shuffle(v.begin(),v.end(),g);
std::copy(v.begin(),v.end(),std::ostream_iterator<int>(fs, " "));
fs.close();
}
}//end of constructor defintion
