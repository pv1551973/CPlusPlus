#include "code.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

string_parse::string_parse(string s){
	this->s = s;
	ss.clear();
	method();
}

string_parse::~string_parse(){
}

void string_parse::method(void){

	//lambda
	auto compare = [](const char& a, const char& b)->bool{return a == b;};
	string tmp_ss;
	tmp_ss.clear();

	for(auto c : s){
		if(tmp_ss.empty()){
			tmp_ss.push_back(c);
		}
		else{
			bool is_repeat = false;
			for(auto ch : tmp_ss){
				if(compare(ch, c)){
					is_repeat = true;
					continue;
				}
			}
			if(is_repeat){
				if(ss.size() < tmp_ss.size()){
					ss = tmp_ss;
				}
				tmp_ss.clear();
				tmp_ss.push_back(c);
				is_repeat = false;
			}
			else{
				tmp_ss.push_back(c);
			}
		}
	}
	if(ss.size() < tmp_ss.size()){
		ss = tmp_ss;
	}

	cout << "The longest unique substring is " << ss <<  " which is " << ss.size() << " bytes long." << endl;

	return;
}
