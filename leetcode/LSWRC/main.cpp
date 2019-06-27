#include "code.hpp"
#include <iostream>

using std::cout;
using std::cin;

int main (void){

	string s;

	cout << "Enter the string: ";
        cin >> s;	
	string_parse obj(s);

	return 0;
}
