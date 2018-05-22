
#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::string;

bool are_uniq_chars(string const&);

int main(){
string s;
cout << "Enter string: ";
cin >> s;
auto flag = are_uniq_chars(s);
if(flag)
cout << "\n" << s << " has unique characters" << "\n";
else
cout << "\n" << s << " does not have unique characters" << "\n";
return 0;
}

bool are_uniq_chars(string const& s){
bool flag = false;
int i = 0, j = 0;
int length = s.length();
while(i++ < length){
for(j = i + 1; j < length; ++j){
if(s[i] == s[j])
goto END;
}
flag = true;
} 
END:
return flag;
}
