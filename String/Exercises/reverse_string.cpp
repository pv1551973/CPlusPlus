
#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

void reverse(string&);

int main(){
string s;
cout << "Enter string:";
//cin >> s;
getline(cin,s);
reverse(s);
cout << "\n" << "The reversed string is " << s << "\n";
return 0;
}

void reverse(string& s){
char* p = const_cast<char*>(s.c_str());
int i = 0;
int j = s.length() - 1;
do{
auto temp = p[i];
p[i] = p[j];
p[j] = temp;
//cout << "i " << i << " j " << j << "\n";
//cout << "p[i] " << p[i] << " p[j] " << p[j] << "\n";
//cout << "p " << p << "\n";
i++;
j--;
}while(i <= j);
s.assign(p);
return;
}
