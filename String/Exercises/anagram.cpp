
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
using std::cin;
using std::getline;
using std::cout;
using std::string;
using std::istringstream;
using std::vector;
using std::endl;

bool is_anagrm(string const&, string const&);

int main(){
string input, token;
vector<string>substrs;
int count = 0;
cout << "Enter the strings (separated by white space):";
getline(cin,input);
istringstream iss(input);
#if 0
do{
iss >> token;
substrs.push_back(token);
++count;
}while(iss);
#endif
while(iss >> token){
substrs.push_back(token);
++count;
}
if(count != 2){
cout << "Exactly two strings are required for anagram evaluation" << "\n";
}
else if(substrs[0].length() != substrs[1].length()){
cout << "Unequal strings, not suitable candidates for anagrams" << "\n";
}
else{
if(is_anagrm(substrs[0],substrs[1]))
cout << "\n" << "The strings " << substrs[0] << " and " << substrs[1]  << " are anagrams" << "\n";
else
cout << "\n" << "The strings " << substrs[0] << " and " << substrs[1]  << " are not anagrams" << "\n";
}
return 0;
}

bool is_anagrm(string const& s1, string const& s2){
auto fnd_rpt_chrs = [&] (string::const_iterator iter1, string::const_iterator iter2) {
for(auto iter = iter2 + 1; iter != s2.end(); ++iter){
if(*iter == *iter1)
return true;
}
return false;
};
int count = 0;
static auto i = 0, j = 0;
for(auto it_s1 = s1.begin(); it_s1 != s1.end(); ++it_s1){
cout << "value of count is " << count << endl;
cout << "outer loop iteration:" << ++i << endl;
cout << "value of it_s1 is " << *it_s1 << endl;
for(auto it_s2 = s2.begin(); it_s2 != s2.end(); ++it_s2){
cout << "inner loop iteration:" << ++j << endl;
cout << "value of it_s2 is " << *it_s2 << endl;
if(*it_s1 == *it_s2){
++count;
if(fnd_rpt_chrs(it_s1,it_s2))
break;
}
}
}
if(count == s1.length())
return true;
else
return false;
}
