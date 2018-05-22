
#include<iostream>
#include<string>
using std::cin;
using std::getline;
using std::cout;
using std::string;

void rem_dup_chrs(string&);

int main(){
string s;
cout << "Enter the string:";
getline(cin,s);
rem_dup_chrs(s);
cout << "\n" << "The revised string is " << s << "\n";
return 0;
}

void rem_dup_chrs(string& s){
for(auto it = s.begin(); it != s.end(); ++it){
for(auto i = s.length() - 1; i; i--){
if(*it == s[i]){
if(i != (it - s.begin()))
s.erase(i,1);
}
}
}
return;
}
