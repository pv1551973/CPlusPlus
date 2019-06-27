#ifndef CODE_HPP
#define CODE_HPP
#include <string>
using std::string;

class parse{
	protected:
		virtual void method () = 0;
};

class string_parse : protected parse{
	public:
		string_parse(string);
		~string_parse();
	protected:
		virtual void method ();
	private:
		string s;
		string ss; //substring
};

#endif
