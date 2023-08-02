#include<iostream>
#include<string>

using std::string;
using std::cout;
using std::endl;

string s = "abcdefghijklmnopqrstuvwxyz";

int main (void){
	auto start = s.begin();
	auto end = s.end() - 1;
	bool flag = true;

	cout << s << endl;

	do{
		while(start != end){
			if(start == end){
				break;
			}
			if (*start == *end)
			{
				flag = false;
				goto END;
			}
			++start;
		}
		start = s.begin();
	}while(--end != s.begin());

END:
	if(flag){
		cout << "Unique string" << endl;
	}
	else{
		cout << "Not unique string" << endl;
	}
		return 0;
}
