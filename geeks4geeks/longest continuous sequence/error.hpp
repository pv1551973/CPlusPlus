#ifndef ERROR_HPP
#define ERROR_HPP
#include <string>
using std::string;

enum class error_code{BAD_INPUT,BAD_INDEX,};

class error{
  public:
    error(error_code, string);
    ~error();
    string what ();
  private:
    error_code e;
    string msg;
};

#endif
