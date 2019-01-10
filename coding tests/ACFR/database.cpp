#include "database.hpp"

using std::vector;
using std::string;

database::database(const string& s):filename(s){
read_from_file();
}//constructor definition

void database::read_from_file(){
func_objs_templ_cls_inst func_obj_read_from_file_into_db(*this);
func_obj_read_from_file_into_db(filename);
}//end of read_from_file definition

const string& database::get_data(int index) const{
if(0 > index || index >= v.size()){
error e(error_code::invalid_range);
throw e;
}//end of if statment block
return v[index];
}//end of get_data definition

int database::get_num_elems() const{
return v.size();
}//end of get_num_elems defintion
