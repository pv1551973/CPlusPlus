#include "ll.hpp"
#include "error.hpp"
#include<string>
#include<fstream>
#include<vector>
using std::cin;
using std::getline;
using std::string;
using std::ifstream;
using std::vector;

#define RANDOM 15

int main (){
try{
string filename;
string line;
vector<string>dataObj;
cout << "Enter filename:";
cin >> filename;
ifstream fileObj(filename);
if(fileObj.is_open()){
while(getline(fileObj,line)){
dataObj.push_back(line);
}
}
fileObj.close();
size_t sz = dataObj.size();
List<string,vector<string>> list(sz,dataObj);
//list.display();
string s = "new";
sz = list.getNumElems();
int pos = sz  % RANDOM;
if(pos < 0 || pos >= sz){
error_code e(error_code::BAD_RANGE);
throw e;
} 
list.insert(pos, s);
list.display();
pos += 1;
list.remove(pos);
list.display();
}
catch(error_code e){
switch(e){
case error_code::BAD_RANGE:
cout << "Invalid index count proposed to access container element.";
cout << endl;
return 1;
}
}
catch(...){

}
return 0;
}
