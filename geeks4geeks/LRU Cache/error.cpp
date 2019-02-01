#include "error.hpp"

error::error(error_code e, string msg){
   this->e = e;
   this->msg = msg;
}

error::~error(){

}

string error::what () const{
   return msg;
}
