#include "error.hpp"

error::error(error_code e){
this->e = e;
}//constructor defintion

error_code error::get(){return e;}

void error::set(error_code e){this->e = e;}
