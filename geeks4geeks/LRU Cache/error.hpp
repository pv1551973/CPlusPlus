#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
using std::string;

enum class error_code {BAD_FILE_NAME, BAD_FILE_INPUT, BAD_QUERY, BAD_FILE_OPEN, BAD_CACHE_CAPACITY, BAD_PROCESSING_LOGIC,};

class error{
public:
   error(error_code, string);
   ~error();
public:
   string what () const;
private:
   error_code e;
   string msg;
};


#endif
