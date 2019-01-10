#ifndef ERROR_H
#define ERROR_H

enum class error_code{
invalid_filename,
invalid_range,
out_of_bound_index,
};

class error{
public:
error(error_code);
error_code get();
void set(error_code);
private:
error_code e;
};
#endif
