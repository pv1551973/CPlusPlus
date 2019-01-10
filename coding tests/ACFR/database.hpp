#ifndef DATABASE_H
#define DATABASE_H
#include "func_objs.hpp"
#include<vector>

using namespace func_objs;
class database;
using func_objs_templ_cls_inst = class create_db_from_file<database>;

class database{
public:
database(const std::string&);
const std::string& get_data(int) const;
int get_num_elems() const;
private:
friend func_objs_templ_cls_inst;
void read_from_file();
const std::string& filename;
std::vector<std::string> v;
};//end of class definition
#endif
